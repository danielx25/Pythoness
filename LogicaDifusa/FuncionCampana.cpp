/* Funcion de pertenencia trapezoidal.  */

#include "stdafx.h"

#include <cmath>
#include "FuncionCampana.h"

namespace LogicaDifusa
{

	FuncionCampana::FuncionCampana(double ancho, double radio, double centro) {
		valor_ancho = ancho;
		valor_radio = radio;
		valor_centro = centro;
		cortada = false;
		valor_corte = 0;
	}

	// Retorna el grado de pertenencia del valor x.
	double FuncionCampana::gradoPertenencia(double x)
	{
		double resultado = 0;

		resultado = 1 / ( 1 + pow( abs(x - valor_centro) / valor_ancho, 2 * valor_radio ) );

		// Si la funcion fue cortada, el grado de pertenencia no puede sobrepasar al valor de corte.
		/*if (resultado > valor_corte && cortada)
		{
			resultado = valor_corte;
		}*/

		return resultado;
	}

	// Escala la funcion de pertenencia al grado de pertenencia pasado.
	bool FuncionCampana::cortarFuncion(double gradoPertenencia)
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
	double FuncionCampana::limiteInferior() const
	{
		return 0;
	}

	// Indica el limite superior (donde termina) de la funcion de pertenencia.  
	double FuncionCampana::limiteSuperior() const
	{
		return 0;
	}

	double FuncionCampana::getValorAncho() const { return valor_ancho; }

	double FuncionCampana::getValorRadio() const { return valor_radio; }

	double FuncionCampana::getValorCentro() const { return valor_centro; }
}