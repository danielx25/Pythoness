#pragma once

#ifndef __FAM_H__
#define __FAM_H__

namespace RedNeuronal
{
	/*
	Una memoria asociativa difusa (FAM) esta compuesta por una asociacion entre dos matrices 
	A y B. La entrada y salida de la memoria asociativa es un subconjunto de A o bien de B. Por ej 
	si la entrada es un subconjunto de A la salida sera un subconjunto de B.
	*/
	class FAM
	{
	public:
		/*
		a = Asociado A.
		nna = Numero de neuronas asociado A.
		b = Asociado B.
		nnb = Numero de neuronas asociado B.
		*/
		FAM(double*& a, int nna, double*& b, int nnb);

		~FAM();

		// fuzzy Hebb Matrix (correlacion minima de codificacion).
		void matrizHebbDifusa(double*& a, double*& b, double**& p);

		// composicion difusa vector-matriz.
		void matrizComposicionDifusa(int filas, int columnas, double*& e, double**& p, double*& s);

		// s = salida.
		void getSalidaB(double*& entrada_a, double*& s);

		// s = salida.
		void getSalidaA(double*& entrada_b, double*& s);
		
		void getPesos(double**& p) const;
	protected:
		double** pesos;
		double* A; // asociado
		double* B; // asociado
		int num_nrns_a;
		int num_nrns_b;
	};
}

#endif