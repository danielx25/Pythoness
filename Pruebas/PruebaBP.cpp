#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "PruebaBP.h"

using namespace std;

namespace PruebasRed
{
	PruebaBP::PruebaBP()
	{
		/*nc = 4;
		nnc = new int[nc];
		t = .1;
		
		nnc[0] = 3;
		nnc[1] = 4;
		nnc[2] = 3;
		nnc[3] = 2;

		double* patron = new double[nnc[0]];

		patron[0] = 0.12;
		patron[1] = 0.51;
		patron[2] = 0.26;

		red = new BP(nc, nnc, t);

		red->setEntrada(patron);
		//inicializacion();
		iniciarPesos();
		//infoCapas();
		calcularSalidas();
		setErrores();
		calcularGradiantes();
		aprendizaje();

		delete red;*/

		entrenamiento();

		int tecla;
		cin >> tecla;
	}

	void PruebaBP::inicializacion()
	{
		cout << "Pesos\n\n";
		imprimirMatriz(red->getPesos(), red->getNumTotalNrns(), red->getNumTotalNrns());
		cout << "\nSalidas\n\n";
		imprimirArray(red->getSalidas(), red->getNumTotalNrns());
		cout << "\nDeltas\n\n";
		imprimirMatriz(red->getDeltas(), red->getNumTotalNrns(), red->getNumTotalNrns());
		cout << "\nGradiantes\n\n";
		imprimirArray(red->getGradiantes(), red->getNumTotalNrns());
		cout << "\nErrores\n\n";
		imprimirArray(red->getErrores(), 2);
	}

	void PruebaBP::infoCapas()
	{
		cout << "\n";

		for (int i = 0; i < nc; i++)
			cout << "Capa " << i << " desde neurona " << red->getPrimeraNeurona(i) << " hasta neurona " << red->getUltimaNeurona(i) << "\n";
	}

	void PruebaBP::iniciarPesos()
	{
		double max = 2.4 / red->getNumNrnsCapas()[0];

		red->iniciarPesos(-max, max);

		cout << "\nPesos aleatorios Min:" << -max << " Max:" << max << "\n\n";
		imprimirMatriz(red->getPesos(), red->getNumTotalNrns(), red->getNumTotalNrns());
	}

	void PruebaBP::calcularSalidas()
	{
		red->calcularSalidas();

		cout << "\nSalidas\n\n";
		imprimirArray(red->getSalidas(), red->getNumTotalNrns());
	}

	void PruebaBP::setErrores()
	{
		double* salida_deseada = new double[nnc[nc - 1]];

		salida_deseada[0] = 0.5;
		salida_deseada[1] = 0.29;

		red->setErrores(salida_deseada);

		cout << "\nErrores\n\n";
		imprimirArray(red->getErrores(), nnc[nc - 1]);
	}


	void PruebaBP::calcularGradiantes()
	{
		red->calcularGradiantes();

		cout << "\nGradiantes\n\n";
		imprimirArray(red->getGradiantes(), red->getNumTotalNrns());
	}

	void PruebaBP::aprendizaje()
	{
		red->aprendizaje();

		cout << "\nDeltas\n\n";
		imprimirMatriz(red->getDeltas(), red->getNumTotalNrns(), red->getNumTotalNrns());
		cout << "\nPesos ajustados\n\n";
		imprimirMatriz(red->getPesos(), red->getNumTotalNrns(), red->getNumTotalNrns());
	}

