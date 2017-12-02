#pragma once

#include "SistemaFAM.h"

using namespace STMFAM;

namespace PruebasRed
{
	class PruebasSFAM
	{
	public:
		PruebasSFAM();

		//~PruebasSFAM();

		void imprimirMatriz(double**& matriz, int filas, int cols);

		void imprimirArray(double*& arr, int cols);

	private:
		SistemaFAM* sfam;
	};
}