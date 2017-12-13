#include "stdafx.h"
#include "ExtraccionReglas.h"

using namespace std;

namespace ConsolaFAM
{
	void ExtraccionReglas::ejecutar(string carpeta_archivos, int num_nrns)
	{
		string archv_reglas[] = { "sa.pynoess", "a1.pynoess", "a2.pynoess", "a3.pynoess", "a4.pynoess" };
		string archv_reglas_activadas[] = { "a_sa.pynoess", "a_a1.pynoess", "a_a2.pynoess", "a_a3.pynoess", "a_a4.pynoess" };
		string archv_datos[] = { "sa.csv", "a1.csv", "a2.csv", "a3.csv", "a4.csv" };
		string carpeta_extraccion = carpeta_archivos + "\\_extraccion";
		string archv_progreso = carpeta_extraccion + "\\progreso_extraccion.pynoess";
		int size = (sizeof(archv_reglas) / sizeof(*archv_reglas));
		int progreso = 0;

		ifstream in(archv_progreso.c_str());

		// si existiera, obtenemos en que tipo de alerta se estaban extrayendo las reglas previamente.
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
			cout << "Extraccion reglas " << (i * 20) << "%\n";
			ValidacionFAM* validacion = new ValidacionFAM(carpeta_extraccion, archv_datos[i], archv_reglas[i], archv_reglas_activadas[i]);

			validacion->ejecutar(num_nrns);

			delete validacion;

			in_progreso.open(archv_progreso);
			in_progreso << i;
			in_progreso.close();

			system("cls");
		}

		remove(archv_progreso.c_str());

		ExtraccionReglas::generarArchvReglas(carpeta_archivos, archv_reglas_activadas, size);

		cout << "Extraccion reglas 100%\n";
	}

	void ExtraccionReglas::generarArchvReglas(string carpeta_archivos, string archv_reglas[], int num_archvs)
	{
		string archv_final = carpeta_archivos + "\\reglas.pynoess";
		ofstream in_final;
		in_final.open(archv_final);

		for (int i = 0; i < num_archvs; i++)
		{
			string archv_activadas = carpeta_archivos + "\\_extraccion\\" + archv_reglas[i];
			ifstream in(archv_activadas.c_str());

			if (in.good())
			{
				string linea;

				while (getline(in, linea))
				{
					in_final << linea << "\n";
				}

				in.close();
			}
		}

		in_final.close();
	}
}