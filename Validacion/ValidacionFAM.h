#pragma once

#include <string>
#include <vector>
#include "VariableLinguistica.h"
#include "SistemaFAM.h"

using namespace std;
using namespace LogicaDifusa;
using namespace STMFAM;

namespace ValidacionRNA
{
	class ValidacionFAM
	{
	public:
		void static validacionFAM(string archv_validacion, string archv_reglas, int num_nrns);

		// obtiene la estación con un ajuste aplicado.
		static double getEstacion(double valor);

		// obtiene la hora con un ajuste aplicado.
		static double getHora(double valor);

		// obtiene la direccion del viento con un ajuste aplicado.
		static double getDViento(double valor);

		static void getRegistros(string archv_validacion, vector<string>& registros);

		static bool getAcierto(double prediccion, double valor_real);

		static string getArchvAciertos();

		static string getArchvProgreso();

		static string getArchvAcertividad();

		static void getProgreso(int& registro, double& aciertos);

		static void guardarAciertos(double prediccion, double valor_real);

		static void guardarProgreso(double registro, double aciertos, double acertividad);

		// guarda wl numero de registros, aciertos y la acertividad final.
		static void guardarAcertividad(string archivo, double registro, double aciertos, double acertividad);

		static void variables(vector<string>& variables);
	};
}
