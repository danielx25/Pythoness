#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "PruebasMP10.h"
#include "VariableLinguistica.h"
#include "FuncionTriangular.h"
#include "FuncionTrapezoidal.h"
#include "VariablesLinguisticas.h"
#include "Reglas.h"
#include "Normalizacion.h"
#include "ValidacionFAM.h"

using namespace std;
using namespace LogicaDifusa;
using namespace Datos;
using namespace ValidacionRNA;

namespace PruebasMP
{
	void PruebasMP10::validacion()
	{
		string archv_validacion = "validacion.csv";
		string archv_reglas = "reglas.txt";
		int num_nrns = 10;

		ValidacionFAM::validacionFAM(archv_validacion, archv_reglas, num_nrns);
	}

	void PruebasMP10::imprimirMatriz(double**& matriz, int filas, int cols)
	{
		cout << "  ";
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int i = 0; i < filas; i++)
		{
			cout << i << " ";

			for (int j = 0; j < cols; j++)
				cout << matriz[i][j] << " ";

			cout << "\n";
		}
	}

	void PruebasMP10::imprimirArray(double*& arr, int cols)
	{
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int j = 0; j < cols; j++)
			cout << arr[j] << " ";

		cout << "\n";
	}
}