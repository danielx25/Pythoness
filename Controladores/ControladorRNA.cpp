// Archivo DLL principal.

#include "stdafx.h"
#include "ControladorRNA.h"
#include "Validacion.h"

using namespace ValidacionRNA;

namespace Controladores {

	void ControladorRNA::validacion()
	{
		string archv_validacion = "validacion.csv";
		string archv_reglas = "reglas.txt";

		Validacion::validacionFAM(archv_validacion, archv_reglas);
	}
}