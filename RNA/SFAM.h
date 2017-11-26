#pragma once
#pragma once

#ifndef __SFAM_H__
#define __SFAM_H__

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <thread>
#include "FAM.h"
#include "VariableLinguistica.h"

using namespace LogicaDifusa;
using namespace std;

namespace RedNeuronal
{
	class SFAM
	{
	public:
		SFAM();

		~SFAM();

		void agregarVariable(VariableLinguistica*& variable);

		void agregarValoresVariable(string variable, double comienzo, double espacio, int num_vals);

		void agregarRegla(string regla);

		void fuzzificacion(ValorLinguistico*& valor, double*& vals_vars, int num_vals, double*& grados_vals_var);

		void inferenciaDescomposicional(double**& salidas, int num_salidas, int num_vals, string operador, double*& salida);

		void evaluacionRegla(map<string, string>& vars, string& consecuente, string& val_consc, string& operador, double*& salida);

		void setValorEntrada(string variable, double valor);

		void getCapaSuma(double**& salidas, int num_salidas, int num_vals, double*& suma);

		double getCentroide(double*& suma, double*& vals_consc, int num_vals);

		void getElementosRegla(const string& regla, map<string, string>& vars, string& var_consc, string& val_consc, string& operador);

		void getBitVector(string variable, double valor_entrada, double*& bit_vector);

		void getValores(string variable, double*& valores);

		void getGradosValores(string variable, string valor, double*& grados);

		void getReglas(vector<string>& r);

		double getSalida();

		virtual double getSalida(map<string, double>& entrada) = 0;

	protected:
		map<string, VariableLinguistica*> variables;
		map<string, double*> valores_variables;
		map<string, map<string, double*>> grados_vals_vars;
		map<string, int> num_vals_vars;
		vector<string> reglas;
		map<string, double> entrada;
		double** salida_reglas;
		pair<int, int> args_h1;
		pair<int, int> args_h2;
	};
}

#endif