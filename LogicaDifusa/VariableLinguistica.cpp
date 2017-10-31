#include "Stdafx.h"
#include <iostream>
#include "VariableLinguistica.h"

using namespace std;

namespace LogicaDifusa
{
	VariableLinguistica::VariableLinguistica(string n, double a, double b)
	{
		nombre = n;
		max = b;
		min = a;
	}

	bool VariableLinguistica::agregarValorLinguistico(string nombre, FuncionPertenencia* fp)
	{
		// IMPLEMENTAR: COMPROBAR QUE EL VALOR LINGUISTICO NO SE SALGA DEL RANGO DE LA VARIABLE LINGUISTICA.
		ValorLinguistico* vl = new ValorLinguistico(nombre, fp);
		valores[nombre] = vl;

		return true;
	}

	/// <summary>
	/// Agrega un valor linguistico a la variable linguistica.
	/// </summary>
	/// <param name="valor"></param>
	/// <returns>Retorna true si se ha agrega el valor con exito, de lo contrario false.</returns>
	bool VariableLinguistica::agregarValorLinguistico(ValorLinguistico* vl)
	{
		// IMPLEMENTAR: COMPROBAR QUE EL VALOR LINGUISTICO NO SE SALGA DEL RANGO DE LA VARIABLE LINGUISTICA.
		valores[vl->getNombre()] = vl;

		return true;
	}

	bool VariableLinguistica::fuzzificar(double dato)
	{
		if (dato >= min && dato <= max)
		{
			for (map<string, ValorLinguistico*>::iterator it = valores.begin(); it != valores.end(); ++it)
			{
				it->second->CalcularGradoPertenencia(dato);
			}

			return true;
		}

		return false;
	}

	bool VariableLinguistica::eliminiarValorLinguistico(string nombre)
	{
		// IMPLEMENTAR: COMPROBAR QUE EL VALOR LINGUISTICO EXISTA.
		valores.erase(nombre);
		return true;
	}

	void VariableLinguistica::getValores(map<string, ValorLinguistico*>& vals) { vals = valores; }

	void VariableLinguistica::getValor(string nombre, ValorLinguistico*& val)
	{
		map<string, ValorLinguistico*>::iterator valor = valores.find(nombre);

		val = valor->second;
	}

	string VariableLinguistica::getNombre() const { return nombre; }

	double VariableLinguistica::getMinimo() const { return min; }

	double VariableLinguistica::getMaximo() const { return max; }

	string VariableLinguistica::getValor(double dato)
	{
		double max = 0;
		string valorlinguistico = "";

		//fuzzificar(dato);

		for (map<string, ValorLinguistico*>::iterator valor = valores.begin(); valor != valores.end(); ++valor)
		{
			valor->second->CalcularGradoPertenencia(dato);
			double grado = valor->second->getGradoPertenencia();

			if (valorlinguistico == "") valorlinguistico = valor->second->getNombre();

			if (grado > max)
			{
				max = grado;
				valorlinguistico = valor->second->getNombre();
			}
		}

		return valorlinguistico;
	}
}