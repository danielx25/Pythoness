/* Funcion de pertenencia trapezoidal.  */

#include "stdafx.h"

#include "FuncionTriangular.h"

namespace LogicaDifusa
{

	FuncionTriangular::FuncionTriangular(double izq, double centro, double derch) {
		if (!(izq <= centro && centro <= derch))
		{
			
		}

		valor_izq = izq;
		valor_centro = centro;
		valor_derch = derch;
		cortada = false;
		valor_corte = 0;
	}

	// Retorna el grado de pertenencia del valor x.
	double FuncionTriangular::gradoPertenencia(double x)
	{
		double resultado = 0;

		if (x == valor_izq && x == valor_centro)
		{
			resultado = 1.0;
		}
		else if (x == valor_centro && x == valor_derch)
		{
			resultado = 1.0;
		}
		else if (x <= valor_izq || x >= valor_derch)
		{
			resultado = 0;
		}
		else if (x == valor_centro)
		{
			resultado = 1;
		}
		else if ((x > valor_izq) && (x < valor_centro))
		{

			resultado = (x / (valor_centro - valor_izq)) - (valor_izq / (valor_centro - valor_izq));
		}
		else
		{
			resultado = (-x / (valor_derch - valor_centro)) + (valor_derch / (valor_derch - valor_centro));
		}
		// Si la funcion fue cortada, el grado de pertenencia no puede sobrepasar al valor de corte.
		if (resultado > valor_corte && cortada)
		{
			resultado = valor_corte;
		}

		return resultado;
	}

	// Escala la funcion de pertenencia al grado de pertenencia pasado.
	bool FuncionTriangular::cortarFuncion(double gradoPertenencia)
	{
		if (gradoPertenencia >= 0 && gradoPertenencia <= 1)
		{
			valor_corte = gradoPertenencia;
			cortada = true;
			return true;
		}
		return false;
	}

	double FuncionTriangular::limiteInferior() const { return valor_izq; }

	double FuncionTriangular::limiteSuperior() const { return valor_derch; }

	double FuncionTriangular::getValorIzq() const { return valor_izq; }

	double FuncionTriangular::getValorCentro() const { return valor_centro; }

	double FuncionTriangular::getValorDerch() const { return valor_derch; }
}