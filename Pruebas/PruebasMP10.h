#pragma once

#include "SistemaFAM.h"

using namespace SFAM;

namespace PruebasMP
{
	class PruebasMP10
	{
	public:
		PruebasMP10();

		//~PruebasLD();

		static void validacion();

		void imprimirMatriz(double**& matriz, int filas, int cols);

		void imprimirArray(double*& arr, int cols);

	private:
		SistemaFAM* sfam;
	};
}