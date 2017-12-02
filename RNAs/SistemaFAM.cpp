#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "SistemaFAM.h"

namespace RNAs
{
	SistemaFAM::SistemaFAM()
	{

	}

	SistemaFAM::~SistemaFAM()
	{

	}

	double SistemaFAM::getSalida()
	{
		return getSalida(entrada);
	}

	double SistemaFAM::getSalida(map<string, double>& e)
	{
		double salida = 0;
		int regla_actual = 0;
		double* suma;
		string consecuente = "mp10";

		entrada = e;

		salida_reglas = new double*[reglas.size()];

		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
		{
			map<string, string> vars;
			string val_consc;
			string operador;

			getElementosRegla(*regla, vars, consecuente, val_consc, operador);
			evaluacionRegla(vars, consecuente, val_consc, operador, salida_reglas[regla_actual]);

			regla_actual += 1;
		}

		getCapaSuma(salida_reglas, reglas.size(), num_vals_vars[consecuente], suma);
		salida = getCentroide(suma, valores_variables[consecuente], num_vals_vars[consecuente]);

		return salida;
	}
}