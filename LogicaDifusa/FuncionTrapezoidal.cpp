/* Funcion de pertenencia trapezoidal.  */

#include "stdafx.h"

#include "FuncionTrapezoidal.h"

namespace LogicaDifusa
{

	FuncionTrapezoidal::FuncionTrapezoidal(double izq_abajo, double izq_arriba, double derch_arriba, double derch_abajo) {
		if (!(izq_abajo <= izq_arriba && izq_arriba <= derch_arriba && derch_arriba <= derch_abajo))
		{

		}

		valor_izq_abajo = izq_abajo;
		valor_izq_arriba = izq_arriba;
		valor_derch_arriba = derch_arriba;
		valor_derch_abajo = derch_abajo;
		cortada = false;
		valor_corte = 0;
	}

	// Retorna el grado de pertenencia del valor x.
	double FuncionTrapezoidal::gradoPertenencia(double x)
	{
		double resultado = 0;

		if (x == valor_izq_abajo && x == valor_izq_arriba)
		{
			resultado = 1.0;
		}
		else if (x == valor_derch_arriba && x == valor_derch_abajo)
		{
			resultado = 1.0;
		}
		else if (x <= valor_izq_abajo || x >= valor_derch_abajo)
		{
			resultado = 0;
		}
		else if ((x >= valor_izq_arriba) && (x <= valor_derch_arriba))
		{
			resultado = 1;
		}
		else if ((x > valor_izq_abajo) && (x < valor_izq_arriba))
		{
			resultado = (x / (valor_izq_arriba - valor_izq_abajo)) - (valor_izq_abajo / (valor_izq_arriba - valor_izq_abajo));
		}
		else
		{
			resultado = (-x / (valor_derch_abajo - valor_derch_arriba)) + (valor_derch_abajo / (valor_derch_abajo - valor_derch_arriba));
		}

		// Si la funcion fue cortada, el grado de pertenencia no puede sobrepasar al valor de corte.
		if (resultado > valor_corte && cortada)
		{
			resultado = valor_corte;
		}

		return resultado;
	}

	// Escala la funcion de pertenencia al grado de pertenencia pasado.
	bool FuncionTrapezoidal::cortarFuncion(double gradoPertenencia)
	{
		if (gradoPertenencia >= 0 && gradoPertenencia <= 1)
		{
			valor_corte = gradoPertenencia;
			cortada = true;
			return true;
		}
		return false;
	}

	// Indica el limite inferior (donde comienza) de la funcion de pertenencia.  
	double FuncionTrapezoidal::limiteInferior() const
	{
		return valor_izq_abajo;
	}

	// Indica el limite superior (donde termina) de la funcion de pertenencia.  
	double FuncionTrapezoidal::limiteSuperior() const
	{
		return valor_derch_arriba;
	}

	double FuncionTrapezoidal::getValorIzqAbj() const { return valor_izq_abajo; }

	double FuncionTrapezoidal::getValorIzqArb() const { return valor_izq_arriba; }

	double FuncionTrapezoidal::getValorDerchArb() const { return valor_derch_arriba; }

	double FuncionTrapezoidal::getValorDerchAbj() const { return valor_derch_abajo; }
}