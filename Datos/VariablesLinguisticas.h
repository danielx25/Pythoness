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

		void estacion(string nombre = "estacion");

		void hora(string nombre = "hora");

		void velocidad_viento(string nombre = "velocidad_viento");
		
		void direccion_viento(string nombre = "direccion_viento");
		
		void temperatura(string nombre = "temperatura");
		
		void humedad_relativa(string nombre = "humedad_relativa");
		
		void radiacion_solar(string nombre = "radiacion_solar");
		
		void presion_atmosferica(string nombre = "presion_atmosferica");
		
		void precipitacion(string nombre);

		void evaporacion(string nombre);
		
		// las palas y chancadores poseen la misma variable linguistica.
		void estado(string nombre);

		void chaxa_camion(string nombre = "chaxa_camion");

		void movitec_camion(string nombre = "movitec_camion");

		void das_camion(string nombre = "das_camion");
		
		void consumo_agua(string nombre = "cnorte_consumo_agua");

		void cnorte_consumo_agua(string nombre = "cnorte_consumo_agua");
		
		void cmovil_consumo_agua(string nombre = "cmovil_consumo_agua");

		void cachimba1_consumo_agua(string nombre = "cachimba1_consumo_agua");

		void cachimba2_consumo_agua(string nombre = "cachimba2_consumo_agua");
		
		void gerencia_consumo_agua(string nombre = "gerencia_consumo_agua");

		void mp10(string nombre = "mp10");

		void funcionGaussiana(string nombre, vector<string> valores, double minimo, double maximo);

		void getVariable(string nombre, VariableLinguistica*& variable);

		void getVariables(map<string, VariableLinguistica*>& vars) const;

	private:
		map<string, VariableLinguistica*> variables;
	};
}

#endif