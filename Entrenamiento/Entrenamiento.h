#pragma once

#ifndef __ENTRENAMIENTO_H__
#define __ENTRENAMIENTO_H__

#include "BP.h"

using namespace RedNeuronal;

namespace Entrenamientos
{
	class Entrenamiento
	{
	public:
		Entrenamiento(int patrones, int columnas);

		Entrenamiento(int patrones, int columnas, double min, double max);

		virtual ~Entrenamiento();

		virtual void setValor(int patron, int column, double valor);

		void setMaxRand(double max);

		void setMinRand(double min);

		void setCriterio(bool(*funcion)(const Entrenamiento*, void*), void* arg);

		void setInicio(void(*funcion)(const Entrenamiento*, void*), void* arg);

		void setFinCiclo(void(*funcion)(const Entrenamiento*, void*), void* arg);

		int getNumPatrones() const;

		int getCiclos() const;
	protected:
		int num_ptrns;
		int num_cols;
		int patron_actual; // numero del patron actual entregado a la red.
		double max_rand;
		double min_rand;
		int ciclos;
		double** epoch;
		void* arg_inc; // argumento adicional para el callback ejecutado al inicio.
		void* arg_fc; // argumento adicional para el callback terminoCiclo.
		void* arg_ct; // argumento adicional para el callback criterioTermino.
		void(*inicio)(const Entrenamiento*, void*); // funcion ejecutada al inicio de la ejecución de la red.
		void(*finCiclo)(const Entrenamiento*, void*); // funcion ejecutada al final de un ciclo de la ejecución de la red.
		bool(*criterioTermino)(const Entrenamiento*, void*); // funcion ejecutada para comprobar si se ha alcanzado el criterio de termino de la red.

		void inicializarEpoch(int patrones, int columnas);
	};
}

#endif