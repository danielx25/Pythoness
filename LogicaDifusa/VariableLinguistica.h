#pragma once

#ifndef C0100_LD_VARIABLELINGUISTICA
#define C0100_LD_VARIABLELINGUISTICA

#include <string>
#include <map>

#include "ValorLinguistico.h"

using namespace std;

namespace LogicaDifusa
{
	class VariableLinguistica
	{
	public:

		// n = nombre, a = minimo, b = maximo.
		VariableLinguistica(string n, double a, double b);

		bool agregarValorLinguistico(string nombre, FuncionPertenencia* fp);

		bool agregarValorLinguistico(ValorLinguistico* vl);

		bool fuzzificar(double dato);

		bool eliminiarValorLinguistico(string nombre);

		void getValores(map<string, ValorLinguistico*>& vals);

		void getValor(string nombre, ValorLinguistico*& val);

		string getNombre() const;

		double getMinimo() const;

		double getMaximo() const;

	private:
		string nombre;
		double min;
		double max;
		map<string, ValorLinguistico*> valores;
	};
}

#endif 