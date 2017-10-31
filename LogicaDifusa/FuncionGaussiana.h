/* Funcion de pertenencia trapezoidal.  */

#pragma once

#include "FuncionPertenencia.h"

#ifndef C0100_LD_FUNCIONGAUSSIANA
#define C0100_LD_FUNCIONGAUSSIANA

namespace LogicaDifusa
{
	class FuncionGaussiana : public FuncionPertenencia
	{
	public:

		FuncionGaussiana(double ancho, double centro, double grado = 1);

		// Retorna el grado de pertenencia del valor x.
		double gradoPertenencia(double x);

		// Escala la funcion de pertenencia al grado de pertenencia pasado.
		bool cortarFuncion(double gradoPertenencia);

		// Indica el limite inferior (donde comienza) de la funcion de pertenencia.  
		double limiteInferior() const;

		// Indica el limite superior (donde termina) de la funcion de pertenencia.  
		double limiteSuperior() const;

		double getValorAncho() const;

		double getValorCentro() const;

		double getValorGrado() const;

	private:
		double valor_ancho;
		double valor_centro;
		double valor_grado;
	};
}

#endif 