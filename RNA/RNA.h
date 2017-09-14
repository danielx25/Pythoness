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

		void setCriterio(bool(*funcion)(const RNA*, void*), void* arg);

		void setInicio(void (*funcion)(const RNA*, void*), void* arg);

		void setFinCiclo(void (*funcion)(const RNA*, void*), void* arg);

		double* getCapa(int idc_capa) const;

		// retorna el indice de la primera neurona de la capa.
		int getPrimeraNeurona(int idc_capa) const;

		// retorna el indice de la ultima neurona de la capa.
		int getUltimaNeurona(int idc_capa) const;

		double getRandom(double min, double max) const;

		double getTasaAprendizaje() const;
		
		int getNumCapas() const;

		int getNumNrns() const;

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
		void* arg_inc; // argumento adicional para el callback ejecutado al inicio.
		void* arg_fc; // argumento adicional para el callback terminoCiclo.
		void* arg_ct; // argumento adicional para el callback criterioTermino.
		void (*inicio)(const RNA*, void*); // funcion ejecutada al inicio de la ejecución de la red.
		void (*finCiclo)(const RNA*, void*); // funcion ejecutada al final de un ciclo de la ejecución de la red.
		bool (*criterioTermino)(const RNA*, void*); // funcion ejecutada para comprobar si se ha alcanzado el criterio de termino de la red.

		// retorna la entrada para una neurona.
		virtual double funcionPropagacion(int idc_capa, int idc_neurona) = 0;

		virtual double funcionActivacion(double entrada_red) = 0;

		virtual void aprendizaje() = 0;

		virtual double* ejecutar(double* entrada) = 0;

		virtual void entrenamiento() = 0;

		virtual void iniciarPesos(double min, double max) = 0;

		// obtiene las salidas de todas las neuronas, exceptuando las neuronas de entrada.
		virtual void calcularSalidas() = 0;
	};
}

#endif