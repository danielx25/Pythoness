#include "stdafx.h"
#include <iostream>
#include "Normalizacion.h"
#include "VariablesLinguisticas.h"
#include "PruebasLD.h"

using namespace std;
using namespace Datos;

namespace PruebasLogicaDifusa
{
	PruebasLD::PruebasLD()
	{
		VariableLinguistica* temperatura = new VariableLinguistica("Temperatura", 9.0, 37.0);
		temperatura->agregarValorLinguistico(new ValorLinguistico("fresca", new FuncionGaussiana(4.757, 9.0)));
		temperatura->agregarValorLinguistico(new ValorLinguistico("agradable", new FuncionGaussiana(4.757, 23.0)));
		temperatura->agregarValorLinguistico(new ValorLinguistico("calida", new FuncionGaussiana(4.757, 37.0)));
		
		// fuzzificamos los valores agregados para todos los valores linguisticos.
		map<string, ValorLinguistico*> valores;
		temperatura->getValores(valores);

		cout << "\nGaussiana - Grados Pertenencia\n";

		for (map<string, ValorLinguistico*>::iterator valor = valores.begin(); valor != valores.end(); ++valor)
		{
			valor->second->CalcularGradoPertenencia(31.5);
			cout << valor->second->getNombre() << ": Grado Pertenencia: " << valor->second->getGradoPertenencia() << "\n";
		}

		VariablesLinguisticas* vars = new VariablesLinguisticas();
		VariableLinguistica* mp10;

		vars->getVariable("mp10", mp10);

		map<string, ValorLinguistico*> vals;
		mp10->getValores(vals);

		double valor_des = Normalizacion::desnormalizar(0.404881, mp10->getMinimo(), mp10->getMaximo());

		valor_des = 500.0;

		cout << "\nMP10 - Grados Pertenencia\n";

		for (map<string, ValorLinguistico*>::iterator val = vals.begin(); val != vals.end(); ++val)
		{
			val->second->CalcularGradoPertenencia(valor_des);
			cout << val->second->getNombre() << ": Grado Pertenencia: " << val->second->getGradoPertenencia() << "\n";
		}

		cout << "\nValor: " << valor_des << " Valor linguistico MP10: " << mp10->getValor(valor_des) << "\n";
	}
}