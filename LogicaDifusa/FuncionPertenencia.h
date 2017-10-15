/* Intefaz para las funciones de pertenencia. */
#pragma once

#ifndef C0100_LD_FUNCIONPERTENENCIA
#define C0100_LD_FUNCIONPERTENENCIA

namespace LogicaDifusa
{
	// Clase para una funcion de pertenencia.
	class FuncionPertenencia
	{
	public:

		// Destructor virtual para una correcta limpieza.
		virtual ~FuncionPertenencia() {}

		// Retorna el grado de pertenencia del valor x.
		virtual  double gradoPertenencia(double x) = 0;

		// Escala la funcion de pertenencia al grado de pertenencia pasado.
		virtual  bool cortarFuncion(double gradoPertenencia) = 0;

		// Indica el limite inferior (donde comienza) de la funcion de pertenencia.  
		virtual  double limiteInferior() const = 0;

		// Indica el limite superior (donde termina) de la funcion de pertenencia.
		virtual  double limiteSuperior() const = 0;

		void setCorte(double corte) { valor_corte = corte; }

		double getCorte() const { return valor_corte; }

		bool estaCortada() const { return cortada; }
	protected:
		double valor_corte;
		bool cortada;
	};
}

#endif