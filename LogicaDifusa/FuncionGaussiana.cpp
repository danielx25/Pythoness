/* Funcion de pertenencia trapezoidal.  */

#include "stdafx.h"
#include <cmath>
#include "FuncionGaussiana.h"

namespace LogicaDifusa
{

	FuncionGaussiana::FuncionGaussiana(double ancho, double centro, double grado) {
		
		valor_ancho = ancho;
		valor_centro = centro;
		valor_grado = grado;
		cortada = false;
		valor_corte = 0;
	}

	// Retorna el grado de pertenencia del valor x.
	double FuncionGaussiana::gradoPertenencia(double x)
	{
		double resultado = 0;

		resultado = valor_grado * exp( -( pow(x - valor_centro, 2) / (2 * pow(valor_ancho, 2)) ) );
		
		// Si la funcion fue cortada, el grado de pertenencia no puede sobrepasar al valor de corte.
		/*if (resultado > valor_corte && cortada)
		{
			resultado = valor_corte;
		}*/

		return resultado;
	}

	// Escala la funcion de pertenencia al grado de pertenencia pasado.
	bool FuncionGaussiana::cortarFuncion(double gradoPertenencia)
	{
		if (gradoPertenencia >= 0 && gradoPertenencia <= 1)
		{
			valor_corte = gradoPertenencia;
			cortada = true;
			return true;
		}
		return false;
	}

	double FuncionGaussiana::limiteInferior() const { return 0; }

	double FuncionGaussiana::limiteSuperior() const { return 0; }

	double FuncionGaussiana::getValorAncho() const { return valor_ancho; }

	double FuncionGaussiana::getValorCentro() const { return valor_centro; }
	
	double FuncionGaussiana::getValorGrado() const { return valor_grado; }
}