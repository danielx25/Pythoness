#pragma once

#ifndef __DISCRETIZACION_H__
#define __DISCRETIZACION_H__

#include <string>

using namespace std;

namespace Datos
{
	class Discretizacion
	{
	public:
		static void pesos(string archv_pesos, string archv_salida);

		static void valoresVariables(string archv_salida);
	};
}

#endif