#include "stdafx.h"
#include "FAM.h"

namespace RedNeuronal
{
	FAM::FAM(double*& a, int nna, double*& b, int nnb)
	{
		num_nrns_a = nna;
		num_nrns_b = nnb;
		A = a;
		B = b;

		pesos = new double*[num_nrns_a];

		// iniciamos todas las neuronas sin ninguna conexion.
		for (int i = 0; i < num_nrns_a; i++)
		{
			pesos[i] = new double[num_nrns_b];

			for (int j = 0; j < num_nrns_b; j++)
				pesos[i][j] = 0;
		}

		matrizHebbDifusa(A, B, pesos);
	}

	FAM::~FAM()
	{
		delete[] A;
		delete[] B;
		
		for (int i = 0; i < num_nrns_b; i++)
			delete[] pesos[i];

		delete[] pesos;
	}

	void FAM::matrizHebbDifusa(double*& a, double*& b, double**& p)
	{
		for (int i = 0; i < num_nrns_a; i++)
		{
			for (int j = 0; j < num_nrns_b; j++)
			{
				if (A[i] < B[j]) p[i][j] = A[i];
				else p[i][j] = B[j];
			}
		}
	}

	void FAM::matrizComposicionDifusa(int filas, int columnas, double*& e, double**& p, double*& s)
	{
		for (int i = 0; i < columnas; i++)
		{
			double max = 0;

			for (int j = 0; j < filas; j++)
			{
				double min = 0;

				if (e[j] < p[j][i]) min = e[j];
				else min = p[j][i];

				if (min > max) max = min;
			}

			s[i] = max;
		}
	}

	void FAM::getSalidaB(double*& entrada_a, double*& s)
	{
		s = new double[num_nrns_b];

		matrizComposicionDifusa(num_nrns_a, num_nrns_b, entrada_a, pesos, s);
	}

	void FAM::getSalidaA(double*& entrada_b, double*& s)
	{
		s = new double[num_nrns_a];

		matrizComposicionDifusa(num_nrns_b, num_nrns_a, entrada_b, pesos, s);
	}

	void FAM::getPesos(double**& p) const { p = pesos; }
}