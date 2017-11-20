// Archivo DLL principal.

#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "ControladorFAM.h"
#include "Validacion.h"
#include "Discretizacion.h"
//#include "SOM.h"

using namespace Datos;
using namespace ValidacionRNA;
//using namespace SOM_;

namespace Controladores {

	void ControladorFAM::discretizacion(String^% archivo_datos, String^% archivo_salida, bool desnormalizar)
	{
		msclr::interop::marshal_context context;
		std::string archv_datos = context.marshal_as<std::string>(archivo_datos);
		std::string archv_salida = context.marshal_as<std::string>(archivo_salida);

		Discretizacion::datos(archv_datos, archv_salida, desnormalizar);
	}
}