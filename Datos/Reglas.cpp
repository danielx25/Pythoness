#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Reglas.h"
#include "VariablesLinguisticas.h"
#include "Normalizacion.h"

namespace Datos
{
	void Reglas::variables(vector<string>& variables)
	{
		variables.push_back("verano");
		variables.push_back("invierno");
		variables.push_back("hora");
		variables.push_back("velocidad_viento");
		variables.push_back("direccion_viento");
		variables.push_back("temperatura");
		variables.push_back("humedad_relativa");
		variables.push_back("radiacion_solar");
		variables.push_back("presion_atmosferica");
		variables.push_back("precipitacion_dia1");
		variables.push_back("precipitacion_dia2");
		variables.push_back("precipitacion_dia3");
		variables.push_back("precipitacion_dia4");
		variables.push_back("precipitacion_dia5");
		variables.push_back("evaporacion_dia1");
		variables.push_back("evaporacion_dia2");
		variables.push_back("evaporacion_dia3");
		variables.push_back("evaporacion_dia4");
		variables.push_back("evaporacion_dia5");
		variables.push_back("pala1");
		variables.push_back("pala2");
		variables.push_back("pala3");
		variables.push_back("pala4");
		variables.push_back("pala5");
		variables.push_back("pala6");
		variables.push_back("pala7");
		variables.push_back("pala8");
		variables.push_back("chancador1");
		variables.push_back("chancador2");
		variables.push_back("chaxa_camion");
		variables.push_back("movitec_camion");
		variables.push_back("das_camion");
		variables.push_back("cnorte_consumo_agua");
		variables.push_back("cmovil_consumo_agua");
		variables.push_back("cachimba1_consumo_agua");
		variables.push_back("cachimba2_consumo_agua");
		variables.push_back("gerencia_consumo_agua");
		variables.push_back("mp10");
	}


	void Reglas::extraccionReglas(string archivo, vector<string>& reglas)
	{
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		ifstream in(archivo);
		string line;
		vector<string> orden_vars;
		vector<string> antecedentes;
		variableslinguisticas->getVariables(vars);
		Reglas::variables(orden_vars);

		while (getline(in, line)) {
			stringstream sep(line);
			string field;
			string regla;
			string antecedente;
			int posicion = 0;
			double grado_verano = 0;
			
			regla = "Si ";

			while (getline(sep, field, ';') && posicion < orden_vars.size()) {
				double valor = atof(field.c_str());
				double val_desnormalizado = 0;
				string nom_var = orden_vars.at(posicion);
				string nom_val;

				if (posicion == 0)
				{
					grado_verano = valor;
				}
				else
				{
					if (posicion == 1)
					{
						nom_var = "estacion";

						if (valor > grado_verano) nom_val = "invierno";
						else if (valor < grado_verano) nom_val = "verano";
					}
					else
					{
						val_desnormalizado = Normalizacion::desnormalizar(valor, vars[nom_var]->getMinimo(), vars[nom_var]->getMaximo());

						nom_val = vars[nom_var]->getValor(val_desnormalizado);
					}

					if (posicion == orden_vars.size() - 1)
					{
						antecedente = regla;
						regla += " entonces ";
					}
					else if (posicion > 0 && posicion != 1) regla += " y ";

					regla += nom_var + " es " + nom_val;

					//cout << "Variable: " << nom_var << " Valor linguistico: " << nom_val << " Valor: " << valor << " Valor Desnormalizado: " << val_desnormalizado << "\n";
				}

				posicion += 1;
			}

			// comprobamos si la regla ya ha sido generada.
			bool existe = false;

			for (vector<string>::iterator ant = antecedentes.begin(); ant != antecedentes.end() && existe == false; ++ant)
			{
				if (*ant == antecedente) existe = true;
			}

			if (!existe)
			{
				antecedentes.push_back(antecedente);
				reglas.push_back(regla);
			}

			double continuar = 0;

			//cin >> continuar;

			//cout << "\n\n";
		}

		in.close();
	}

	void Reglas::leerReglas(string archivo, vector<string>& reglas)
	{
		ifstream in(archivo);
		string regla;

		while (getline(in, regla))
		{
			if (regla != "") reglas.push_back(regla);
		}

		in.close();
	}

	void Reglas::guardarReglas(string archivo, vector<string>& reglas)
	{
		ofstream archivo_reglas;
		archivo_reglas.open(archivo);

		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
			archivo_reglas << *regla << "\n";
		
		archivo_reglas.close();
	}
}