#include "stdafx.h"
#include <iostream>
#include "PruebasSFAM.h"
#include "VariableLinguistica.h"
#include "FuncionTriangular.h"
#include "FuncionTrapezoidal.h"

using namespace std;
using namespace LogicaDifusa;

namespace PruebasRed
{
	PruebasSFAM::PruebasSFAM()
	{
		sfam = new SistemaFAM();

		VariableLinguistica* temperatura = new VariableLinguistica("Temperatura", 9.0, 37.0);
		temperatura->agregarValorLinguistico(new ValorLinguistico("fresca", new FuncionTriangular(9.0, 15.0, 21.0)));
		temperatura->agregarValorLinguistico(new ValorLinguistico("agradable", new FuncionTriangular(17.0, 23.0, 29.0)));
		temperatura->agregarValorLinguistico(new ValorLinguistico("calida", new FuncionTriangular(25.0, 31.0, 36.0)));
		sfam->agregarVariable(temperatura);

		VariableLinguistica* velocidad = new VariableLinguistica("Velocidad", 10.0, 50.0);
		velocidad->agregarValorLinguistico(new ValorLinguistico("lenta", new FuncionTrapezoidal(10.0, 18.05, 21.95, 30.0)));
		velocidad->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTrapezoidal(20.0, 28.05, 31.95, 40.0)));
		velocidad->agregarValorLinguistico(new ValorLinguistico("rapida", new FuncionTrapezoidal(30.0, 38.05, 41.95, 50.0)));
		sfam->agregarVariable(velocidad);

		int num_vals_temp = 6;
		int num_vals_vel = 5;

		sfam->agregarValoresVariable("Temperatura", 15.0, 3.0, num_vals_temp);
		sfam->agregarValoresVariable("Velocidad", 20.0, 5.0, num_vals_vel);

		double* valores_temp;
		double* valores_vel;
		double** grados_vals = new double*[6];

		sfam->getValores("Temperatura", valores_temp);
		sfam->getValores("Velocidad", valores_vel);
		sfam->getGradosValores("Temperatura", "fresca", grados_vals[0]);
		sfam->getGradosValores("Temperatura", "agradable", grados_vals[1]);
		sfam->getGradosValores("Temperatura", "calida", grados_vals[2]);
		sfam->getGradosValores("Velocidad", "lenta", grados_vals[3]);
		sfam->getGradosValores("Velocidad", "media", grados_vals[4]);
		sfam->getGradosValores("Velocidad", "rapida", grados_vals[5]);

		double* bit;

		sfam->getBitVector("Temperatura", 18.0, bit);

		//cout << "Pesos\n";
		//imprimirMatriz(pesos, nna, nnb);
		cout << "\nValores Velocidad\n";
		imprimirArray(valores_vel, num_vals_vel);
		cout << "\nValores Temperatura\n";
		imprimirArray(valores_temp, num_vals_temp);
		cout << "\nBit Vector\n";
		imprimirArray(bit, num_vals_temp);
		cout << "\nGrados fresca\n";
		imprimirArray(grados_vals[0], num_vals_temp);
		cout << "\nGrados agradable\n";
		imprimirArray(grados_vals[1], num_vals_temp);
		cout << "\nGrados calida\n";
		imprimirArray(grados_vals[2], num_vals_temp);

		cout << "\nGrados lenta\n";
		imprimirArray(grados_vals[3], num_vals_vel);
		cout << "\nGrados media\n";
		imprimirArray(grados_vals[4], num_vals_vel);
		cout << "\nGrados rapida\n";
		imprimirArray(grados_vals[5], num_vals_vel);

		sfam->agregarRegla("Si Temperatura es fresca entonces Velocidad es lenta");
		sfam->agregarRegla("Si Temperatura es agradable entonces Velocidad es media");
		sfam->agregarRegla("Si Temperatura es calida entonces Velocidad es rapida");

		vector<string> reglas;
		string consecuente;
		
		sfam->getReglas(reglas);

		cout << "\nReglas\n";
		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
		{
			cout << *regla << "\n";
		
			map<string, string> vars;
			string val_consc;
			string operador;

			sfam->getElementosRegla(*regla, vars, consecuente, val_consc, operador);

			cout << "\nVariables regla\n";
			for (map<string, string>::iterator var = vars.begin(); var != vars.end(); ++var)
				cout << "Variable: " << var->first << " Valor: " << var->second << "\n";

			cout << "Consecuente: " << consecuente << " Valor: " << val_consc << "\n";
			cout << "Operador: " << operador << "\n";
			cout << "\n";
		}

		map<string, double> entrada;

		entrada["Temperatura"] = 18;

		cout << "Salida: " << sfam->getSalida(entrada) << "\n";

		int num_salidas = 5;
		int num_vals = 6;
		double** salidas = new double*[num_salidas];
		double* salida_min = new double[num_vals];
		double* salida_max = new double[num_vals];

		salidas[0] = new double[num_vals];
		salidas[1] = new double[num_vals];
		salidas[2] = new double[num_vals];
		salidas[3] = new double[num_vals];
		salidas[4] = new double[num_vals];

		salidas[0][0] = 21; salidas[0][1] = 16; salidas[0][2] = 72;
		salidas[0][3] = 1; salidas[0][4] = 63; salidas[0][5] = 51;
		
		salidas[1][0] = 11; salidas[1][1] = 64; salidas[1][2] = 129;
		salidas[1][3] = 46; salidas[1][4] = 39; salidas[1][5] = 15;
		
		salidas[2][0] = 2; salidas[2][1] = 12; salidas[2][2] = 59;
		salidas[2][3] = 1; salidas[2][4] = 44; salidas[2][5] = 61;

		salidas[3][0] = 13; salidas[3][1] = 48; salidas[3][2] = 29;
		salidas[3][3] = 15; salidas[3][4] = 139; salidas[3][5] = 15;

		salidas[4][0] = 91; salidas[4][1] = 71; salidas[4][2] = 20;
		salidas[4][3] = 43; salidas[4][4] = 30; salidas[4][5] = 14;

		sfam->inferenciaDescomposicional(salidas, num_salidas, num_vals, "y", salida_min);
		
		cout << "\nMinimo\n";
		imprimirArray(salida_min, num_vals);
		
		sfam->inferenciaDescomposicional(salidas, num_salidas, num_vals, "o", salida_max);

		cout << "\nMaximo\n";
		imprimirArray(salida_max, num_vals);
	}

	void PruebasSFAM::imprimirMatriz(double**& matriz, int filas, int cols)
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

	void PruebasSFAM::imprimirArray(double*& arr, int cols)
	{
		for (int j = 0; j < cols; j++)
			cout << j << " ";

		cout << "\n";

		for (int j = 0; j < cols; j++)
			cout << arr[j] << " ";

		cout << "\n";
	}
}