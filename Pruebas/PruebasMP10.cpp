#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "PruebasMP10.h"
#include "VariableLinguistica.h"
#include "FuncionTriangular.h"
#include "FuncionTrapezoidal.h"
#include "VariablesLinguisticas.h"
#include "Reglas.h"
#include "Normalizacion.h"

using namespace std;
using namespace LogicaDifusa;
using namespace Datos;

namespace PruebasMP
{
	PruebasMP10::PruebasMP10()
	{
		sfam = new SistemaFAM();
		VariablesLinguisticas* variables = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;

		variables->getVariables(vars);

		int num_nrns = 6;
		map<string, double> entrada;
		map<string, double> valor_norm;

		/*valor_norm["estacion"] = 0.852;
		valor_norm["hora"] = 0.542;
		valor_norm["velocidad_viento"] = 0.121;
		valor_norm["direccion_viento"] = 0.631;
		valor_norm["temperatura"] = 0.403;
		valor_norm["humedad_relativa"] = 0.2;
		valor_norm["radiacion_solar"] = 0.643;
		valor_norm["presion_atmosferica"] = 0.96;
		valor_norm["precipitacion_dia1"] = 0;
		valor_norm["precipitacion_dia2"] = 0;
		valor_norm["precipitacion_dia3"] = 0;
		valor_norm["precipitacion_dia4"] = 0.002;
		valor_norm["precipitacion_dia5"] = 0;
		valor_norm["evaporacion_dia1"] = 0.47;
		valor_norm["evaporacion_dia2"] = 0.473;
		valor_norm["evaporacion_dia3"] = 0.47;
		valor_norm["evaporacion_dia4"] = 0.475;
		valor_norm["evaporacion_dia5"] = 0.473;
		valor_norm["pala1"] = 1;
		valor_norm["pala2"] = 0;
		valor_norm["pala3"] = 0;
		valor_norm["pala4"] = 0;
		valor_norm["pala5"] = 0;
		valor_norm["pala6"] = 0;
		valor_norm["pala7"] = 1;
		valor_norm["pala8"] = 0;
		valor_norm["chancador1"] = 0;
		valor_norm["chancador2"] = 0;
		valor_norm["chaxa_camion"] = 1;
		valor_norm["movitec_camion"] = 0.444;
		valor_norm["das_camion"] = 0.6;
		valor_norm["cnorte_consumo_agua"] = 0.001;
		valor_norm["cmovil_consumo_agua"] = 0;
		valor_norm["cachimba1_consumo_agua"] = 0.028;
		valor_norm["cachimba2_consumo_agua"] = 0.015;
		valor_norm["gerencia_consumo_agua"] = 0;
		valor_norm["mp10"] = 0.034;*/

		for (map<string, VariableLinguistica*>::iterator var = vars.begin(); var != vars.end(); ++var)
		{
			double espacio = (var->second->getMaximo() - var->second->getMinimo()) * .1;
			double comienzo = var->second->getMinimo() + espacio;

			sfam->agregarVariable(var->second);
			sfam->agregarValoresVariable(var->second->getNombre(), comienzo, espacio, num_nrns);

			/*if (var->second->getNombre() != "mp10")
				entrada[var->second->getNombre()] = Normalizacion::desnormalizar(valor_norm[var->second->getNombre()], var->second->getMinimo(), var->second->getMaximo());*/
		}

		vector<string> reglas;
		Reglas::leerReglas("reglas.txt", reglas);

		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
			sfam->agregarRegla(*regla);

		ifstream in("validacion.csv");
		string line;

		while (getline(in, line)) {
			stringstream sep(line);
			string field;
			string regla;
			int posicion = 0;
			double grado_verano = 0;
			vector<string> orden_vars;

			Reglas::variables(orden_vars);

			while (getline(sep, field, ';') && posicion < orden_vars.size()) {
				double valor_norm = atof(field.c_str());
				double val_desnormalizado = 0;
				string nom_var = orden_vars.at(posicion);

				if (nom_var != "mp10")
				{
					if (posicion == 0)
					{
						grado_verano = valor_norm;
					}
					else
					{
						if (posicion == 1)
						{
							nom_var = "estacion";

							if (valor_norm < grado_verano) valor_norm = grado_verano;
						}

						entrada[nom_var] = Normalizacion::desnormalizar(valor_norm, vars[nom_var]->getMinimo(), vars[nom_var]->getMaximo());
					}

				}
				else
				{
					//cout << "Entrada lista\n";

					double salida = 0;
					salida = sfam->getSalida(entrada);
					
					cout << "Salida: " << salida << " Valor historico: " << Normalizacion::desnormalizar(valor_norm, vars["mp10"]->getMinimo(), vars["mp10"]->getMaximo()) << "\n";
				}

				posicion += 1;
			}
		}

		in.close();
	}

	void PruebasMP10::imprimirMatriz(double**& matriz, int filas, int cols)
	{
		cout << "  ";
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int i = 0; i < filas; i++)
		{
			cout << i << " ";

			for (int j = 0; j < cols; j++)
				cout << matriz[i][j] << " ";

			cout << "\n";
		}
	}

	void PruebasMP10::imprimirArray(double*& arr, int cols)
	{
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int j = 0; j < cols; j++)
			cout << arr[j] << " ";

		cout << "\n";
	}
}