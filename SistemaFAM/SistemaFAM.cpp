#include "stdafx.h"
#include <sstream>
#include "SistemaFAM.h"

namespace SFAM
{
	/*
	Sistema FAM para un control difuso para multiples antecedentes y un solo consecuente.
	*/
	SistemaFAM::SistemaFAM() { }

	SistemaFAM::~SistemaFAM()
	{

	}

	void SistemaFAM::agregarVariable(VariableLinguistica*& variable)
	{
		variables[variable->getNombre()] = variable;
	}

	void SistemaFAM::agregarValoresVariable(string variable, double comienzo, double espacio, int num_vals)
	{
		double valor_actual = comienzo;
		num_vals_vars[variable] = num_vals;
		valores_variables[variable] = new double[num_vals];

		// agregamos los valores no fuzzificados para la variable.
		for (int i = 0; i < num_vals; i++)
		{
			valores_variables[variable][i] = valor_actual;
			valor_actual += espacio;
		}

		// fuzzificamos los valores agregados para todos los valores linguisticos.
		map<string, ValorLinguistico*> valores;
		variables[variable]->getValores(valores);

		for (map<string, ValorLinguistico*>::iterator valor = valores.begin(); valor != valores.end(); ++valor)
		{
			fuzzificacion(valor->second, valores_variables[variable], num_vals, grados_vals_vars[variable][valor->second->getNombre()]);
		}
	}


	void SistemaFAM::agregarRegla(string regla)
	{
		reglas.push_back(regla);
	}

	void SistemaFAM::fuzzificacion(ValorLinguistico*& valor, double*& vals_vars, int num_vals, double*& grados)
	{
		grados = new double[num_vals];

		for (int i = 0; i < num_vals; i++)
		{
			valor->CalcularGradoPertenencia(vals_vars[i]);
			grados[i] = valor->getGradoPertenencia();
		}
	}


	void SistemaFAM::inferenciaDescomposicional(double**& salidas, int num_salidas, int num_vals, string operador, double*& salida)
	{
		salida = new double[num_vals];

		salida = salidas[0];

		for (int s = 1; s < num_salidas; s++)
		{
			if (operador == "y")
			{
				for (int i = 0; i < num_vals; i++)
				{
					if (salidas[s][i] < salida[i]) salida[i] = salidas[s][i];
				}
			}
			else if (operador == "o")
			{
				for (int i = 0; i < num_vals; i++)
				{
					if (salidas[s][i] > salida[i]) salida[i] = salidas[s][i];
				}
			}
		}
	}

	void SistemaFAM::evaluacionRegla(map<string, string>& vars, string& consecuente, string& val_consc, string& operador, map<string, double>& entrada, double*& salida)
	{
		double** salidas;
		int salida_actual = 0;

		salidas = new double*[vars.size()];

		// obtenemos las salidas para cada antecedente de la regla.
		for (map<string, string>::iterator var = vars.begin(); var != vars.end(); ++var)
		{
			double* bit;

			FAM* fam = new FAM(grados_vals_vars[var->first][var->second], num_vals_vars[var->first], grados_vals_vars[consecuente][val_consc], num_vals_vars[consecuente]);

			getBitVector(var->first, entrada[var->first], bit);
			fam->getSalidaB(bit, salidas[salida_actual]);
			salida_actual += 1;
		}

		inferenciaDescomposicional(salidas, vars.size(), num_vals_vars[consecuente], operador, salida);
	}

	void SistemaFAM::getBitVector(string variable, double valor_entrada, double*& bit)
	{
		int num_vals = num_vals_vars[variable];
		bit = new double[num_vals];
		int valor = abs(valor_entrada - valores_variables[variable][0]);
		int posicion = 0;

		for (int i = 0; i < num_vals; i++)
		{
			bit[i] = 0;

			if (valor > abs(valor_entrada - valores_variables[variable][i]))
			{
				valor = abs(valor_entrada - valores_variables[variable][i]);
				posicion = i;
			}
		}

		bit[posicion] = 1;
	}

	void SistemaFAM::getElementosRegla(const string& regla, map<string, string>& vars, string& consecuente, string& val_consc, string& operador)
	{
		operador = "";
		istringstream iss(regla);
		bool es_consecuente = false;
		string variable = "";

		do
		{
			string elemento = ""; // elemento actual de la regla.
			iss >> elemento;

			if (elemento != "Si" && elemento != "es")
			{
				if (elemento == "entonces")
				{
					es_consecuente = true;
				}
				else if (elemento == "y")
				{
					if (operador == "") operador = "y";
				}
				else if (elemento == "o")
				{
					if (operador == "") operador = "o";
				}
				else if (variable == "")
				{
					variable = elemento;
				}
				else
				{
					// el elemento actual es un valor linguistico.
					if (!es_consecuente)
					{
						vars[variable] = elemento;
					}
					else
					{
						consecuente = variable;
						val_consc = elemento;
					}

					variable = "";
				}
			}
		} while (iss);
	}

	void SistemaFAM::getCapaSuma(double**& salidas, int num_salidas, int num_vals, double*& suma)
	{
		suma = new double[num_vals];

		// iniciamos todos los valores de la capa suma en cero.
		for (int i = 0; i < num_vals; i++) suma[i] = 0;

		for (int s = 0; s < num_salidas; s++)
		{
			for (int i = 0; i < num_vals; i++)
			{
				suma[i] += salidas[s][i];
			}
		}
	}

	double SistemaFAM::getCentroide(double*& suma, double*& vals_consc, int num_vals)
	{
		double numerador = 0;
		double denominador = 0;
		double centroide = 0;

		for (int i = 0; i < num_vals; i++)
		{
			numerador += vals_consc[i] * suma[i];
			denominador += suma[i];
		}

		centroide = numerador / denominador;

		return centroide;
	}

	void SistemaFAM::getValores(string variable, double*& valores)
	{
		valores = valores_variables[variable];
	}

	void SistemaFAM::getGradosValores(string variable, string valor, double*& grados)
	{
		grados = grados_vals_vars[variable][valor];
	}

	void SistemaFAM::getReglas(vector<string>& r)
	{
		r = reglas;
	}

	double SistemaFAM::getSalida(map<string, double>& entrada)
	{
		double salida = 0;
		int regla_actual = 0;
		double** salida_reglas;
		double* suma;
		string consecuente;

		salida_reglas = new double*[reglas.size()];

		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
		{
			map<string, string> vars;
			string val_consc;
			string operador;

			getElementosRegla(*regla, vars, consecuente, val_consc, operador);
			evaluacionRegla(vars, consecuente, val_consc, operador, entrada, salida_reglas[regla_actual]);
			regla_actual += 1;
		}

		getCapaSuma(salida_reglas, reglas.size(), num_vals_vars[consecuente], suma);
		salida = getCentroide(suma, valores_variables[consecuente], num_vals_vars[consecuente]);

		return salida;
	}
}