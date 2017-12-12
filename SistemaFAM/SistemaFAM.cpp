#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "SistemaFAM.h"

namespace STMFAM
{
	/*
	Sistema FAM para un control difuso para multiples antecedentes y un solo consecuente.
	*/
	SistemaFAM::SistemaFAM() 
	{
		debug = false;
	}

	SistemaFAM::SistemaFAM(bool dbg)
	{
		debug = dbg;
	}


	SistemaFAM::~SistemaFAM()
	{
		/*for (int i = 0; i < reglas.size(); i++)
			delete[] salida_reglas[i];

		delete[] salida_reglas;*/

		//if (debug) vector<pair<int, int>>().swap(activaciones_reglas);
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

			// revisamos, de ser necesario, si la regla se ha activado.
			if (debug && esVerdad(salida_reglas[r], num_vals_vars[consecuente]))
			{
				//cout << "Regla " << r << "\n";
				activaciones_reglas.at(r).second += 1;
			}

			vars.erase(vars.begin(), vars.end());
		}
	}

	bool SistemaFAM::esVerdad(double*& matriz, int num_nrns)
	{
		bool verdadero = false;

		for (int i = 0; i < num_nrns && !verdadero; i++)
		{
			if (matriz[i] > 0.0)
			{
				//cout << " " << matriz[i];
				verdadero = true;
			}
		}

		return verdadero;
	}

	void SistemaFAM::setActivacionesReglas()
	{
		for (int i = 0; i < reglas.size(); i++)
			activaciones_reglas.push_back(make_pair(i, 0));
	}

	void SistemaFAM::setActivacionesReglas(vector<pair<int, int>>& activaciones)
	{
		activaciones_reglas = activaciones;
	}

	void SistemaFAM::getActivacionesReglas(vector<pair<int, int>>& activaciones)
	{
		activaciones = activaciones_reglas;
	}

	double SistemaFAM::getSalida(map<string, double>& e)
	{
		double salida = 0;
		int regla_actual = 0;
		double* suma;
		string consecuente = "mp10";

		entrada = e;

		salida_reglas = new double*[reglas.size()];

		//if (debug) setActivacionesReglas();

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

		getCapaSuma(salida_reglas, reglas.size(), num_vals_vars[consecuente], suma);
		salida = getCentroide(suma, valores_variables[consecuente], num_vals_vars[consecuente]);

		for (int i = 0; i < reglas.size(); i++)
		{
			delete[] salida_reglas[i];
		}

		delete[] salida_reglas;

		delete[] suma;

		return salida;
	}
}