#pragma once

#ifndef __BP_H__
#define __BP_H__

#include "RNA.h"

namespace RedNeuronal
{
	class BP : public RNA
	{
	public:
		/*
		nc = Numero de neuronas.
		nnc = Numero de neuronas por capa.
		t = Tasa de aprendizaje.
		c = Funcion para el criterio de detencion.
		m = Momentum para la diferencia (delta) de pesos.
		a = Constante para la funcion tangente hiperbolica.
		b = Constante para la funcion tangente hiperbolica.
		s = Array de dos dimensiones para las salidas de las neuronas.
		p = Array de dos dimensiones para los  pesos de las neuronas.
		*/
		BP(int nc, int *nnc, double t, double* sd, double m = 0.95, double a = 1.716, double b = 0.667);

		~BP();

		double funcionActivacion(double entrada_red);

		double gradianteError(double salida, double error);

		double deltaPeso(int idc_nrn_salida, int idc_nrn_oculta);

		void ajustarPesosCapaSalida();

		void ajustarPesosCapaOculta(int idc_capa);

		void entrenamiento();

		void aprendizaje();

		double* ejecutar(double* entrada);
		
		void setErrores();

		void setError(int idc_nrn, double error);

		double getError(int idc_nrn) const;

		double getError() const;

		double* getErrores() const;

		double* getDeltas() const;

		// obtiene la suma de errores al cuadrado.
		double getSumErr2();
	protected:
		double* salida_deseada;
		double* errores;
		double *gradiantes;
		double *deltas;
		double error;
		double momentum; // constante para la diferencia (delta) del error.
		double th_a; // constante para la funcion tangente hiperbolica.
		double th_b; // constante para la funcion tangente hiperbolica;

		int getIdcNrnSalida(int idc_nrn) const;
	};
}

#endif