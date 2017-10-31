#include "stdafx.h"
#include <iostream>
#include "PruebasReglas.h"
#include "Reglas.h"

using namespace std;
using namespace Datos;

namespace PruebasReglasFAM
{
	PruebasReglas::PruebasReglas()
	{
		string archivo = "C:\\Users\\Sefirot\\Documents\\Visual Studio 2015\\Projects\\Pythoness\\Debug\\pesosRNA.csv";
		vector<string> reglas;

		Reglas::extraccionReglas(archivo, reglas);
		Reglas::guardarReglas("reglas.txt", reglas);
		//for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla) cout << *regla << "\n";

		cout << "Something\n";
	}
}