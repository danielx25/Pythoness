#include "stdafx.h"

#include <math.h>
#include "BP.h"

namespace RedNeuronal
{
	BP::BP(int nc, int *nnc, double t, double* sd, double m = 0.95, double a = 1.716, double b = 0.667) : RNA(nc, nnc, t)
	{
		salida_deseada = sd;
		momentum = m;
		th_a = a;
		th_b = b;

		error = 0;
		errores = new double[num_nrns_capas[num_capas - 1]];
		pesos = new double*[num_total_nrns];
		gradiantes = new double[num_total_nrns];

		// iniciamos los errores de las neuronas de salida en cero.
		for (int i = 0; i < num_nrns_capas[num_capas - 1]; i++)
			errores[i] = 0;

		// iniciamos todas las neuronas sin salida y sin ninguna conexion.
		for (int i = 0; i < num_total_nrns; i++)
		{
			salidas[i] = 0;
			gradiantes[i] = 0;
			pesos[i][i] = 0;
		}
	}

	BP::~BP()
	{
		for (int i = 0; i < num_total_nrns; i++)
			delete[] pesos[i];

		delete[] pesos;
		delete[] salidas;
		delete[] deltas;
		delete[] num_nrns_capas;
	}

	// tangente hiperbolica.
	double BP::funcionActivacion(double entrada_red)
	{
		return ((2 * th_a) / (1 + exp(-th_b * entrada_red))) - th_a;
	}

	double BP::gradianteError(double salida, double error)
	{
		// salida * derivada de la tangente hiperbolica * error de la neurona de salida.
		return salida * pow(salida, 2) * error;
	}

	double BP::deltaPeso(int idc_nrn_salida, int idc_nrn_oculta)
	{
		deltas[idc_nrn_salida] = tasa_aprdj * salidas[idc_nrn_oculta] * gradianteError(salidas[idc_nrn_oculta], getError(idc_nrn_salida));

		return deltas[idc_nrn_salida];
	}

	void BP::setErrores()
	{
		int idc_pr_nrn = getPrimeraNeurona(num_capas - 1);
		int idc_ult_nrn = getUltimaNeurona(num_capas - 1);

		for (int i = idc_pr_nrn; i < idc_ult_nrn; i++)
			setError(i, salida_deseada[i] - salidas[i]);
	}

	void BP::ajustarPesosCapaSalida()
	{
		

	}

	void BP::ajustarPesosCapaOculta(int idc_capa)
	{
		int idc_pr_nrn = getPrimeraNeurona(idc_capa - 1);
		int idc_ult_nrn = getUltimaNeurona(idc_capa - 1);
		int idc_pr_nrn_co = getPrimeraNeurona(idc_capa - 2); // capa oculta.
		int idc_ult_nrn_co = getUltimaNeurona(idc_capa - 2); // capa oculta.
	}

	void BP::entrenamiento()
	{
		double max = 2.4 / num_nrns_capas[0];

		iniciarPesos((max * -1), max);

		inicio(this, arg_inc);

		do
		{
			calcularSalidas();
			setErrores();
			aprendizaje();
			finCiclo(this, arg_fc);
		} while (criterioTermino(this, arg_ct));

		//cllbkTerminoCiclo(cllbk_term_ciclo);

	}

	void BP::aprendizaje()
	{
		for (int capa = (num_capas - 1); capa > 0; capa--)
		{
			int idc_pr_nrn = getPrimeraNeurona(capa);
			int idc_ult_nrn = getUltimaNeurona(capa);
			int idc_pr_nrn_ca = getPrimeraNeurona(capa - 1); // capa anterior.
			int idc_ult_nrn_ca = getUltimaNeurona(capa - 1); // capa anterior.

			for (int i = idc_pr_nrn; i < idc_ult_nrn; i++)
			{
				for (int j = idc_pr_nrn_ca; j < idc_ult_nrn_ca; j++)
				{
					if (capa < (num_capas - 1))
						pesos[j][i] += deltaPeso(i, j);
					else if (capa < (num_capas - 1))
						pesos[j][i] += deltaPeso(i, j);
				}
			}
		}
	}

	double* BP::ejecutar(double* entrada)
	{
		int capa_salida = num_capas - 1;

		return getCapa(capa_salida);
	}

	void BP::setError(int idc_nrn, double error) { errores[getIdcNrnSalida(idc_nrn)] = error; }
	
	double BP::getError(int idc_nrn) const { return errores[getIdcNrnSalida(idc_nrn)]; }

	double BP::getError() const { return error; }

	double* BP::getErrores() const { return errores; }

	double* BP::getDeltas() const { return deltas; }

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