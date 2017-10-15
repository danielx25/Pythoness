#include "stdafx.h"
#include <iostream>
#include "ValorLinguistico.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace LogicaDifusa
{
	ValorLinguistico::ValorLinguistico(string n, FuncionPertenencia* f)
	{
		nombre = n;
		fp = f;
		gradoPertenencia = -1; // grado de pertenencia por defecto.
	}

	ValorLinguistico::ValorLinguistico(string n, FuncionPertenencia* f, double grado)
	{
		nombre = n;
		fp = f;
		gradoPertenencia = grado; // grado de pertenencia por defecto.
	}

	void ValorLinguistico::CalcularGradoPertenencia(double valor)
	{
		gradoPertenencia = fp->gradoPertenencia(valor);
	}

	string ValorLinguistico::getNombre() const { return nombre; }

	void ValorLinguistico::getFuncionPertenencia(FuncionPertenencia*& funcion) const { funcion = fp; }

	void ValorLinguistico::setGradoPertenencia(double gp) { gradoPertenencia = gp; }

	double ValorLinguistico::getGradoPertenencia() const { return gradoPertenencia; }
}