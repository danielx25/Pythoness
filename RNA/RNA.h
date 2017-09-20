#pragma once

#ifndef __RNA_H__
#define __RNA_H__

namespace RedNeuronal
{
	class RNA
	{
	public:
		/*
		nc = Numero de neuronas.
		nnc = Numero de neuronas por capa.
		t = Tasa de aprendizaje.
		*/
		RNA(int nc, int *nnc, double t);

		virtual ~RNA();

		// retorna la entrada para una neurona.
		virtual double funcionPropagacion(int idc_capa, int idc_neurona);

		virtual double funcionActivacion(double entrada_red) = 0;

		// result_act : valor resultante de la funcion de activacion.
		virtual double calcularSalida(double result_act);

		// algoritmo de aprendizaje para la red.
		virtual void aprendizaje() = 0;

		virtual void iniciarPesos(double min, double max);

		// obtiene las salidas de todas las neuronas, exceptuando las neuronas de entrada.
		virtual void calcularSalidas();

		virtual void setEntrada(double* patron);

		double* getCapa(int idc_capa) const;

		// retorna el indice de la primera neurona de la capa.
		int getPrimeraNeurona(int idc_capa) const;

		// retorna el indice de la ultima neurona de la capa.
		int getUltimaNeurona(int idc_capa) const;

		double getRandom(double min, double max) const;

		double getTasaAprendizaje() const;
		
		int getNumCapas() const;

		int getNumNrns() const;

		int getNumTotalNrns() const;

		int* getNumNrnsCapas() const;

		int getIteraciones() const;

		double* getSalidas() const;

		double** getPesos() const;

	protected:
		double *salidas;
		double **pesos;
		double tasa_aprdj;
		int num_capas;
		int num_nrns;
		int num_total_nrns;
		int *num_nrns_capas;
		int ciclos;
	};
}

#endif