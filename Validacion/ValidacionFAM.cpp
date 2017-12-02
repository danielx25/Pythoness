#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "VariablesLinguisticas.h"
#include "Reglas.h"
#include "ValidacionFAM.h"

using namespace std;
using namespace Datos;

namespace ValidacionRNA
{
	void ValidacionFAM::validacionFAM(string archv_validacion, string archv_reglas, int neuronas)
	{
		vector<string> registros;
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		variableslinguisticas->getVariables(vars);
		vector<string> orden_vars;
		ValidacionFAM::variables(orden_vars);
		int progreso = 0;
		int respaldo = 1;
		double registro = 1;
		double aciertos = 0;
		double acertividad = 0;
		int linea_actual = 0;
		double porcentaje = (100.0 / neuronas) / 100.0;

		// borramos los aciertos de ejecuciones anteriores.
		remove(ValidacionFAM::getArchvAciertos().c_str());

		getRegistros(archv_validacion, registros);

		// cargamos el progreso previo si existiera alguno.
		ValidacionFAM::getProgreso(respaldo, aciertos);

		vector<string> reglas;
		Reglas::leerReglas(archv_reglas, reglas);

		SistemaFAM* sfam = new SistemaFAM();

		for (map<string, VariableLinguistica*>::iterator var = vars.begin(); var != vars.end(); ++var)
		{
			double espacio = (var->second->getMaximo() - var->second->getMinimo()) * porcentaje;
			int num_nrns = ((var->second->getMaximo() - var->second->getMinimo()) / espacio) + 1;

			double comienzo = var->second->getMinimo() /*+ espacio*/;
			//double comienzo = 0;

			sfam->agregarVariable(var->second);
			sfam->agregarValoresVariable(var->second->getNombre(), comienzo, espacio, num_nrns);
		}

		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
			sfam->agregarRegla(*regla);

		for (int i = respaldo; i <= registros.size(); i++) {
			registro = i;
			map<string, double> entrada;
			stringstream sep(registros.at(registro - 1));
			string field;
			int posicion = 0;
			double valor_mp10 = 0;

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
					if (valor < vars[nom_var]->getMinimo()) valor = vars[nom_var]->getMinimo();
					else if (valor > vars[nom_var]->getMaximo()) valor = vars[nom_var]->getMaximo();

					entrada[nom_var] = valor;

					posicion += 1;
				}
				else
				{
					valor_mp10 = valor;
				}
			}

			double prediccion = sfam->getSalida(entrada);

			if (ValidacionFAM::getAcierto(prediccion, valor_mp10))
			{
				aciertos += 1;

				ValidacionFAM::guardarAciertos(prediccion, valor_mp10);
			}

			acertividad = (aciertos / registro) * 100;

			progreso += 1;

			// se guarda el estado de la validacion.
			if (progreso == 100)
			{
				ValidacionFAM::guardarProgreso(registro, aciertos, acertividad);
				progreso = 0;
			}

			system("cls");
			cout << "Registro: " << registro << " Aciertos: " << aciertos << " Acertividad: " << acertividad << " Prediccion: " << prediccion << " Valor Real: " << valor_mp10  << "\n";
		}

		ValidacionFAM::guardarAcertividad(ValidacionFAM::getArchvAcertividad(), registro, aciertos, acertividad);

		// removemos el archivo de progreso ya que la validacion fue completada.
		remove(ValidacionFAM::getArchvProgreso().c_str());

		// se guarda el progreso al finalizar la validacion.
		//if (registro > 0) ValidacionFAM::guardarProgreso(registro, aciertos);
	}

	double ValidacionFAM::getEstacion(double valor)
	{
		if (valor < 2.5 && valor > 1) valor += 12;

		return valor;
	}

	double ValidacionFAM::getHora(double valor)
	{
		if (valor < 1 && valor > 0) valor += 24;

		return valor;
	}

	double ValidacionFAM::getDViento(double valor)
	{
		if (valor < 45 && valor > 0) valor += 360;

		return valor;
	}

	void ValidacionFAM::getRegistros(string archv_validacion, vector<string>& registros)
	{
		ifstream in(archv_validacion);
		string registro;

		while (getline(in, registro))
		{
			registros.push_back(registro);
		}

		in.close();
	}

	bool ValidacionFAM::getAcierto(double prediccion, double valor_real)
	{
		if (prediccion <= 150 && valor_real <= 150)
		{
			return true; // sin alerta.
		}
		else if (prediccion <= 250 && valor_real <= 250)
		{
			return true; // alerta 1.
		}
		else if (prediccion <= 350 && valor_real <= 350)
		{
			return true; // alerta 2.
		}
		else if (prediccion <= 500 && valor_real <= 500)
		{
			return true; // alerta 3.
		}
		else if (prediccion > 500 && valor_real > 500)
		{
			return true; // alerta 4.
		}

		return false;
	}

	string ValidacionFAM::getArchvAciertos()
	{
		return "aciertos.txt";
	}

	string ValidacionFAM::getArchvProgreso()
	{
		return "registros.txt";
	}

	string ValidacionFAM::getArchvAcertividad()
	{
		return "acertividad.txt";
	}

	void ValidacionFAM::getProgreso(int& registro, double& aciertos)
	{
		ifstream archivo(ValidacionFAM::getArchvProgreso().c_str());

		if (archivo.good())
		{
			string linea;

			while (getline(archivo, linea))
			{
				stringstream sep(linea);
				string valor;
				int posicion = 0;

				while (getline(sep, valor, ';') && posicion < 2)
				{
					if (posicion == 0) registro = atof(valor.c_str());
					if (posicion == 1) aciertos = atof(valor.c_str());

					posicion += 1;
				}
			}

			archivo.close();
		}
	}

	void ValidacionFAM::guardarAciertos(double prediccion, double valor_real)
	{
		ofstream archv_aciertos;
		archv_aciertos.open(ValidacionFAM::getArchvAciertos().c_str(), fstream::in | fstream::out | fstream::app);
		archv_aciertos << prediccion << ";" << valor_real << "\n";
		archv_aciertos.close();
	}

	void ValidacionFAM::guardarProgreso(double registro, double aciertos, double acertividad)
	{
		guardarAcertividad("progreso.txt", registro, aciertos, acertividad);
	}

	void ValidacionFAM::guardarAcertividad(string archivo, double registro, double aciertos, double acertividad)
	{
		ofstream in;
		in.open(archivo);
		in << registro << ";" << aciertos << ";" << acertividad;
		in.close();
	}


	void ValidacionFAM::variables(vector<string>& variables)
	{
		variables.push_back("estacion");
		variables.push_back("hora");
		variables.push_back("velocidad_viento");
		variables.push_back("direccion_viento");
		variables.push_back("temperatura");
		variables.push_back("humedad_relativa");
		variables.push_back("radiacion_solar");
		variables.push_back("precipitacion_dia1");
		variables.push_back("precipitacion_dia2");
		variables.push_back("precipitacion_dia3");
		variables.push_back("precipitacion_dia4");
		variables.push_back("precipitacion_dia5");
		variables.push_back("evaporacion");
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