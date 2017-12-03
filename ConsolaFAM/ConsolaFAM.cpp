// ConsolaFAM.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include "ValidacionFAM.h"

using namespace std;
using namespace ValidacionRNA;

int main(int argc, char* argv[])
{
	string carpeta_archivos(argv[1]);
	int num_nrns = atoi(argv[2]);

	/*string archv_validacion("validacion.csv");
	string archv_reglas("reglas.txt");
	int num_nrns = atoi("10");*/

	//cout << archv_reglas << " " << archv_validacion << " " << num_nrns << "\n";

	ValidacionFAM::validacionFAM(carpeta_archivos, num_nrns);

	system("pause");

    return 0;
}

