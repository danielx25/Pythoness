#include "stdafx.h"
#include "Validacion.h"

using namespace std;

namespace ConsolaFAM
{
	void Validacion::ejecutar(string carpeta_archivos, int num_nrns)
	{
		string archv_datos[] = { "validacion_1.csv", "validacion_2.csv", "validacion_3.csv" };
		string archv_reglas = carpeta_archivos + "\\reglas.pynoess";
		string archv_progreso = carpeta_archivos + "\\progreso_validacion.pynoess";
		int size = (sizeof(archv_datos) / sizeof(*archv_datos));
		int progreso = 0;

		ifstream in(archv_progreso.c_str());

		// si existiera, obtenemos en que validacion estaba previamente.
		if (in.good())
		{
			string linea;

			while (getline(in, linea))
			{
				progreso = atoi(linea.c_str()) + 1;
			}

			in.close();
		}

		ofstream in_progreso;

		for (int i = progreso; i < size; i++)
		{
			ValidacionFAM* validacion = new ValidacionFAM(carpeta_archivos, archv_datos[i], archv_reglas);

			validacion->ejecutar(num_nrns, true);

			in_progreso.open(archv_progreso);
			in_progreso << i;
			in_progreso.close();

			system("pause");

			delete validacion;
		}

		remove(archv_progreso.c_str());
	}
}