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
		static void datos(int neuronas, string archv_datos, string archv_salida, bool desnormalizar = false);

		static void valoresVariables(string archv_salida);
	};
}

#endif