#pragma once

#ifndef __VARLINGUISTICA_H__
#define __VARLINGUISTICA_H__

#include "VariableLinguistica.h"
#include <string>
#include <vector>
#include <map>

using namespace LogicaDifusa;

namespace Datos
{
	// Clase para una funcion de pertenencia.
	class VariablesLinguisticas
	{
	public:
		VariablesLinguisticas();

		// Destructor virtual para una correcta limpieza.
		//~VariablesLinguisticas() {}

		void estacion();

		void hora();

		void velocidad_viento();
		
		void direccion_viento();
		
		void temperatura();
		
		void humedad_relativa();
		
		void radiacion_solar();
		
		void presion_atmosferica();
		
		void precipitacion_dia1();
		
		void precipitacion_dia2();
		
		void precipitacion_dia3();
		
		void precipitacion_dia4();
		
		void precipitacion_dia5();
		
		void evaporacion_dia1();
		
		void evaporacion_dia2();
		
		void evaporacion_dia3();
		
		void evaporacion_dia4();
		
		void evaporacion_dia5();
		
		// las palas y chancadores poseen la misma variable linguistica.
		void estado(string nombre);

		void chaxa_camion();

		void movitec_camion();

		void das_camion();
		
		void cnorte_consumo_agua();
		
		void cmovil_consumo_agua();

		void cachimba1_consumo_agua();

		void cachimba2_consumo_agua();
		
		void gerencia_consumo_agua();

		void mp10();

		void funcionGaussiana(string nombre, vector<string> valores, double minimo, double maximo);

		void getVariable(string nombre, VariableLinguistica*& variable);

		void getVariables(map<string, VariableLinguistica*>& vars) const;

	private:
		map<string, VariableLinguistica*> variables;
	};
}

#endif