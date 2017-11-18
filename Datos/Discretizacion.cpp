#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Normalizacion.h"
#include "Discretizacion.h"
#include "VariablesLinguisticas.h"
#include "Reglas.h"

namespace Datos
{
	void Discretizacion::pesos(string archv_pesos, string archv_salida)
	{
		vector<string> filas;
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		ifstream in(archv_pesos);
		string line;
		vector<pair<string, pair<double, double>>> orden_vars;
		vector<string> antecedentes;
		variableslinguisticas->getVariables(vars);
		Reglas::variables(orden_vars);

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

				val_desnormalizado = Normalizacion::desnormalizar(valor, var_min, var_max);
					
				// realizamos ajustes a las variables "circulares".
				if (nom_var == "estacion")
					val_desnormalizado = Reglas::getEstacion(val_desnormalizado);
				else if (nom_var == "hora")
					val_desnormalizado = Reglas::getHora(val_desnormalizado);
				else if (nom_var == "direccion_viento")
					val_desnormalizado = Reglas::getDViento(val_desnormalizado);

				if (val_desnormalizado > var_max) val_desnormalizado = var_max;
				else if (val_desnormalizado < var_min) val_desnormalizado = var_min;

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