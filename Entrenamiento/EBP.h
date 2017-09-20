#pragma once

#ifndef __EBP_H__
#define __EBP_H__

#include "Entrenamiento.h"
#include "BP.h"

using namespace RedNeuronal;

namespace Entrenamientos
{
	class EBP : Entrenamiento
	{
	public:
		EBP(int patrones, int columnas, int nc, int *nnc, double t);

		EBP(int patrones, int columnas, int nc, int *nnc, double t, double m, double a, double b);

		EBP(int patrones, int columnas, int nc, int *nnc, double t, double m, double a, double b, double min, double max);

		~EBP();

		// realiza un entrenamiento online para una red con aprendizaje backpropagation.
		void online();

		// realiza un entrenamiento offline para una red con aprendizaje backpropagation.
		void offline();

		// setea el valor por default para el minimo para los numeros aleatoreos.
		void EBP::setDefaultMin();
		
		// setea el valor por default para el maximo para los numeros aleatoreos.
		void EBP::setDefaultMax();
	private:
		BP* red;
		int ciclos;
		double error;
		double criterio;
		double** salida_deseada;
	};
}

#endif