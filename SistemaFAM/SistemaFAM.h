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

		~SistemaFAM();

		void evaluacionReglas(int comienzo, int fin);

		double getSalida(map<string, double>& entrada);
	};
}

#endif