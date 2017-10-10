#include "stdafx.h"
#include <iostream>
#include "PruebasFAM.h"

using namespace std;

namespace PruebasRed
{
	PruebasFAM::PruebasFAM()
	{
		int nna = 6;
		int nnb = 5;
		double* a = new double[nna];
		double* b = new double[nnb];
		double** pesos;
		double* e = new double[nna];
		double* s;

		a[0] = .0; a[1] = .17; a[2] = .67; a[3] = .83, a[4] = .33, a[5] = .0;
		b[0] = .0; b[1] = .62; b[2] = 1; b[3] = .62, b[4] = .0;
		
		e[0] = 0; e[1] = 1; e[2] = 0; e[3] = 0, e[4] = 0, e[5] = 0;

		red = new FAM(a, nna, b, nnb);

		red->getPesos(pesos);
		red->getSalidaB(e, s);

		cout << "Pesos\n";
		imprimirMatriz(pesos, nna, nnb);
		cout << "\nSalida\n";
		imprimirArray(s, nnb);
	}

	void PruebasFAM::imprimirMatriz(double**& matriz, int filas, int cols)
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

	void PruebasFAM::imprimirArray(double*& arr, int cols)
	{
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int j = 0; j < cols; j++)
			cout << arr[j] << " ";

		cout << "\n";
	}
}