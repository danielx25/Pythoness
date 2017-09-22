#include "stdafx.h"
#include "Entrenamiento.h"

namespace Entrenamientos
{
	Entrenamiento::Entrenamiento(int patrones, int columnas) : num_ptrns(patrones), num_cols(columnas)
	{
		inicializarEpoch(num_ptrns, num_cols);
		max_rand = 0.5;
		min_rand = -max_rand;
	}

	Entrenamiento::Entrenamiento(int patrones, int columnas, double min, double max) : num_ptrns(patrones), num_cols(columnas), min_rand(min), max_rand(max)
	{
		inicializarEpoch(num_ptrns, num_cols);
	}

	Entrenamiento::~Entrenamiento()
	{
		for (int i = 0; i < num_cols; i++)
			delete[] epoch[i];

		delete[] epoch;
	}

	void Entrenamiento::inicializarEpoch(int patrones, int columnas)
	{
		epoch = new double*[patrones];

		// iniciamos el epoch en cero.
		for (int i = 0; i < patrones; i++)
		{
			epoch[i] = new double[columnas];

			for (int j = 0; j < columnas; j++)
				epoch[i][j] = 0;
		}
	}

	void Entrenamiento::setValor(int patron, int column, double valor) { epoch[patron][column] = valor; }

	void Entrenamiento::setMaxRand(double max) { max_rand = max; }

	void Entrenamiento::setMinRand(double min) { min_rand = min; }

	void Entrenamiento::setInicio(void(*funcion)(const Entrenamiento*, void*), void* arg)
	{
		inicio = funcion;
		arg_inc = arg;
	}

	void Entrenamiento::setFinCiclo(void(*funcion)(const Entrenamiento*, void*), void* arg)
	{
		finCiclo = funcion;
		arg_fc = arg;
	}

	void Entrenamiento::setCriterio(bool(*funcion)(const Entrenamiento*, void*), void* arg)
	{
		criterioTermino = funcion;
		arg_ct = arg;
	}

	int Entrenamiento::getCiclos() const { return ciclos; }

	int Entrenamiento::getNumPatrones() const { return num_ptrns; }

}