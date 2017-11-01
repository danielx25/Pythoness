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
		precipitacion("precipitacion_dia1");
		precipitacion("precipitacion_dia2");
		precipitacion("precipitacion_dia3");
		precipitacion("precipitacion_dia4");
		precipitacion("precipitacion_dia5");
		evaporacion("evaporacion_dia1");
		evaporacion("evaporacion_dia2");
		evaporacion("evaporacion_dia3");
		evaporacion("evaporacion_dia4");
		evaporacion("evaporacion_dia5");
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

	void VariablesLinguisticas::estacion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 1.0, 14.0);
		variable->agregarValorLinguistico(new ValorLinguistico("otono", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("invierno", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("primavera", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("verano", new FuncionGaussiana(50.96, 350.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::hora(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 12.0);
		variable->agregarValorLinguistico(new ValorLinguistico("amanecer", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("manana", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("mediodia", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("tarde", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("atardecer", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("anochecer", new FuncionGaussiana(50.96, 350.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("noche", new FuncionGaussiana(50.96, 350.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("transnoche", new FuncionGaussiana(50.96, 350.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::velocidad_viento(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 12.0);
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionCampana(34.96, 5, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionCampana(34.96, 5, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::direccion_viento(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 360.0);
		variable->agregarValorLinguistico(new ValorLinguistico("norte", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("oeste", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("sur", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("este", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::temperatura(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 1.0, 24.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("fresca", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("calurosa", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_calurosa", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::humedad_relativa(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 1.0, 24.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::radiacion_solar(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 1700.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::presion_atmosferica(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 2860.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::precipitacion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 2860.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}


	void VariablesLinguisticas::evaporacion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 36300000.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::chaxa_camion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 7.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::movitec_camion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 8.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::das_camion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 4.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::cnorte_consumo_agua(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 90240.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::cmovil_consumo_agua(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 4480.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::cachimba1_consumo_agua(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 1500.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::cachimba2_consumo_agua(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 2270.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::gerencia_consumo_agua(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 27000.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionGaussiana(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionGaussiana(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionGaussiana(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionGaussiana(34.96, 250.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::mp10(string nombre)
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