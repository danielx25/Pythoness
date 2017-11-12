#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "VariablesLinguisticas.h"
#include "Reglas.h"
#include "SistemaFAM.h"
#include "Validacion.h"

using namespace std;
using namespace Datos;
using namespace SFAM;

namespace ValidacionRNA
{
	void Validacion::validacionFAM(string archv_validacion, string archv_reglas)
	{
		ifstream in(archv_validacion);
		string line;
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		variableslinguisticas->getVariables(vars);
		vector<string> orden_vars;
		Validacion::variables(orden_vars);
		int registro = 1;
		int aciertos = 0;

		while (getline(in, line)) {
			SistemaFAM* sfam = new SistemaFAM();
			map<string, double> entrada;
			stringstream sep(line);
			string field;
			int posicion = 0;
			int num_nrns = 6;
			double valor_mp10 = 0;

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
			Reglas::leerReglas(archv_reglas, reglas);

			for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
				sfam->agregarRegla(*regla);

			while (getline(sep, field, ';') && posicion < vars.size()) {
				double valor = atof(field.c_str());
				string nom_var = orden_vars.at(posicion);

				if (nom_var != "mp10")
				{
					// realizamos ajustes a las variables "circulares".
					if (nom_var == "estacion") valor = getEstacion(valor);
					else if (nom_var == "hora") valor = getHora(valor);
					else if (nom_var == "direccion_viento") valor = getDViento(valor);

					// si el valor esta fuera de los limites, lo corregimos.
					if (valor < vars[nom_var]->getMinimo()) valor = valor < vars[nom_var]->getMinimo();
					else if (valor > vars[nom_var]->getMaximo()) valor = valor < vars[nom_var]->getMaximo();

					entrada[nom_var] = valor;

					posicion += 1;
				}
				else
				{
					valor_mp10 = valor;
				}
			}

			double prediccion = sfam->getSalida(entrada);

			if (Validacion::getAcierto(prediccion, valor_mp10, vars["mp10"]))
				aciertos += 1;

			Validacion::guardarProgreso(registro, aciertos);

			registro += 1;
			//cout << "Prediccion: " << prediccion << " Valor Real: " << valor_mp10 << "\n";
		}

		in.close();
	}

	double Validacion::getEstacion(double valor)
	{
		if (valor < 2.5 && valor > 1) valor += 12;

		return valor;
	}

	double Validacion::getHora(double valor)
	{
		if (valor < 1 && valor > 0) valor += 24;
		
		return valor;
	}

	double Validacion::getDViento(double valor)
	{
		if (valor < 45 && valor > 0) valor += 360;
		
		return valor;
	}

	bool Validacion::getAcierto(double prediccion, double valor_real, VariableLinguistica*& mp10)
	{
		string predecido = mp10->getValor(prediccion);
		string real = mp10->getValor(valor_real);

		if (predecido == real)
			return true;

		return false;
	}

	void Validacion::guardarProgreso(double registro, double aciertos)
	{
		double acertividad = (aciertos / registro) * 100;
		ofstream archivo;
		archivo.open("progreso.txt");
		archivo << registro << ";" << aciertos << ";" << acertividad;
		archivo.close();
	}

	void Validacion::variables(vector<string>& variables)
	{
		variables.push_back("estacion");
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
		variables.push_back("pala3");
		variables.push_back("pala4");
		variables.push_back("pala5");
		variables.push_back("pala7");
		variables.push_back("pala8");
		variables.push_back("pala10");
		variables.push_back("pala11");
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
}