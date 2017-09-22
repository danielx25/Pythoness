#pragma once

#include "BP.h"
#include "EBP.h"

using namespace RedNeuronal;
using namespace Entrenamientos;

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
		
		void setErrores();

		void calcularGradiantes();
		
		void aprendizaje();

		void entrenamiento();

		void imprimirMatriz(double** matriz, int filas, int cols);

		void imprimirArray(double* arr, int cols);

		void inicio(const EBP* ebp, void* arg);

		void finCiclo(const EBP* ebp, void* arg);

		bool criterio(const EBP* ebp, void* arg);
	private:
		int nc;
		int* nnc;
		double t;
		BP* red;
	};
}