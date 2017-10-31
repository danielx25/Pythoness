#pragma once

#ifndef __REGLAS_H__
#define __REGLAS_H__

#include <string>
#include <vector>

using namespace std;

namespace Datos
{
	class Reglas
	{
	public:
		static void variables(vector<string>& variables);

		static void extraccionReglas(string archivo, vector<string>& reglas);

		static void leerReglas(string archivo, vector<string>& reglas);

		static void guardarReglas(string archivo, vector<string>& reglas);
	};
}

#endif