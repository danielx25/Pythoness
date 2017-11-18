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
	//Discretizacion::pesos("pesosRNA.csv", "datosID3.csv");
	//Discretizacion::valoresVariables("valores_variables.csv");
	//PruebasMP10();
	PruebasMP10::validacion();

	cout << "\nPrueba Finalizada\n";

	int tecla;
	
	std::cin >> tecla;

    return 0;
}

