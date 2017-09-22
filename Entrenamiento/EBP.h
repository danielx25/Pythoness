#pragma once

#ifndef __EBP_H__
#define __EBP_H__

#include "Entrenamiento.h"
#include "BP.h"

using namespace RedNeuronal;

namespace Entrenamientos
{
	class EBP : public Entrenamiento
	{
	public:
		EBP(int patrones, int columnas, int nc, int *nnc, double t);

		EBP(int patrones, int columnas, int nc, int *nnc, double t, double m, double a, double b);

		EBP(int patrones, int columnas, int nc, int *nnc, double t, double m, double a, double b, double min, double max);

		~EBP();

		// realiza un entrenamiento online para una red con aprendizaje backpropagation.
		double** online();

		// realiza un entrenamiento offline para una red con aprendizaje backpropagation.
		double** offline();

		bool criterio();

		void setSalida(int patron, int salida, double valor);

		// setea el valor por default para el minimo para los numeros aleatoreos.
		void setDefaultMin();
		
		// setea el valor por default para el maximo para los numeros aleatoreos.
		void setDefaultMax();

		void setError(double e);

		double getError() const;

		double getNumSalidas() const;

		double* getErrores() const;
	private:
		BP* red;
		int ciclos;
		double error;
		//double criterio;
		double** salidas_deseadas;

		void inicializarSalidas();
	};
}

#endif