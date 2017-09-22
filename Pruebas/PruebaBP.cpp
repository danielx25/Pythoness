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
		string linea;
		ifstream archv_entrenamiento("C:\\Users\\Sefirot\\Documents\\Visual Studio 2015\\Projects\\Pythoness\\Debug\\iris\\entrenamiento.data");
		ifstream archv_validacion("C:\\Users\\Sefirot\\Documents\\Visual Studio 2015\\Projects\\Pythoness\\Debug\\iris\\validacion.data");
		int columna = 0;
		string valor;
		int patron = 0;
		int patrones = 105;
		int num_entrada = 4;

		nc = 3;
		nnc = new int[nc];
		t = .1;

		nnc[0] = 4;
		nnc[1] = 4;
		nnc[2] = 3;

		EBP* ebp = new EBP(patrones, num_entrada, nc, nnc, t);
		//ebp->setInicio(inicio(), NULL);

		if (archv_entrenamiento.is_open())
		{
			while (std::getline(archv_entrenamiento, linea))
			{
				cout << "Lectura datos entrenamiento\n";

				columna = 0;
				std::stringstream ss(linea);

				while (std::getline(ss, valor, ','))
				{
					//cout << columna << " " << valor << "\n";
					if (columna == 4)
					{
						double* salidas = new double[3];
						salidas[0] = 0;
						salidas[1] = 0;
						salidas[2] = 0;

						if (valor == "Iris-setosa") salidas[0] = 1;
						else if (valor == "Iris-versicolor") salidas[1] = 1;
						else if (valor == "Iris-virginica") salidas[2] = 1;

						ebp->setSalida(patron, 0, salidas[0]);
						ebp->setSalida(patron, 1, salidas[1]);
						ebp->setSalida(patron, 2, salidas[2]);
					}
					else 
					{
						ebp->setValor(patron, columna, stod(valor));
					}

					columna += 1;
				}

				patron += 1;
			}
			archv_entrenamiento.close();

			cout << "Entrenamiento\n";
			red = new BP(nc, nnc, ebp->online());

			cout << "Ejecucion\n";
			patron = 0;
			while (std::getline(archv_validacion, linea))
			{
				//cout << "Lectura datos validacion\n";
				double* entradas = new double[num_entrada];
				columna = 0;
				std::stringstream ss(linea);

				while (std::getline(ss, valor, ','))
				{
					//cout << valor << " Lectura datos validacion\n";
					if (columna == 4)
					{
						double* result = red->ejecutar(entradas);

						if (result[0] == 1) cout << "Patron: " << patron << " Clase: " << valor << " Predicción: Iris-setosa\n";
						else if (result[1] == 1) cout << "Patron: " << patron << " Clase: " << valor << " Predicción: Iris-versicolor\n";
						else if (result[2] == 1) cout << "Patron: " << patron << " Clase: " << valor << " Predicción: Iris-virginica\n";
						else cout << "Patron: " << patron << " Clase: " << valor << " Predicción: Sin clase Resultados: " << result[0] << " " << result[1] << " " << result[2]  << "\n";
					}
					else
					{
						entradas[columna] = stod(valor);
					}

					columna += 1;
				}

				patron += 1;
			}
			archv_validacion.close();
		}

		//cout << "No entro al for";

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