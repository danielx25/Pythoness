// Archivo DLL principal.

#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "ControladorFAM.h"
#include "Discretizacion.h"
#include "VariablesLinguisticas.h"
#include "Reglas.h"

using namespace Datos;

namespace Controladores {

	ControladorFAM::ControladorFAM(int nrns)
	{
		string archv_reglas = "_FAM/reglas.pynoess";
		neuronas = nrns;
		sfam = new SistemaFAM();

		VariablesLinguisticas* variableslinguisticas = new VariablesLinguisticas();
		map<string, VariableLinguistica*> vars;
		variableslinguisticas->getVariables(vars);
		double porcentaje = (100.0 / neuronas) / 100.0;

		for (map<string, VariableLinguistica*>::iterator var = vars.begin(); var != vars.end(); ++var)
		{
			double espacio = (var->second->getMaximo() - var->second->getMinimo()) * porcentaje;
			int num_nrns = ((var->second->getMaximo() - var->second->getMinimo()) / espacio) + 1;

			double comienzo = var->second->getMinimo();

			sfam->agregarVariable(var->second);
			sfam->agregarValoresVariable(var->second->getNombre(), comienzo, espacio, num_nrns);
		}

		vector<string> reglas;
		Reglas::leerReglas(archv_reglas, reglas);

		for (vector<string>::iterator regla = reglas.begin(); regla != reglas.end(); ++regla)
			sfam->agregarRegla(*regla);
	}

	void ControladorFAM::setValorVariable(String^% variable, double valor)
	{
		sfam->setValorEntrada(getString(variable), valor);
	}

	double ControladorFAM::prediccion()
	{
		return sfam->getSalida();
	}

	void ControladorFAM::discretizacion(int num_neuronas, String^% archivo_datos, String^% archivo_salida, bool desnormalizar)
	{
		msclr::interop::marshal_context context;
		std::string archv_datos = ControladorFAM::getString(archivo_datos);
		std::string archv_salida = ControladorFAM::getString(archivo_salida);

		Discretizacion::datos(num_neuronas, archv_datos, archv_salida, desnormalizar);
	}

	string ControladorFAM::getString(String^% string_net)
	{
		msclr::interop::marshal_context context;
		std::string string_std = context.marshal_as<std::string>(string_net);

		return string_std;
	}

}