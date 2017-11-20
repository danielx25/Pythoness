// Controladores.h

#pragma once

#include <string>

using namespace System;
using namespace std;

namespace Controladores {

	public ref class ControladorFAM
	{
	public:
		static void discretizacion(String^% archivo_datos, String^% archivo_salida, bool desnormalizar);
	};
}
