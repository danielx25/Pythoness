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
		void static validacionFAM(string carpeta_archivos, int num_nrns);

		// obtiene la estación con un ajuste aplicado.
		static double getEstacion(double valor);

		// obtiene la hora con un ajuste aplicado.
		static double getHora(double valor);

		// obtiene la direccion del viento con un ajuste aplicado.
		static double getDViento(double valor);

		static void getRegistros(string archv_validacion, vector<string>& registros);

		static string getAlerta(double nivel_mp10);

		static bool getAciertoAlerta(double prediccion, double valor_real);

		static string getArchvReglas(string carpeta_archivos);
		
		static string getArchvValidacion(string carpeta_archivos);

		static string getArchvAciertos(string carpeta_archivos);

		static string getArchvProgreso(string carpeta_archivos);

		static string getArchvAcertividad(string carpeta_archivos);

		static void getProgreso(string archivo, int& registro, double& aciertos);

		static void guardarAciertos(string archivo, double prediccion, double valor_real);

		static void guardarProgreso(string archivo, double registro, double aciertos, double acertividad);

		// guarda wl numero de registros, aciertos y la acertividad final.
		static void guardarAcertividad(string archivo, double registro, double aciertos, double acertividad);

		static void variables(vector<string>& variables);
	};
}
