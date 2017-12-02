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
	string archv_validacion(argv[1]);
	string archv_reglas(argv[2]);
	int num_nrns = atoi(argv[3]);

	/*string archv_validacion("validacion.csv");
	string archv_reglas("reglas.txt");
	int num_nrns = atoi("10");*/

	//cout << archv_reglas << " " << archv_validacion << " " << num_nrns << "\n";

	ValidacionFAM::validacionFAM(archv_validacion, archv_reglas, num_nrns);

	system("pause");

    return 0;
}

