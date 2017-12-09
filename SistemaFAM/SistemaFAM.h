#pragma once

#ifndef __SFAMCH_H__
#define __SFAMCH_H__

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <thread>
#include "FAM.h"
#include "SFAM.h"
#include "VariableLinguistica.h"

using namespace RedNeuronal;
using namespace LogicaDifusa;
using namespace std;

namespace STMFAM
{
	class SistemaFAM : public SFAM
	{
	public:
		SistemaFAM();

		// Constructor. Especifica si se genera informacion de la ejecucion del Sistema FAM.
		SistemaFAM(bool dbg);

		~SistemaFAM();

		void evaluacionReglas(int comienzo, int fin);

		// setea todas las reglas en cero activaciones.
		void setActivacionesReglas();

		void setActivacionesReglas(vector<pair<int, int>>& activaciones);

		void getActivacionesReglas(vector<pair<int, int>>& activaciones);

		double getSalida(map<string, double>& entrada);
	private:
		bool debug;
		vector<pair<int, int>> activaciones_reglas;

		// si la matriz contiene al menos un elemento mayor a cero, retorna true.
		bool esVerdad(double*& matriz, int num_nrns);
	};
}

#endif