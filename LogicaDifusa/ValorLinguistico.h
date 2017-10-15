#pragma once

#ifndef C0100_LD_VALORLINGUISTICO
#define C0100_LD_VALORLINGUISTICO

#include "FuncionPertenencia.h"
#include <string>

using namespace std;

namespace LogicaDifusa
{
	// Clase para un valor linguistico.
	class ValorLinguistico
	{
	public:

		ValorLinguistico(string n, FuncionPertenencia* f);

		ValorLinguistico(string n, FuncionPertenencia* f, double grado);

		void CalcularGradoPertenencia(double valor);

		string getNombre() const;

		void getFuncionPertenencia(FuncionPertenencia*& funcion) const;

		void setGradoPertenencia(double gp);

		double getGradoPertenencia() const;

	private:
		string nombre;
		FuncionPertenencia* fp;
		double gradoPertenencia;
	};
}

#endif 