#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "ValidacionFAM.h"

using namespace std;
using namespace ValidacionRNA;

namespace ConsolaFAM
{
	class ExtraccionReglas
	{
	public:
		static void ejecutar(string carpeta_archivos, int num_nrns);

		static void generarArchvReglas(string carpeta_archivos, string archv_reglas[], int num_archvs);
	};
}