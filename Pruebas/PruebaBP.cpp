#include "stdafx.h"
#include <iostream>
#include "PruebaBP.h"

using namespace std;

namespace PruebasRed
{
	PruebaBP::PruebaBP()
	{
		nc = 4;
		nnc = new int[nc];
		t = .1;
		
		nnc[0] = 3;
		nnc[1] = 4;
		nnc[2] = 3;
		nnc[3] = 2;

		double* patron = new double[nnc[0]];

		patron[0] = 0.12;
		patron[1] = 0.51;
		patron[2] = 0.26;

		red = new BP(nc, nnc, t);

		red->setEntrada(patron);
		inicializacion();
		iniciarPesos();
		infoCapas();
		calcularSalidas();

		int tecla;
		cin >> tecla;

		delete red;
	}

	void PruebaBP::inicializacion()
	{
		cout << "Pesos\n\n";
		imprimirMatriz(red->getPesos(), red->getNumTotalNrns(), red->getNumTotalNrns());
		cout << "\nSalidas\n\n";
		imprimirArray(red->getSalidas(), red->getNumTotalNrns());
		cout << "\nDeltas\n\n";
		imprimirArray(red->getDeltas(), red->getNumTotalNrns());
		cout << "\nGradiantes\n\n";
		imprimirArray(red->getGradiantes(), red->getNumTotalNrns());
		cout << "\nErrores\n\n";
		imprimirArray(red->getErrores(), 2);
	}

	void PruebaBP::infoCapas()
	{
		cout << "\n";

		for (int i = 0; i < nc; i++)
			cout << "Capa " << i << " desde neurona " << red->getPrimeraNeurona(i) << " hasta neurona " << red->getUltimaNeurona(i) << "\n";
	}

	void PruebaBP::iniciarPesos()
	{
		double max = 2.4 / red->getNumNrnsCapas()[0];

		red->iniciarPesos(-max, max);

		cout << "\nPesos aleatorios Min:" << -max << " Max:" << max << "\n\n";
		imprimirMatriz(red->getPesos(), red->getNumTotalNrns(), red->getNumTotalNrns());
	}

	void PruebaBP::calcularSalidas()
	{
		red->calcularSalidas();

		cout << "\nSalidas\n\n";
		imprimirArray(red->getSalidas(), red->getNumTotalNrns());
	}

	void PruebaBP::imprimirMatriz(double** matriz, int filas, int cols)
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

	void PruebaBP::imprimirArray(double* arr, int cols)
	{
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int j = 0; j < cols; j++)
			cout << arr[j] << " ";

		cout << "\n";
	}
}