	void PruebaBP::entrenamiento()
	{
		/*double arr[60][4] =
		{
			{ 0.08333333333333333, 0.125, 0.14285714285714285, 0.07407407407407407 },
			{ 0.0, 1.0, 0.2857142857142857, 0.37962962962962965 },
			{ 1.0, 0.125, 0.5714285714285714, 0.5694444444444444 },
			{ 1.0, 0.375, 0.2857142857142857, 0.5601851851851852 },
			{ 0.8333333333333334, 0.25, 0.8571428571428571, 0.6388888888888888 },
			{ 0.75, 0.5, 0.42857142857142855, 0.5509259259259259 },
			{ 0.5, 0.875, 0.0, 0.4398148148148148 },
			{ 1.0, 1.0, 1.0, 1.0 },
			{ 0.9166666666666666, 0.125, 0.8571428571428571, 0.6296296296296297 },
			{ 0.5, 0.0, 0.8571428571428571, 0.42592592592592593 },
			{ 0.16666666666666666, 0.25, 0.5714285714285714, 0.28703703703703703 },
			{ 0.5, 0.5, 0.7142857142857143, 0.5462962962962963 },
			{ 0.75, 0.125, 0.7142857142857143, 0.5185185185185185 },
			{ 1.0, 0.5, 0.0, 0.5092592592592593 },
			{ 0.8333333333333334, 0.5, 0.0, 0.4444444444444444 },
			{ 0.0, 0.875, 0.2857142857142857, 0.33796296296296297 },
			{ 0.6666666666666666, 0.0, 0.2857142857142857, 0.3055555555555556 },
			{ 0.4166666666666667, 0.375, 0.2857142857142857, 0.3333333333333333 },
			{ 0.25, 0.5, 0.7142857142857143, 0.44907407407407407 },
			{ 0.0, 0.0, 0.14285714285714285, 0.0 },
			{ 0.5, 0.5, 0.2857142857142857, 0.4074074074074074 },
			{ 0.25, 0.75, 1.0, 0.625 },
			{ 0.4166666666666667, 0.5, 0.14285714285714285, 0.3287037037037037 },
			{ 0.16666666666666666, 0.5, 0.2857142857142857, 0.2777777777777778 },
			{ 1.0, 0.875, 0.14285714285714285, 0.6805555555555556 },
			{ 0.16666666666666666, 1.0, 0.2857142857142857, 0.4444444444444444 },
			{ 0.08333333333333333, 1.0, 0.0, 0.3194444444444444 },
			{ 0.5, 0.625, 0.5714285714285714, 0.5416666666666666 },
			{ 0.25, 0.375, 0.14285714285714285, 0.2222222222222222 },
			{ 0.25, 0.25, 0.8571428571428571, 0.41203703703703703 },
			{ 0.75, 0.125, 0.0, 0.28703703703703703 },
			{ 0.25, 0.375, 0.42857142857142855, 0.3148148148148148 },
			{ 0.25, 0.5, 0.2857142857142857, 0.3101851851851852 },
			{ 0.4166666666666667, 0.875, 0.42857142857142855, 0.5462962962962963 },
			{ 0.4166666666666667, 0.875, 0.8571428571428571, 0.6851851851851852 },
			{ 0.9166666666666666, 0.0, 1.0, 0.6342592592592593 },
			{ 0.9166666666666666, 1.0, 0.0, 0.6435185185185185 },
			{ 0.16666666666666666, 0.0, 0.42857142857142855, 0.1574074074074074 },
			{ 0.75, 0.375, 0.8571428571428571, 0.6481481481481481 },
			{ 0.75, 0.375, 0.42857142857142855, 0.5092592592592593 },
			{ 1.0, 0.5, 0.7142857142857143, 0.7407407407407407 },
			{ 0.9166666666666666, 0.875, 0.2857142857142857, 0.6944444444444444 },
			{ 0.16666666666666666, 0.75, 1.0, 0.5925925925925926 },
			{ 0.25, 0.25, 0.0, 0.13425925925925927 },
			{ 0.8333333333333334, 0.75, 0.5714285714285714, 0.7129629629629629 },
			{ 0.5, 0.375, 0.5714285714285714, 0.4583333333333333 },
			{ 0.75, 0.375, 0.8571428571428571, 0.6481481481481481 },
			{ 0.3333333333333333, 0.875, 0.5714285714285714, 0.5601851851851852 },
			{ 0.75, 0.375, 0.2857142857142857, 0.46296296296296297 },
			{ 0.8333333333333334, 0.375, 0.2857142857142857, 0.49537037037037035 },
			{ 0.0, 0.875, 0.42857142857142855, 0.38425925925925924 },
			{ 0.5, 0.875, 0.8571428571428571, 0.7175925925925926 },
			{ 0.3333333333333333, 1.0, 0.5714285714285714, 0.6018518518518519 },
			{ 0.5, 0.375, 0.5714285714285714, 0.4583333333333333 },
			{ 0.5833333333333334, 0.5, 0.0, 0.3472222222222222 },
			{ 1.0, 0.125, 0.42857142857142855, 0.5231481481481481 },
			{ 0.0, 0.875, 0.42857142857142855, 0.38425925925925924 },
			{ 0.08333333333333333, 1.0, 1.0, 0.6435185185185185 },
			{ 0.75, 0.625, 0.5714285714285714, 0.6388888888888888 },
			{ 0.3333333333333333, 1.0, 0.8571428571428571, 0.6944444444444444 },
		};*/

		// prepare XOR traing data
		double data[][4] = {
			0,	0,	0,	0,
			0,	0,	1,	1,
			0,	1,	0,	1,
			0,	1,	1,	0,
			1,	0,	0,	1,
			1,	0,	1,	0,
			1,	1,	0,	0,
			1,	1,	1,	1 };

		// prepare test data	
		double testData[][3] = {
			0,      0,      0,
			0,      0,      1,
			0,      1,      0,
			0,      1,      1,
			1,      0,      0,
			1,      0,      1,
			1,      1,      0,
			1,      1,      1 };

		int patrones = 8;
		int num_entrada = 3;

		nc = 3;
		nnc = new int[nc];
		t = .1;

		nnc[0] = 3;
		nnc[1] = 3;
		nnc[2] = 2;
		nnc[3] = 1;

		EBP* ebp = new EBP(patrones, num_entrada, nc, nnc, t);
		//ebp->setInicio(inicio(), NULL);

		cout << "Ingreso de datos\n";
		for (int i = 0; i < patrones; i++)
		{
			for (int j = 0; j < 4; j++)
				ebp->setValor(i, j, data[i][j]);
			
			ebp->setSalida(i, 3, data[i][3]);
		}

		cout << "Entrenamiento\n";
		red = new BP(nc, nnc, ebp->online());
		cout << "Ejecucion\n";
		double* entradas = new double[num_entrada];


		for (int i = 0; i < patrones; i++)
		{
			for (int j = 0; j < num_entrada; j++)
				entradas[j] = testData[i][j];
	
			double* result = red->ejecutar(entradas);
			cout << "Patron " << i << "Resultado : " << result[0] << "\n";
		}

		//delete red;
	}

	void PruebaBP::imprimirMatriz(double** matriz, int filas, int cols)
	{
		cout << "  ";
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int i = 0; i < filas; i++)
		{
			cout << i << " ";

			for (int j = 0; j < cols; j++)
				cout << matriz[i][j] << " ";

			cout << "\n";
		}
	}

	void PruebaBP::imprimirArray(double* arr, int cols)
	{
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int j = 0; j < cols; j++)
			cout << arr[j] << " ";

		cout << "\n";
	}

	void PruebaBP::inicio(const EBP* ebp, void* arg) { }

	void PruebaBP::finCiclo(const EBP* ebp, void* arg) { }

	bool PruebaBP::criterio(const EBP* ebp, void* arg)
	{
		int num_salidas = ebp->getNumSalidas();
		double* errores = ebp->getErrores();
		double sumErr2 = ebp->getError();
		double rms = 0;

		for (int i = 0; i < num_salidas; i++)
			sumErr2 += pow(errores[i], 2);

		rms = sqrt(sumErr2 / ebp->getNumPatrones());

		if (rms == 0.001) return true;

		return false;
	}
}