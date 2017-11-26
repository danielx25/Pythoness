#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "SistemaFAM.h"

namespace STMFAM
{
	/*
	Sistema FAM para un control difuso para multiples antecedentes y un solo consecuente.
	*/
	SistemaFAM::SistemaFAM() { }

	SistemaFAM::~SistemaFAM()
	{

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