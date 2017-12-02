#pragma once

#ifndef __REGLAS_H__
#define __REGLAS_H__

#include <string>
#include <vector>
#include <map>
#include <utility>
#include "VariableLinguistica.h"

using namespace std;
using namespace LogicaDifusa;

namespace Datos
{
	class Reglas
	{
	public:
		static void variables(vector<pair<string, pair<double, double>>>& variables);

		static void extraccionReglas(string archivo, vector<string>& reglas, bool desnormalizar = true);

		static void leerReglas(string archivo, vector<string>& reglas);

		static void guardarReglas(string archivo, vector<string>& reglas);

		static void setValoresVariable(double comienzo, double espacio, int num_nrns, double*& valores_variable);

		static void setValoresVariables(map<string, VariableLinguistica*>& vars, double porcentaje, int& num_nrns, map<string, double*>& valores_variables);

		static double getValorNeurona(double*& valores_variable, int num_nrns, double valor_entrada);

		// obtiene la estación con un ajuste aplicado.
		static double getEstacion(double valor);

		// obtiene la hora con un ajuste aplicado.
		static double getHora(double valor);

		// obtiene la direccion del viento con un ajuste aplicado.
		static double getDViento(double valor);
	};
}

#endif