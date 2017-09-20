#pragma once

#include "BP.h"

using namespace RedNeuronal;

namespace PruebasRed
{
	class PruebaBP
	{
	public:
		PruebaBP();

		//~PruebaBP();

		void inicializacion();
		
		void infoCapas();

		void iniciarPesos();
		
		void calcularSalidas();
		
		void calcularGradiantes();
		
		void ajustarPesos();

		void imprimirMatriz(double** matriz, int filas, int cols);

		void imprimirArray(double* arr, int cols);
	private:
		int nc;
		int* nnc;
		double t;
		BP* red;
	};
}