#pragma once

#ifndef __REGLAS_H__
#define __REGLAS_H__

#include <string>
#include <vector>
#include <utility>

using namespace std;

namespace Datos
{
	class Reglas
	{
	public:
		static void variables(vector<pair<string, pair<double, double>>>& variables);

		static void extraccionReglas(string archivo, vector<string>& reglas, bool desnormalizar = true);

		static void leerReglas(string archivo, vector<string>& reglas);

		static void guardarReglas(string archivo, vector<string>& reglas);

		// obtiene la estación con un ajuste aplicado.
		static double getEstacion(double valor);

		// obtiene la hora con un ajuste aplicado.
		static double getHora(double valor);

		// obtiene la direccion del viento con un ajuste aplicado.
		static double getDViento(double valor);
	};
}

#endif