// Archivo DLL principal.

#include "stdafx.h"
#include "ControladorRNA.h"
#include "Validacion.h"

using namespace ValidacionRNA;

namespace Controladores {

	void ControladorRNA::validacion(/*String archv_validacion, String archv_reglas*/)
	{
		string archv_validacion = "C:\\Users\\Sefirot\\Documents\\Visual Studio 2017\\Projects\\Pythoness\\PruebasCS\\bin\\Debug\\validacion.csv";
		string archv_reglas = "C:\\Users\\Sefirot\\Documents\\Visual Studio 2017\\Projects\\Pythoness\\Pruebas\\reglas.txt";

		Validacion::validacionFAM(archv_validacion, archv_reglas);
	}
}