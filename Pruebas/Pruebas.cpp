// Pruebas.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>
#include "PruebasFAM.h"
#include "PruebasSFAM.h"

using namespace PruebasRed;

int main()
{
	//PruebasFAM();
	PruebasSFAM();

	int tecla;
	
	std::cin >> tecla;

    return 0;
}

