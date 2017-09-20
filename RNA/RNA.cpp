#include "stdafx.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "RNA.h"

namespace RedNeuronal
{
	RNA::RNA(int nc, int *nnc, double t) : num_capas(nc), num_nrns_capas(nnc), tasa_aprdj(t)
	{
		// obtenemos el numero de neuronas;
		num_nrns = 0;
		for (int i = 0; i < nc; i++) num_nrns += num_nrns_capas[i];
		
		// inicializamos las matrices.
		num_total_nrns = num_nrns + (num_capas - 1); // se agregan los bias al numero de neuronas.
		salidas = new double[num_total_nrns];
		pesos = new double*[num_total_nrns];

		// iniciamos todas las neuronas sin salida y sin ninguna conexion.
		for (int i = 0; i < num_total_nrns; i++)
		{
			salidas[i] = 0;
			pesos[i] = new double[num_total_nrns];

			for (int j = 0; j < num_total_nrns; j++)
				pesos[i][j] = 0;
		}

		// seteamos la salida de los bias.
		for (int i = 0; i < (num_capas - 1); i++)
			salidas[getUltimaNeurona(i)] = 1;

	}

	RNA::~RNA()
	{
		for (int i = 0; i < num_total_nrns; i++)
			delete[] pesos[i];

		delete[] pesos;
		delete[] salidas;
	}

	void RNA::iniciarPesos(double min, double max)
	{
		int idc_neurona = 0;
		int idc_ultima_nr = 0;
		srand(time(NULL));

		for (int i = 0; i < (num_capas - 1); i++)
		{
			int pr_nr_capa_act = getPrimeraNeurona(i);
			int ult_nr_capa_act = getUltimaNeurona(i);

			for (int j = pr_nr_capa_act; j <= ult_nr_capa_act; j++)
			{
				int pr_nr_capa_sig = getPrimeraNeurona(i + 1);
				int ult_nr_capa_sig = getUltimaNeurona(i + 1);

				for (int k = pr_nr_capa_sig; k <= ult_nr_capa_sig; k++)
					pesos[j][k] = getRandom(min, max);
			}

			idc_neurona = idc_ultima_nr;
		}
	}

	double RNA::funcionPropagacion(int idc_capa, int idc_neurona)
	{
		double entrada_red = 0;
		int idc_ult_nrn = getUltimaNeurona(idc_capa - 1);
		int idc_pr_nrn = getPrimeraNeurona(idc_capa - 1);

		for (int i = idc_pr_nrn; i < idc_ult_nrn; i++)
			entrada_red += pesos[idc_neurona][i] * salidas[i];

		// restamos el bias.
		entrada_red -= pesos[idc_neurona][idc_ult_nrn] * salidas[idc_ult_nrn];

		return entrada_red;
	}

	double RNA::calcularSalida(double result_act)
	{
		return result_act;
	}

	void RNA::calcularSalidas()
	{
		// partimos de la segunda cap.
		for (int idc_capa = 1; idc_capa < num_capas; idc_capa++)
		{
			int idc_pr_nrn = getPrimeraNeurona(idc_capa);
			int idc_ult_nrn = getUltimaNeurona(idc_capa);
		
			for (int idc_nrn = idc_pr_nrn; idc_nrn < num_total_nrns; idc_nrn++)
				salidas[idc_nrn] = calcularSalida(funcionActivacion(funcionPropagacion(idc_capa, idc_nrn)));

			// la salida de los bias siempre son 1.
			salidas[idc_ult_nrn] = 1;
		}
			
	}

	void RNA::setEntrada(double* patron)
	{
		for (int i = 0; i < num_nrns_capas[0]; i++)
			salidas[i] = patron[i];
	}


	double* RNA::getCapa(int idc_capa) const
	{
		double* capa;
		int num_nrns_capa = num_nrns_capas[idc_capa]; // se agrega el bias.
		int idc_neurona = 0;

		if (idc_capa < (num_capas - 1))
		{
			num_nrns_capa += 1; // se agrega el bias.
			// si la capa no es la de salida obtenemos el indice de su primera neurona.
			for (int i = 0; i < idc_capa; i++)
			{
				// se agrega el bias (+1) a la cantidad de neuronas de la capa.
				idc_neurona += num_nrns_capas[idc_capa] + 1;
			}
		}
		else
		{
			// la capa de salida no tiene bias, por lo que solo restamos el n de neuronas de la capa al n total de neuronas de la red.
			idc_neurona = num_total_nrns - num_nrns_capa;
		}

		// iniciamos la capa y asignamos las salidas.
		capa = new double[num_nrns_capa];
		for (int i = idc_neurona; i < num_nrns_capa; i++)
			capa[i] = salidas[i];

		return capa;
	}

	int RNA::getPrimeraNeurona(int idc_capa) const
	{
		int idc_neurona = 0;

		if (idc_capa > 0)
		{
			for (int i = idc_capa - 1; i >= 0; i--)
				idc_neurona += num_nrns_capas[i];
			idc_neurona += idc_capa;
		}

		return idc_neurona;
	}

	int RNA::getUltimaNeurona(int idc_capa) const
	{
		int idc_neurona = 0;

		if (idc_capa == (num_capas - 1))
			idc_neurona = num_total_nrns - 1;
		else if (idc_capa < (num_capas - 1))
			idc_neurona  = getPrimeraNeurona(idc_capa) + num_nrns_capas[idc_capa];

		return idc_neurona;
	}

	double RNA::getRandom(double min, double max) const
	{
		double f = (double)rand() / double(RAND_MAX);

		return (f * (max - min)) + min;
	}

	int RNA::getNumCapas() const { return num_capas; }

	int RNA::getNumNrns() const { return num_nrns; }

	int RNA::getNumTotalNrns() const { return num_total_nrns; }

	double RNA::getTasaAprendizaje() const { return tasa_aprdj; }

	int* RNA::getNumNrnsCapas() const { return num_nrns_capas; }

	int RNA::getIteraciones() const { return ciclos; }

	double* RNA::getSalidas() const { return salidas; }

	double** RNA::getPesos() const { return pesos; }
}