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
	class Validacion
	{
	public:
		static void ejecutar(string carpeta_archivos, int num_nrns);
	};
}