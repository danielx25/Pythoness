// ConsolaFAM.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "ValidacionFAM.h"
#include "Validacion.h"
#include "ExtraccionReglas.h"

using namespace std;
using namespace ValidacionRNA;
using namespace ConsolaFAM;

int main(int argc, char* argv[])
{
	/*string modo(argv[1]);
	string carpeta_archivos(argv[2]);
	int num_nrns = atoi(argv[3]);*/

	string modo = "-v";
	string carpeta_archivos = "_FAM";
	int num_nrns = 10;

	/*string archv_validacion("validacion.csv");
	string archv_reglas("reglas.txt");
	int num_nrns = atoi("10");*/

	//cout << archv_reglas << " " << archv_validacion << " " << num_nrns << "\n";


	if (modo == "-v")
	{
		Validacion::ejecutar(carpeta_archivos, num_nrns);
	}
	else if (modo == "-e")
	{
		ExtraccionReglas::ejecutar(carpeta_archivos, num_nrns);
	}

	system("pause");

    return 0;
}
