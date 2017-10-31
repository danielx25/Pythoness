#include "stdafx.h"
#include "VariablesLinguisticas.h"
#include "FuncionTriangular.h"
#include "FuncionTrapezoidal.h"
#include "FuncionGaussiana.h"
#include "FuncionCampana.h"

namespace Datos
{

	VariablesLinguisticas::VariablesLinguisticas() 
	{
		estacion();
		hora();
		velocidad_viento();
		direccion_viento();
		temperatura();
		humedad_relativa();
		radiacion_solar();
		presion_atmosferica();
		precipitacion_dia1();
		precipitacion_dia2();
		precipitacion_dia3();
		precipitacion_dia4();
		precipitacion_dia5();
		evaporacion_dia1();
		evaporacion_dia2();
		evaporacion_dia3();
		evaporacion_dia4();
		evaporacion_dia5();
		estado("pala1");
		estado("pala2");
		estado("pala3");
		estado("pala4");
		estado("pala5");
		estado("pala6");
		estado("pala7");
		estado("pala8");
		estado("chancador1");
		estado("chancador2");
		chaxa_camion();
		movitec_camion();
		das_camion();
		cnorte_consumo_agua();
		cmovil_consumo_agua();
		cachimba1_consumo_agua();
		cachimba2_consumo_agua();
		gerencia_consumo_agua();
		mp10();
	}

	void VariablesLinguisticas::estacion()
	{
		vector<string> valores = { "verano", "invierno", "verano_2" };
		funcionGaussiana("estacion", valores, 0.5, 12.5);
	}

	void VariablesLinguisticas::hora()
	{
		vector<string> valores = { "manana", "tarde", "noche" };
		funcionGaussiana("hora", valores, 0.0, 24.0);
	}

	void VariablesLinguisticas::velocidad_viento()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("velocidad_viento", valores, 0.0, 30.0);
	}

	void VariablesLinguisticas::direccion_viento()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("direccion_viento", valores, 0.0, 360.0);
	}

	void VariablesLinguisticas::temperatura()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("temperatura", valores, -10.0, 55.0);
	}

	void VariablesLinguisticas::humedad_relativa()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("humedad_relativa", valores, 0.0, 100.0);
	}

	void VariablesLinguisticas::radiacion_solar()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("radiacion_solar", valores, 0.0, 1700.0);
	}

	void VariablesLinguisticas::presion_atmosferica()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("presion_atmosferica", valores, 0.0, 600.0);
	}

	void VariablesLinguisticas::precipitacion_dia1()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("precipitacion_dia1", valores, 0.0, 2860.0);
	}

	void VariablesLinguisticas::precipitacion_dia2()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("precipitacion_dia2", valores, 0.0, 2860.0);
	}

	void VariablesLinguisticas::precipitacion_dia3()
	{
		vector<string> valores = {"baja", "media", "alta"};
		funcionGaussiana("precipitacion_dia3", valores, 0.0, 2860.0);
	}

	void VariablesLinguisticas::precipitacion_dia4()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("precipitacion_dia4", valores, 0.0, 2860.0);
	}

	void VariablesLinguisticas::precipitacion_dia5()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("precipitacion_dia5", valores, 0.0, 2860.0);
	}

	void VariablesLinguisticas::evaporacion_dia1()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("evaporacion_dia1", valores, 0.0, 36300000.0);
	}

	void VariablesLinguisticas::evaporacion_dia2()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("evaporacion_dia2", valores, 0.0, 36300000.0);
	}

	void VariablesLinguisticas::evaporacion_dia3()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("evaporacion_dia3", valores, 0.0, 36300000.0);
	}

	void VariablesLinguisticas::evaporacion_dia4()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("evaporacion_dia4", valores, 0.0, 36300000.0);
	}

	void VariablesLinguisticas::evaporacion_dia5()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("evaporacion_dia5", valores, 0.0, 36300000.0);
	}

	void VariablesLinguisticas::chaxa_camion()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("chaxa_camion", valores, 0.0, 7.0);
	}

	void VariablesLinguisticas::movitec_camion()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("movitec_camion", valores, 0.0, 8.0);
	}

	void VariablesLinguisticas::das_camion()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("das_camion", valores, 0.0, 4.0);
	}

	void VariablesLinguisticas::cnorte_consumo_agua()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("cnorte_consumo_agua", valores, 0.0, 90240.0);
	}

	void VariablesLinguisticas::cmovil_consumo_agua()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("cmovil_consumo_agua", valores, 0.0, 4480.0);
	}

	void VariablesLinguisticas::cachimba1_consumo_agua()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("cachimba1_consumo_agua", valores, 0.0, 1500.0);
	}

	void VariablesLinguisticas::cachimba2_consumo_agua()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("cachimba2_consumo_agua", valores, 0.0, 2270.0);
	}

	void VariablesLinguisticas::gerencia_consumo_agua()
	{
		vector<string> valores = { "baja", "media", "alta" };
		funcionGaussiana("gerencia_consumo_agua", valores, 0.0, 27000.0);
	}

	void VariablesLinguisticas::mp10()
	{
		/*vector<string> valores = { "sin_alerta", "alerta_1", "alerta_2", "alerta_3", "alerta_4" };
		funcionGaussiana("mp10", valores, 0.0, 800.0);*/

		VariableLinguistica* variable = new VariableLinguistica("mp10", 0.0, 800.0);
		variable->agregarValorLinguistico(new ValorLinguistico("sin_alerta", new FuncionGaussiana(34.96, 0.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_1", new FuncionGaussiana(34.96, 150.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_2", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_3", new FuncionGaussiana(50.96, 350.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_4", new FuncionCampana(350.0, 20.0, 800.0)));

		variables["mp10"] = variable;
	}

	// las palas y chancadores poseen la misma variable linguistica.
	void VariablesLinguisticas::estado(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 1.0);
		variable->agregarValorLinguistico(new ValorLinguistico("detenido", new FuncionTriangular(0.0, 00, 0.5)));
		variable->agregarValorLinguistico(new ValorLinguistico("activo", new FuncionTriangular(0.0, 1.0, 1.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::funcionGaussiana(string nombre, vector<string> valores, double minimo, double maximo)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, minimo, maximo);
		double pos_valor = 0;
		double rango = maximo - minimo;
		double num_valores = valores.size();
		double ancho = 0;
		double medio = rango / (num_valores - 1);

		if (num_valores == 3) ancho = rango * .1699;
		else if (num_valores == 5) ancho = rango * .1062;

		for (vector<string>::iterator valor = valores.begin(); valor != valores.end(); ++valor)
		{
			variable->agregarValorLinguistico(new ValorLinguistico(*valor, new FuncionGaussiana(ancho, medio * pos_valor)));
			pos_valor += 1;
		}
		
		variables[nombre] = variable;
	}

	void VariablesLinguisticas::getVariable(string nombre, VariableLinguistica*& variable) 
	{
		variable = variables[nombre];
	}

	void VariablesLinguisticas::getVariables(map<string, VariableLinguistica*>& vars) const
	{
		vars = variables;
	}
}