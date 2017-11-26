#pragma once
#pragma once

#ifndef __SFAMSH_H__
#define __SFAMSH_H__

#include <string>
#include <vector>
#include <map>
#include <utility>
#include "FAM.h"
#include "SFAM.h"
#include "VariableLinguistica.h"

using namespace RedNeuronal;
using namespace LogicaDifusa;
using namespace std;

namespace RNAs
{
	class SistemaFAM : public SFAM
	{
	public:
		SistemaFAM();

		~SistemaFAM();

		double getSalida();

		double getSalida(map<string, double>& entrada);
	};
}

#endif