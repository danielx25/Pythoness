#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Normalizacion.h"
#include "VariablesLinguisticas.h"
#include "Reglas.h"
#include "Discretizacion.h"

namespace Datos
{
	void Discretizacion::datos(int neuronas, string archv_datos, string archv_salida, bool desnormalizar)
	{
		vector<string> filas;
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		ifstream in(archv_datos);
		string line;
		vector<pair<string, pair<double, double>>> orden_vars;
		vector<string> antecedentes;
		variableslinguisticas->getVariables(vars);
		Reglas::variables(orden_vars);
		//int neuronas = 10;
		int num_nrns = 0;
		double porcentaje = (100.0 / neuronas) / 100.0;
		map<string, double*> valores_variables;

		// seteamos los valores de las neuronas para las variables liguisticas.
		Reglas::setValoresVariables(vars, porcentaje, num_nrns, valores_variables);

		while (getline(in, line)) {
			stringstream sep(line);
			string field;
			string fila;
			string antecedente;
			int posicion = 0;

			while (getline(sep, field, ';') && posicion < orden_vars.size()) {
				double valor = atof(field.c_str());
				double val_desnormalizado = 0;
				string nom_var = orden_vars.at(posicion).first;
				string nom_val;
				double var_max = orden_vars.at(posicion).second.second;
				double var_min = orden_vars.at(posicion).second.first;

				if (desnormalizar)
					val_desnormalizado = Normalizacion::desnormalizar(valor, var_min, var_max);
				else
					val_desnormalizado = valor;

				// realizamos ajustes a las variables "circulares".
				if (nom_var == "estacion")
					val_desnormalizado = Reglas::getEstacion(val_desnormalizado);
				else if (nom_var == "hora")
					val_desnormalizado = Reglas::getHora(val_desnormalizado);
				else if (nom_var == "direccion_viento")
					val_desnormalizado = Reglas::getDViento(val_desnormalizado);

				if (val_desnormalizado > var_max) val_desnormalizado = var_max;
				else if (val_desnormalizado < var_min) val_desnormalizado = var_min;

				// obtenemos el valor de la neurona que se activa con el valor.
				if (nom_var != "pala1" && nom_var != "pala3" && nom_var != "pala4" && nom_var != "pala5" && nom_var != "pala7" && nom_var != "pala8" && nom_var != "pala10" && nom_var != "pala11" && nom_var != "chancador1" && nom_var != "chancador2")
				{
					val_desnormalizado = Reglas::getValorNeurona(valores_variables[nom_var], num_nrns, val_desnormalizado);
				}

				nom_val = vars[nom_var]->getValor(val_desnormalizado);

				fila += nom_val;

				if (posicion < (orden_vars.size() - 1)) fila += ";";

				posicion += 1;
			}

			filas.push_back(fila);
		}

		in.close();
		Reglas::guardarReglas(archv_salida, filas);
	}

	void Discretizacion::valoresVariables(string archv_salida)
	{
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		variableslinguisticas->getVariables(vars);
		vector<string> filas;

		for (map<string, VariableLinguistica*>::iterator var = vars.begin(); var != vars.end(); ++var)
		{
			map<string, ValorLinguistico*> vals;
			string fila = "";

			var->second->getValores(vals);

			fila += var->first + ";";

			int posicion = 0;
			for (map<string, ValorLinguistico*>::iterator val = vals.begin(); val != vals.end(); ++val)
			{
				fila += val->first;

				if (posicion < (vals.size() - 1)) fila += ";";
				
				posicion += 1;
			}

			filas.push_back(fila);
		}

		Reglas::guardarReglas(archv_salida, filas);
	}
}