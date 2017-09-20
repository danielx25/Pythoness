#include "stdafx.h"
#include "EBP.h"

namespace Entrenamientos
{
	EBP::EBP(int patrones, int columnas, int nc, int* nnc, double t) : Entrenamiento(patrones, columnas)
	{
		red = new BP(nc, nnc, t);
		setDefaultMin();
		setDefaultMax();
	}

	EBP::EBP(int patrones, int columnas, int nc, int* nnc, double t, double m, double a, double b) : Entrenamiento(patrones, columnas)
	{
		red = new BP(nc, nnc, t, m, a, b);
		setDefaultMin();
		setDefaultMax();
	}

	EBP::EBP(int patrones, int columnas, int nc, int* nnc, double t, double m, double a, double b, double min, double max) : Entrenamiento(patrones, columnas, min, max)
	{
		red = new BP(nc, nnc, t, m, a, b);
	}

	EBP::~EBP() {}

	void EBP::online()
	{
		int patron = 0;

		red->iniciarPesos(min_rand, max_rand);

		inicio(this, arg_inc);

		do
		{
			red->setEntrada(epoch[patron]);
			red->calcularSalidas();
			red->setErrores(salida_deseada[patron]);
			red->calcularGradiantes();
			red->aprendizaje(); // se ajustan los pesos.
			finCiclo(this, arg_fc);

			if (patron == num_ptrns) patron = 0;
		} while (criterioTermino(this, arg_ct));
	}

	void EBP::offline()
	{

	}

	void EBP::setDefaultMin()
	{
		min_rand = (2.4 / red->getNumNrnsCapas()[0]) * -1;
	}

	void EBP::setDefaultMax()
	{
		max_rand = 2.4 / red->getNumNrnsCapas()[0];
	}
}