#include "stdafx.h"
#include <iostream>
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

		//cout << "Valores Variables: " << variable << "\n";
		// agregamos los valores no fuzzificados para la variable.
		for (int i = 0; i < num_vals; i++)
		{
			//cout << valor_actual << " ";

			valores_variables[variable][i] = valor_actual;
			valor_actual += espacio;
		}
		//cout << "\n";

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

		//cout << "Grados Pertenencia Valor: " << valor->getNombre() << "\n";
		for (int i = 0; i < num_vals; i++)
		{
			valor->CalcularGradoPertenencia(vals_vars[i]);
			grados[i] = valor->getGradoPertenencia();
			//cout << grados[i] << " ";
		}
		//cout << "\n";

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

	void SistemaFAM::evaluacionReglas(int comienzo, int fin)
	{
		string consecuente;

		for (int r = comienzo; r < fin; r++)
		{
			map<string, string> vars;
			string val_consc;
			string operador;

			getElementosRegla(reglas[r], vars, consecuente, val_consc, operador);
			evaluacionRegla(vars, consecuente, val_consc, operador, salida_reglas[r]);
		}
	}


	void SistemaFAM::evaluacionRegla(map<string, string>& vars, string& consecuente, string& val_consc, string& operador, double*& salida)
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
			
			/*cout << "Salida Antecedente: " << var->first << " es " << var->second << "\n";
			for (int i = 0; i < num_vals_vars[consecuente]; i++)
				cout << salidas[salida_actual][i] << " ";
			cout << "\n";*/

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

		//cout << "Centroide\n";
		for (int i = 0; i < num_vals; i++)
		{
			//cout << "valor consc: " << vals_consc[i] << " suma: " << suma[i] << "\n";
			//cout << "suma: " << suma[i] << "\n";
			numerador += vals_consc[i] * suma[i];
			denominador += suma[i];
		}

		//cout << "numerador: " << numerador << " denominador: " << denominador << "\n";
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

	double SistemaFAM::getSalida(map<string, double>& e)
	{
		double salida = 0;
		int regla_actual = 0;
		double* suma;
		string consecuente = "mp10";

		entrada = e;

		salida_reglas = new double*[reglas.size()];

		/*for (int i = 0; i < reglas.size(); i++)
		{
			salida_reglas[i] = new double[num_vals_vars["mp10"]];
			
			for (int j = 0; j < num_vals_vars["mp10"]; j++) salida_reglas[i][j] = 0;
		}*/

		const int num_hilos = 12;
		int particion = reglas.size() / num_hilos;
		thread hilos[num_hilos];

		for (int i = 0; i < num_hilos; i++)
		{
			int comienzo = particion * i;
			int fin = 0;
			if (i + 1 == num_hilos) fin = reglas.size();
			else fin = particion * (i + 1);

			hilos[i] = thread(&SistemaFAM::evaluacionReglas, this, comienzo, fin);
		}
			

		for (int i = 0; i < num_hilos; i++)
			hilos[i].join();

		//evaluacionReglas(0, reglas.size());

		/*for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
		{
			map<string, string> vars;
			string val_consc;
			string operador;

			getElementosRegla(*regla, vars, consecuente, val_consc, operador);
			evaluacionRegla(vars, consecuente, val_consc, operador, salida_reglas[regla_actual]);

			//cout << "\nRegla:" << regla_actual << "\n";
			for (int j = 0; j < num_vals_vars[consecuente]; j++)
			{
				//cout << salida_reglas[regla_actual][j] << " ";
			}
			//cout << "\n";

			regla_actual += 1;
		}*/

		/*cout << "\nSalida Regla\n";

		cout << salida_reglas[5][0] << " ";
		cout << salida_reglas[5][1] << " ";
		cout << salida_reglas[5][2] << " ";
		cout << salida_reglas[5][3] << " ";
		cout << salida_reglas[5][4] << " ";
		cout << salida_reglas[5][5] << " \n";*/

		/*for (int i = 0; i < reglas.size(); i++)
		{
			cout << "Regla:" << i << "\n";
			for (int j = 0; j < num_vals_vars[consecuente]; j++)
			{
				cout << salida_reglas[i][j] << " ";
			}
			cout << "\n";
		}*/

		getCapaSuma(salida_reglas, reglas.size(), num_vals_vars[consecuente], suma);
		salida = getCentroide(suma, valores_variables[consecuente], num_vals_vars[consecuente]);

		return salida;
	}
}