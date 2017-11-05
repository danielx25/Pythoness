// Pruebas.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include "PruebasFAM.h"
#include "PruebasSFAM.h"
#include "PruebasLD.h"
#include "PruebasReglas.h"
#include "PruebasMP10.h"

using namespace PruebasRed;
using namespace PruebasLogicaDifusa;
using namespace PruebasReglasFAM;
using namespace PruebasMP;

int main()
{
	//PruebasFAM();
	//PruebasSFAM();
	//PruebasLD();
	PruebasReglas();
	//PruebasMP10();

	int tecla;
	
	std::cin >> tecla;

    return 0;
}

