/* Funcion de pertenencia trapezoidal.  */

#pragma once

#include "FuncionPertenencia.h"

#ifndef C0100_LD_FUNCIONTRIANGULAR
#define C0100_LD_FUNCIONTRIANGULAR

namespace LogicaDifusa
{
	// This class is exported from the MathLibrary.dll  
	class FuncionTriangular : public FuncionPertenencia
	{
	public:

		FuncionTriangular(double izq, double centro, double derch);

		// Retorna el grado de pertenencia del valor x.
		double gradoPertenencia(double x);

		// Escala la funcion de pertenencia al grado de pertenencia pasado.
		bool cortarFuncion(double gradoPertenencia);

		// Indica el limite inferior (donde comienza) de la funcion de pertenencia.  
		double limiteInferior() const;

		// Indica el limite superior (donde termina) de la funcion de pertenencia.  
		double limiteSuperior() const;

		double getValorIzq() const;

		double getValorCentro() const;

		double getValorDerch() const;

	private:
		double valor_izq;
		double valor_centro;
		double valor_derch;
	};
}

#endif 