#include "stdafx.h"
#include "EBP.h"
#include "Entrenamiento.h"
#include "BP.h"
#include <math.h>

using namespace RedNeuronal;

namespace Entrenamientos
{
	EBP::EBP(int patrones, int columnas, int nc, int* nnc, double t) : Entrenamiento(patrones, columnas)
	{
		red = new BP(nc, nnc, t);
		setDefaultMin();
		setDefaultMax();
		inicializarSalidas();
		ciclos = 0;
	}

	EBP::EBP(int patrones, int columnas, int nc, int* nnc, double t, double m, double a, double b) : Entrenamiento(patrones, columnas)
	{
		red = new BP(nc, nnc, t, m, a, b);
		setDefaultMin();
		setDefaultMax();
		inicializarSalidas();
		ciclos = 0;
	}

	EBP::EBP(int patrones, int columnas, int nc, int* nnc, double t, double m, double a, double b, double min, double max) : Entrenamiento(patrones, columnas, min, max)
	{
		red = new BP(nc, nnc, t, m, a, b);
		inicializarSalidas();
		ciclos = 0;
	}

	EBP::~EBP() 
	{
		double num_nrns_salida = red->getNumNrnsCapas()[red->getNumCapas() - 1];
		
		for (int i = 0; i < num_nrns_salida; i++)
			delete[] salidas_deseadas[i];

		delete[] salidas_deseadas;
	}

	void EBP::inicializarSalidas()
	{
		double num_nrns_salida = red->getNumNrnsCapas()[red->getNumCapas() - 1];
		salidas_deseadas = new double*[num_ptrns];

		for (int i = 0; i < num_ptrns; i++)
		{
			salidas_deseadas[i] = new double[num_nrns_salida];
			
			for (int j = 0; j < num_nrns_salida; j++)
				salidas_deseadas[i][j] = 0;
		}
	}


	double** EBP::online()
	{
		patron_actual = 0;

		red->iniciarPesos(min_rand, max_rand);

		//inicio(this, arg_inc);

		do
		{
			red->setEntrada(epoch[patron_actual]);
			red->calcularSalidas();
			red->calcularErrores(salidas_deseadas[patron_actual]);
			red->calcularGradiantes();
			red->aprendizaje(); // se ajustan los pesos.
			
			//finCiclo(this, arg_fc);

			if (patron_actual == num_ptrns) patron_actual = 0;
			else patron_actual += 1;
		} while (criterio()/*criterioTermino(this, arg_ct)*/);

		return red->getPesos();
	}

	double** EBP::offline()
	{
		int capa_salida = red->getNumCapas() - 1;
		double* errores = new double[red->getNumNrnsCapas()[capa_salida]];
		int idc_pr_nrn = red->getPrimeraNeurona(capa_salida);
		int idc_ult_nrn = red->getUltimaNeurona(capa_salida);

		for (int i = 0; i < num_ptrns; i++)
			errores[i] = 0;

		red->iniciarPesos(min_rand, max_rand);

		inicio(this, arg_inc);

		do
		{
			for (patron_actual = 0; patron_actual < num_ptrns; patron_actual++)
			{
				red->setEntrada(epoch[patron_actual]);
				red->calcularSalidas();

				double* salidas = red->getSalidas();

				// acumulamos el error.
				for (int i = idc_pr_nrn; i <= idc_ult_nrn; i++)
					errores[i] += salidas_deseadas[patron_actual][i] - salidas[i];
			}
			
			for (int i = idc_pr_nrn; i <= idc_ult_nrn; i++)
				red->setError(i, errores[i]);

			red->calcularGradiantes();
			red->aprendizaje(); // se ajustan los pesos.

			finCiclo(this, arg_fc);
		} while (criterioTermino(this, arg_ct));

		return red->getPesos();
	}

	bool EBP::criterio()
	{
		int num_salidas = getNumSalidas();
		double* errores = getErrores();
		double sumErr2 = getError();
		double rms = 0;

		for (int i = 0; i < num_salidas; i++)
			sumErr2 += pow(errores[i], 2);

		rms = sqrt(sumErr2 / getNumPatrones());

		if (rms == 0.001) return true;

		return false;
	}

	void EBP::setSalida(int patron, int salida, double valor) { salidas_deseadas[patron][salida] = valor; }

	void EBP::setDefaultMin()
	{
		min_rand = (2.4 / red->getNumNrnsCapas()[0]) * -1;
	}

	void EBP::setDefaultMax()
	{
		max_rand = 2.4 / red->getNumNrnsCapas()[0];
	}

	void EBP::setError(double e) { error = e; }

	double EBP::getError() const { return error; }

	double EBP::getNumSalidas() const { return red->getNumNrnsCapas()[red->getNumCapas() - 1]; }

	double* EBP::getErrores() const { return red->getErrores(); }
}