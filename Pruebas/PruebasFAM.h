#pragma once

#include "FAM.h"

using namespace RedNeuronal;

namespace PruebasRed
{
	class PruebasFAM
	{
	public:
		PruebasFAM();

		//~PruebasFAM();

		void imprimirMatriz(double**& matriz, int filas, int cols);

		void imprimirArray(double*& arr, int cols);

	private:
		FAM* red;
	};
}