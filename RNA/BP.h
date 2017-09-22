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
		sd = salidas deseadas.
		m = Momentum para la diferencia (delta) de pesos.
		a = Constante para la funcion tangente hiperbolica.
		b = Constante para la funcion tangente hiperbolica.
		*/
		BP(int nc, int *nnc, double t, double m = 0.95, double a = 1.716, double b = 0.667);

		/*
		Constructor usado para una red con pesos ya obtenidos.
		nc = Numero de neuronas.
		nnc = Numero de neuronas por capa.
		p : pesos de la red.
		*/
		BP(int nc, int* nnc, double** p);

		~BP();

		double funcionActivacion(double entrada_red);

		double tangenteHiperbolica(double entrada_red);

		/*
		coeficiente : el tercer coeficiente de la formula del gradiante, este varia dependiendo si es
		capa de salida u oculta.
		*/
		void calcularGradiantes();

		double gradianteError(double salida, double coeficiente);

		double deltaPeso(int idc_nrn, int idc_nrn_sig);

		void ajustarPeso(int idc_nrn, int idc_capa);

		void aprendizaje();

		double* ejecutar(double* patron);

		// calcula y setea el error de las neuronas de salida a partir de la salida deseada.
		void calcularErrores(double* salida_deseada);

		double getSumGradiante(int idc_nrn, int idc_capa);

		void setErrores(double* errores);

		void setError(int idc_nrn, double error);

		double getError(int idc_nrn) const;

		double getError() const;

		double* getErrores() const;

		double** getDeltas() const;

		double* getGradiantes() const;

		int getIdcNrnSalida(int idc_nrn) const;

		// obtiene la suma de errores al cuadrado.
		double getSumErr2();
	protected:
		double* errores;
		double* gradiantes;
		double** deltas;
		double error;
		double momentum; // constante para la diferencia (delta) del error.
		double th_a; // constante para la funcion tangente hiperbolica.
		double th_b; // constante para la funcion tangente hiperbolica;
	};
}

#endif