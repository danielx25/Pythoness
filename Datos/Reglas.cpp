#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Reglas.h"
#include "VariablesLinguisticas.h"
#include "Normalizacion.h"

namespace Datos
{
	void Reglas::variables(vector<pair<string, pair<double, double>>>& variables)
	{
		variables.push_back(make_pair("estacion", make_pair(0.0, 12.0)));
		variables.push_back(make_pair("hora", make_pair(0.0, 24.0)));
		variables.push_back(make_pair("velocidad_viento", make_pair(0.0, 30.0)));
		variables.push_back(make_pair("direccion_viento", make_pair(0.0, 360.0)));
		variables.push_back(make_pair("temperatura", make_pair(-10.0, 55.0)));
		variables.push_back(make_pair("humedad_relativa", make_pair(0.0, 100.0)));
		variables.push_back(make_pair("radiacion_solar", make_pair(0.0, 1700.0)));
		//variables.push_back("presion_atmosferica");
		variables.push_back(make_pair("precipitacion_dia1", make_pair(0.0, 2860.0)));
		variables.push_back(make_pair("precipitacion_dia2", make_pair(0.0, 2860.0)));
		variables.push_back(make_pair("precipitacion_dia3", make_pair(0.0, 2860.0)));
		variables.push_back(make_pair("precipitacion_dia4", make_pair(0.0, 2860.0)));
		variables.push_back(make_pair("precipitacion_dia5", make_pair(0.0, 2860.0)));
		variables.push_back(make_pair("evaporacion", make_pair(-1.0, 255.0)));
		/*variables.push_back("evaporacion_dia1");
		variables.push_back("evaporacion_dia2");
		variables.push_back("evaporacion_dia3");
		variables.push_back("evaporacion_dia4");
		variables.push_back("evaporacion_dia5");*/
		variables.push_back(make_pair("pala1", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("pala3", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("pala4", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("pala5", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("pala7", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("pala8", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("pala10", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("pala11", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("chancador1", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("chancador2", make_pair(0.0, 1.0)));
		variables.push_back(make_pair("chaxa_camion", make_pair(-1.0, 7.0)));
		variables.push_back(make_pair("movitec_camion", make_pair(-1.0, 8.0)));
		variables.push_back(make_pair("das_camion", make_pair(-1.0, 4.0)));
		variables.push_back(make_pair("cnorte_consumo_agua", make_pair(0.0, 90240.0)));
		variables.push_back(make_pair("cmovil_consumo_agua", make_pair(0.0, 4480.0)));
		variables.push_back(make_pair("cachimba1_consumo_agua", make_pair(0.0, 1500.0)));
		variables.push_back(make_pair("cachimba2_consumo_agua", make_pair(0.0, 2270.0)));
		variables.push_back(make_pair("gerencia_consumo_agua", make_pair(0.0, 27000.0)));
		variables.push_back(make_pair("mp10", make_pair(0.0, 800.0)));
	}


	void Reglas::extraccionReglas(string archivo, vector<string>& reglas, bool desnormalizar)
	{
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		ifstream in(archivo);
		string line;
		vector<pair<string, pair<double, double>>> orden_vars;
		vector<string> antecedentes;
		variableslinguisticas->getVariables(vars);
		Reglas::variables(orden_vars);

		while (getline(in, line)) {
			stringstream sep(line);
			string field;
			string regla;
			string antecedente;
			int posicion = 0;
			
			regla = "Si ";

			while (getline(sep, field, ';') && posicion < orden_vars.size()) {
				if ((posicion > 3 && posicion < 6) || posicion > 30)
				{
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

					//cout << nom_var << ": " << val_desnormalizado << " ";

					// realizamos ajustes a las variables "circulares".
					if (nom_var == "estacion")
						val_desnormalizado = getEstacion(val_desnormalizado);
					else if (nom_var == "hora")
						val_desnormalizado = getHora(val_desnormalizado);
					else if (nom_var == "direccion_viento")
						val_desnormalizado = getDViento(val_desnormalizado);

					if (val_desnormalizado > var_max) val_desnormalizado = var_max;
					else if (val_desnormalizado < var_min) val_desnormalizado = var_min;

					nom_val = vars[nom_var]->getValor(val_desnormalizado);

					if (posicion == orden_vars.size() - 1)
					{
						antecedente = regla;
						regla += " entonces ";
					}
					else if (posicion > 0)
						regla += " y ";

					regla += nom_var + " es " + nom_val;

					//cout << "Variable: " << nom_var << " Valor linguistico: " << nom_val << " Valor: " << valor << " Valor Desnormalizado: " << val_desnormalizado << "\n";
				}
				

				posicion += 1;
			}

			//cout << "\n";

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

	double Reglas::getEstacion(double valor)
	{
		if (valor < 2.5 && valor > 1) valor += 12;

		return valor;
	}

	double Reglas::getHora(double valor)
	{
		if (valor < 1 && valor > 0) valor += 24;

		return valor;
	}

	double Reglas::getDViento(double valor)
	{
		if (valor < 45 && valor > 0) valor += 360;

		return valor;
	}
}