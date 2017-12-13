#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "VariablesLinguisticas.h"
#include "Reglas.h"
#include "ValidacionFAM.h"

using namespace std;
using namespace Datos;

namespace ValidacionRNA
{
	ValidacionFAM::ValidacionFAM(string carpeta_archivos, string archivo_validacion, string archivo_reglas, string archivo_activadas)
	{
		carpeta = carpeta_archivos;
		archv_reglas = carpeta + "\\" + archivo_reglas;
		archv_validacion = carpeta + "\\" + archivo_validacion;
		archv_progreso = carpeta + "\\progreso.pynoess";
		archv_aciertos = carpeta + "\\aciertos.pynoess";
		archv_acertividad = carpeta + "\\acertividad.pynoess";

		if (archivo_activadas != "")
		{
			debug_sfam = true;
			archv_reglas_activadas = carpeta + "\\" + archivo_activadas;
			archv_progreso_activaciones = carpeta + "\\progreso_activadas.pynoess";
		}
		else
		{
			debug_sfam = false;
			archv_reglas_activadas = "";
			archv_progreso_activaciones = "";
		}
		
		getRegistros(archv_validacion, registros);
	}

	ValidacionFAM::~ValidacionFAM()
	{
		delete sfam;
		vector<string>().swap(registros);
	}


	void ValidacionFAM::ejecutar(int neuronas, bool mostrar_progreso)
	{
		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		variableslinguisticas->getVariables(vars);
		vector<string> orden_vars;
		ValidacionFAM::variables(orden_vars);
		vector<string> reglas;
		Reglas::leerReglas(archv_reglas, reglas);
		vector<pair<int, int>> activaciones_reglas;
		int progreso = 0;
		int respaldo = 1;
		double registro = 1;
		double aciertos_alerta = 0;
		double aciertos_nivel = 0;
		double acertividad_alerta = 0;
		double acertividad_nivel = 0;
		int linea_actual = 0;

		// borramos los aciertos de ejecuciones anteriores.
		remove(archv_aciertos.c_str());

		// cargamos el progreso previo si existiera alguno.
		getProgreso(respaldo, aciertos_alerta, acertividad_alerta, aciertos_nivel, acertividad_nivel);

		sfam = new SistemaFAM(debug_sfam);

		// agregamos las variables linguisticas al Sistema FAM.
		setVariables(vars, neuronas);

		// agregamos las reglas al Sistema FAM.
		setReglas(reglas);

		// de ser necesario, cargamos las reglas activadas previamente.
		if (debug_sfam)
		{
			//sfam->getActivacionesReglas(activaciones_reglas);
			getProgresoActivaciones(activaciones_reglas);

			if (activaciones_reglas.size() > 0)
			{
				//cout << "Progreso\n";
				sfam->setActivacionesReglas(activaciones_reglas);
			}
			else
			{
				//cout << "Sin Progreso\n";
				sfam->setActivacionesReglas();
			}
		}

		map<string, double> entrada;

		// recorremos los registros.
		for (int i = respaldo; i <= registros.size(); i++) {
			registro = i;
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
			
			actualizarAciertos(prediccion, valor_mp10, aciertos_alerta, aciertos_nivel);

			acertividad_alerta = (aciertos_alerta / registro) * 100;
			acertividad_nivel = (aciertos_nivel / registro) * 100;

			progreso += 1;

			// se guarda el estado de la validacion.
			if (progreso == 100)
			{
				guardarProgreso(registro, aciertos_alerta, acertividad_alerta, aciertos_nivel, acertividad_nivel);

				if (debug_sfam) guardarProgresoActivaciones(activaciones_reglas);
				
				progreso = 0;
			}

			if (debug_sfam) sfam->getActivacionesReglas(activaciones_reglas);

			if (mostrar_progreso)
			{
				system("cls");
				cout << "Registro: " << registro << " \nAciertos Alerta: " << aciertos_alerta << " \nAsertividad Alerta: " << acertividad_alerta << "% \nAciertos Nivel: " << aciertos_nivel << " \nAsertividad Nivel: " << acertividad_nivel << "% \nPrediccion: " << prediccion << " \nValor Real: " << valor_mp10 << "\n";
			}
		}

		guardarAcertividad(archv_acertividad, registro, aciertos_alerta, acertividad_alerta, aciertos_nivel, acertividad_nivel);

		// removemos el archivo de progreso ya que la validacion fue completada.
		remove(archv_progreso.c_str());
		remove(archv_progreso_activaciones.c_str());

		if (debug_sfam)
		{
			guardarReglasActivadas(reglas, activaciones_reglas);
		}

		aser_alerta = acertividad_alerta;
		aser_nivel = acertividad_nivel;

		//delete sfam;

		// se guarda el progreso al finalizar la validacion.
		//if (registro > 0) ValidacionFAM::guardarProgreso(registro, aciertos);
	}

