// Controladores.h

#pragma once

#include <string>
#include "SFAM.h"
#include "SistemaFAM.h"

using namespace System;
using namespace std;
using namespace RNAs;

namespace Controladores {

	public ref class ControladorFAM
	{
	public:
		ControladorFAM(int nrns);

		static void discretizacion(String^% archivo_datos, String^% archivo_salida, bool desnormalizar);

		void setValorVariable(String^% variable, double valor);

		double prediccion();

		static string getString(String^% string_net);

	private:
		SistemaFAM* sfam;
		int neuronas;
	};
}
