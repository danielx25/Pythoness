/* Funcion de pertenencia trapezoidal.  */

#pragma once

#include "FuncionPertenencia.h"

#ifndef C0100_LD_FUNCIONCAMPANA
#define C0100_LD_FUNCIONCAMPANA

namespace LogicaDifusa
{
	// This class is exported from the MathLibrary.dll  
	class FuncionCampana : public FuncionPertenencia
	{
	public:

		FuncionCampana(double ancho, double radio, double centro);

		// Retorna el grado de pertenencia del valor x.
		double gradoPertenencia(double x);

		// Escala la funcion de pertenencia al grado de pertenencia pasado.
		bool cortarFuncion(double gradoPertenencia);

		// Indica el limite inferior (donde comienza) de la funcion de pertenencia.  
		double limiteInferior() const;

		// Indica el limite superior (donde termina) de la funcion de pertenencia.
		double limiteSuperior() const;

		double getValorAncho() const;

		double getValorRadio() const;

		double getValorCentro() const;
	private:
		double valor_ancho;
		double valor_radio;
		double valor_centro;
	};
}

#endif 