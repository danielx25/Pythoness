#include "stdafx.h"
#include <math.h>
#include <iostream>
#include "BP.h"

namespace RedNeuronal
{
	BP::BP(int nc, int* nnc, double t, double m, double a, double b) : RNA(nc, nnc, t)
	{
		momentum = m;
		th_a = a;
		th_b = b;

		error = 0;
		errores = new double[num_nrns_capas[num_capas - 1]];
		gradiantes = new double[num_total_nrns];
		deltas = new double*[num_total_nrns];

		// iniciamos los errores de las neuronas de salida en cero.
		for (int i = 0; i < num_nrns_capas[num_capas - 1]; i++)
			errores[i] = 0;

		// iniciamos todas las neuronas sin salida y sin ninguna conexion.
		for (int i = 0; i < num_total_nrns; i++)
		{
			gradiantes[i] = 0;
			deltas[i] = new double[num_total_nrns];

			for (int j = 0; j < num_total_nrns; j++)
				deltas[i][j] = 0;
		}
	}

	BP::BP(int nc, int* nnc, double** p) : RNA(nc, nnc, 0.1) { pesos = p; }


	BP::~BP()
	{
		delete[] errores;
		delete[] deltas;
		delete[] gradiantes;
	}

	double BP::tangenteHiperbolica(double entrada_red)
	{
		return ((2 * th_a) / (1 + exp(-th_b * entrada_red))) - th_a;
	}

	// tangente hiperbolica.
	double BP::funcionActivacion(double entrada_red)
	{
		return tangenteHiperbolica(entrada_red);
	}

	double BP::gradianteError(double salida, double valor)
	{
		// salida * derivada de la tangente hiperbolica * error de la neurona de salida.
		return salida * pow(salida, 2) * valor;
	}

	double BP::deltaPeso(int idc_nrn, int idc_nrn_sig)
	{
		deltas[idc_nrn][idc_nrn_sig] = tasa_aprdj * salidas[idc_nrn] * gradiantes[idc_nrn_sig];

		return deltas[idc_nrn][idc_nrn_sig];
	}

	void BP::calcularErrores(double* salida_deseada)
	{
		int idc_pr_nrn = getPrimeraNeurona(num_capas - 1);
		int idc_ult_nrn = getUltimaNeurona(num_capas - 1);

		for (int i = idc_pr_nrn; i <= idc_ult_nrn; i++)
			setError(i, salida_deseada[getIdcNrnSalida(i)] - salidas[i]);
	}

	void BP::setErrores(double* errores)
	{
		int idc_pr_nrn = getPrimeraNeurona(num_capas - 1);
		int idc_ult_nrn = getUltimaNeurona(num_capas - 1);

		for (int i = idc_pr_nrn; i <= idc_ult_nrn; i++)
			setError(i, errores[getIdcNrnSalida(i)]);
	}

	double BP::getSumGradiante(int idc_nrn, int idc_capa)
	{
		int idc_pr_nrn = getPrimeraNeurona(idc_capa);
		int idc_ult_nrn = getUltimaNeurona(idc_capa);
		double sum_gradiante = 0;

		// cada gradiante se multiplica por el peso de la conexion.
		for (int i = idc_pr_nrn; i < idc_ult_nrn; i++)
			sum_gradiante += gradiantes[i] * pesos[idc_nrn][i];

		return sum_gradiante;
	}


	void BP::calcularGradiantes()
	{
		for (int capa = (num_capas - 1); capa > 0; capa--)
		{
			int idc_pr_nrn = getPrimeraNeurona(capa);
			int idc_ult_nrn = getUltimaNeurona(capa);

			for (int i = idc_pr_nrn; i <= idc_ult_nrn; i++)
			{
				double coeficiente = 0;

				if (capa == (num_capas - 1))
					coeficiente = getError(i);
				else if (capa < (num_capas - 1))
					coeficiente = getSumGradiante(i, capa + 1);

				gradiantes[i] = gradianteError(salidas[i], coeficiente);
			}
		}
	}

	void BP::ajustarPeso(int idc_nrn, int idc_capa)
	{
		int idc_pr_nrn = getPrimeraNeurona(idc_capa + 1); // capa anterior.
		int idc_ult_nrn = getUltimaNeurona(idc_capa + 1); // capa anterior.

		for (int i = idc_pr_nrn; i <= idc_ult_nrn; i++)
		{
			double delta = deltaPeso(idc_nrn, i);
			//std::cout << "Peso " << pesos[idc_nrn][i] << " delta " << delta << " ";
			pesos[idc_nrn][i] += deltaPeso(idc_nrn, i);
			//std::cout << "peso ajustado" << pesos[idc_nrn][i] << "\n";
		}
	}

	void BP::aprendizaje()
	{
		for (int capa = 0; capa < num_capas; capa++)
		{
			int idc_pr_nrn = getPrimeraNeurona(capa);
			int idc_ult_nrn = getUltimaNeurona(capa);

			for (int idc_nrn = idc_pr_nrn; idc_nrn <= idc_ult_nrn; idc_nrn++)
				ajustarPeso(idc_nrn, capa);
		}
	}

	double* BP::ejecutar(double* patron)
	{
		double* nrns_salida = new double[num_nrns_capas[num_capas - 1]];
		int idc_pr_nrn = getPrimeraNeurona(num_capas - 1);
		int idc_ult_nrn = getUltimaNeurona(num_capas - 1);

		setEntrada(patron);
		calcularSalidas();

		int nrn_salida = 0;
		for (int idc_nrn = idc_pr_nrn; idc_nrn < idc_ult_nrn; idc_nrn++)
		{
			nrns_salida[nrn_salida] = salidas[idc_nrn];
			nrn_salida += 1;
		}

		return nrns_salida;
	}

	void BP::setError(int idc_nrn, double error) { errores[getIdcNrnSalida(idc_nrn)] = error; }
	
	double BP::getError(int idc_nrn) const { return errores[getIdcNrnSalida(idc_nrn)]; }

	double BP::getError() const { return error; }

	double* BP::getErrores() const { return errores; }

	double** BP::getDeltas() const { return deltas; }

	double* BP::getGradiantes() const { return gradiantes; }

	double BP::getSumErr2()
	{
		double sum_err2 = 0;

		return sum_err2;
	}

	int BP::getIdcNrnSalida(int idc_nrn) const
	{
		int idc_pr_nrn = getPrimeraNeurona(num_capas - 1);

		return idc_nrn - idc_pr_nrn;
	}

}