	void ValidacionFAM::ordenarReglasActivacion(vector<pair<int, int>>& activaciones)
	{
		sort(activaciones.begin(), activaciones.end(), ValidacionFAM::compararActivacion);
	}

	bool ValidacionFAM::compararActivacion(pair<int, int>& primer_elemento, pair<int, int>& segundo_elemento)
	{
		return primer_elemento.second > segundo_elemento.second;
	}

	void ValidacionFAM::setVariables(map<string, VariableLinguistica*>& vars, int neuronas)
	{
		double porcentaje = (100.0 / neuronas) / 100.0;

		for (map<string, VariableLinguistica*>::iterator var = vars.begin(); var != vars.end(); ++var)
		{
			double espacio = (var->second->getMaximo() - var->second->getMinimo()) * porcentaje;
			int num_nrns = ((var->second->getMaximo() - var->second->getMinimo()) / espacio) + 1;

			double comienzo = var->second->getMinimo() /*+ espacio*/;
			//double comienzo = 0;

			sfam->agregarVariable(var->second);
			sfam->agregarValoresVariable(var->second->getNombre(), comienzo, espacio, num_nrns);
		}
	}

	void ValidacionFAM::setReglas(vector<string>& reglas)
	{
		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
			sfam->agregarRegla(*regla);
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

	string ValidacionFAM::getAlerta(double nivel_mp10)
	{
		string alerta = "";

		if (nivel_mp10 >= 0 && nivel_mp10 <= 150)
		{
			alerta = "sin_alerta";
		}
		else if (nivel_mp10 > 150 && nivel_mp10 <= 250)
		{
			alerta = "alerta_1";
		}
		else if (nivel_mp10 > 250 && nivel_mp10 <= 350)
		{
			alerta = "alerta_2";
		}
		else if (nivel_mp10 > 350 && nivel_mp10 <= 500)
		{
			alerta = "alerta_3";
		}
		else if (nivel_mp10 > 500)
		{
			alerta = "alerta_4";
		}

		return alerta;
	}


	bool ValidacionFAM::getAciertoAlerta(double prediccion, double valor_real)
	{
		string alerta_prediccion = getAlerta(prediccion);
		string alerta_real = getAlerta(valor_real);

		if (alerta_prediccion == alerta_real) return true;

		return false;
	}

	bool ValidacionFAM::getAciertoNivel(double prediccion, double valor_real)
	{
		double distancia = 50;
		double acierto = false;
		
		if (prediccion == valor_real)
		{
			acierto = true;
		}
		else if (prediccion < valor_real)
		{
			if (prediccion >= (valor_real - 50)) acierto = true;
		} else if (prediccion > valor_real)
		{
			if (prediccion <= (valor_real + 50)) acierto = true;
		}

		return acierto;
	}

	void ValidacionFAM::getProgreso(int& registro, double& aciertos_alerta, double& acertividad_alerta, double& aciertos_nivel, double& acertividad_nivel)
	{
		ifstream in(archv_progreso.c_str());

		if (in.good())
		{
			string linea;

			while (getline(in, linea))
			{
				stringstream sep(linea);
				string valor;
				int posicion = 0;

				while (getline(sep, valor, ';') && posicion < 5)
				{
					if (posicion == 0) registro = atof(valor.c_str());
					if (posicion == 1) aciertos_alerta = atof(valor.c_str());
					if (posicion == 3) acertividad_alerta = atof(valor.c_str());
					if (posicion == 4) aciertos_nivel = atof(valor.c_str());
					if (posicion == 5) acertividad_nivel = atof(valor.c_str());

					posicion += 1;
				}
			}

			in.close();
		}
	}

	void ValidacionFAM::getProgresoActivaciones(vector<pair<int, int>>& activaciones)
	{
		ifstream in(archv_progreso_activaciones.c_str());

		if (in.good())
		{
			string linea;

			while (getline(in, linea))
			{
				stringstream sep(linea);
				string valor;
				int posicion = 0;
				int id_regla = 0;
				int activaciones_regla = 0;

				while (getline(sep, valor, ';') && posicion < 2)
				{
					if (posicion == 0) id_regla = atoi(valor.c_str());
					if (posicion == 1) activaciones_regla = atoi(valor.c_str());

					posicion += 1;
				}

				activaciones.push_back(make_pair(id_regla, activaciones_regla));
			}

			in.close();
		}
	}

	double ValidacionFAM::getAsertividadAlerta()
	{
		return aser_alerta;
	}

	double ValidacionFAM::getAsertividadNivel()
	{
		return aser_nivel;
	}

	void ValidacionFAM::actualizarAciertos(double prediccion, double valor_real, double& aciertos_alerta, double& aciertos_nivel)
	{
		bool acierto_alerta = getAciertoAlerta(prediccion, valor_real);
		bool acierto_nivel = getAciertoNivel(prediccion, valor_real);
		string tipo = "";

		if (acierto_alerta || acierto_nivel)
		{
			if (acierto_alerta)
			{
				aciertos_alerta += 1;
				tipo += "Alerta";
			}

			if (acierto_nivel)
			{
				aciertos_nivel += 1;
				tipo += "-Nivel";
			}

			ofstream archivo;
			archivo.open(archv_aciertos.c_str(), fstream::in | fstream::out | fstream::app);
			archivo << prediccion << ";" << valor_real << ";" << tipo << "\n";
			archivo.close();
		}
	}

	void ValidacionFAM::guardarProgreso(double registro, double aciertos_alerta, double acertividad_alerta, double aciertos_nivel, double acertividad_nivel)
	{
		guardarAcertividad(archv_progreso, registro, aciertos_alerta, acertividad_alerta, aciertos_nivel, acertividad_nivel);
	}

	void ValidacionFAM::guardarAcertividad(string archivo, double registro, double aciertos_alerta, double acertividad_alerta, double aciertos_nivel, double acertividad_nivel)
	{
		ofstream in;
		in.open(archivo);
		in << registro << ";" << aciertos_alerta << ";" << acertividad_alerta << ";" << aciertos_nivel << ";" << acertividad_nivel;
		in.close();
	}

	void ValidacionFAM::guardarProgresoActivaciones(vector<pair<int, int>>& activaciones)
	{
		ofstream in;
		in.open(archv_progreso_activaciones);

		for (vector<pair<int, int>>::iterator activacion = activaciones.begin(); activacion != activaciones.end(); ++activacion)
		{
			in << activacion->first << ";" << activacion->second << "\n";
		}

		in.close();
	}

	void ValidacionFAM::guardarReglasActivadas(vector<string>& reglas, vector<pair<int, int>>& activaciones, int limite_reglas)
	{
		int regla_actual = 0;
		ofstream in;
		in.open(archv_reglas_activadas);

		ValidacionFAM::ordenarReglasActivacion(activaciones);

		if (limite_reglas == 0) limite_reglas = activaciones.size();

		//cout << "Tamaño activaciones: " << activaciones.size() << "\n";

		for (vector<pair<int, int>>::iterator activacion = activaciones.begin(); activacion != activaciones.end() && regla_actual < limite_reglas; ++activacion)
		{
			if (activacion->second > 0)
			{
				//cout << "Regla " << activacion->first << " Activaciones: " << activacion->second << "\n";

				in << reglas.at(activacion->first) << "\n";
				regla_actual += 1;
			}
		}
		
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