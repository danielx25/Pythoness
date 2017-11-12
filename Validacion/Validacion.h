#pragma once

#include <string>
#include <vector>
#include "VariableLinguistica.h"

using namespace std;
using namespace LogicaDifusa;

namespace ValidacionRNA
{
	class Validacion
	{
	public:
		static void validacionFAM(string archv_validacion, string archv_reglas);

		// obtiene la estación con un ajuste aplicado.
		static double getEstacion(double valor);

		// obtiene la hora con un ajuste aplicado.
		static double getHora(double valor);

		// obtiene la direccion del viento con un ajuste aplicado.
		static double getDViento(double valor);

		static bool getAcierto(double prediccion, double valor_real, VariableLinguistica*& mp10);

		static void guardarProgreso(double registro, double aciertos);

		static void variables(vector<string>& variables);
	};
}
