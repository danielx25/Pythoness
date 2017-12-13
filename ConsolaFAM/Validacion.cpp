#include "stdafx.h"
#include "Validacion.h"

using namespace std;

namespace ConsolaFAM
{
	void Validacion::ejecutar(string carpeta_archivos, int num_nrns)
	{
		string archv_datos[] = { "validacion_1.csv", "validacion_2.csv", "validacion_3.csv" };
		string archv_reglas = "reglas.pynoess";
		string archv_progreso = carpeta_archivos + "\\progreso_validacion.pynoess";
		int size = (sizeof(archv_datos) / sizeof(*archv_datos));
		int progreso = 0;
		double alerta_final = 0;
		double nivel_final = 0;

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

			alerta_final += validacion->getAsertividadAlerta();
			nivel_final += validacion->getAsertividadNivel();

			if (i == 0) cout << "Resultados Primer Tercio (1 nov 2014 - 28 feb 2017)\n";
			if (i == 1) cout << "Resultados Segundo Tercio (1 jun 2012 - 31 oct 2014)\n";
			if (i == 2) cout << "Resultados Tercer Tercio (1 ene 2010 - 31 may 2012)\n";
			
			cout << "\n";

			system("pause");

			delete validacion;
		}

		alerta_final /= 3;
		nivel_final /= 3;

		system("cls");
		cout << "¡Validacion terminada!\n\n";
		cout << "Resultado Final\n\nAsertividad Alerta: " << alerta_final << "% \nAsertividad Nivel: " << nivel_final << "%\n\n";

		remove(archv_progreso.c_str());
	}
}