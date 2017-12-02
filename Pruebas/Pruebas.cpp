// Pruebas.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include "PruebasFAM.h"
#include "PruebasSFAM.h"
#include "PruebasLD.h"
#include "PruebasReglas.h"
#include "PruebasMP10.h"
#include "Discretizacion.h"

using namespace PruebasRed;
using namespace PruebasLogicaDifusa;
using namespace PruebasReglasFAM;
using namespace PruebasMP;
using namespace Datos;

int main()
{
	//PruebasFAM();
	//PruebasSFAM();
	//PruebasLD();
	//PruebasReglas();
	//Discretizacion::datos("validacion.csv", "dataset1.csv", true);
	//Discretizacion::valoresVariables("valores_variables.csv");
	//PruebasMP10();
	PruebasMP10::validacion();

	cout << "\nPrueba Finalizada\n";

	system("pause");

    return 0;
}

