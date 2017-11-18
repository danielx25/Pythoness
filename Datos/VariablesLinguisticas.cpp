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
		//presion_atmosferica();
		precipitacion("precipitacion_dia1");
		precipitacion("precipitacion_dia2");
		precipitacion("precipitacion_dia3");
		precipitacion("precipitacion_dia4");
		precipitacion("precipitacion_dia5");
		evaporacion("evaporacion");
		/*evaporacion("evaporacion_dia1");
		evaporacion("evaporacion_dia2");
		evaporacion("evaporacion_dia3");
		evaporacion("evaporacion_dia4");
		evaporacion("evaporacion_dia5");*/
		estado("pala1");
		estado("pala3");
		estado("pala4");
		estado("pala5");
		estado("pala7");
		estado("pala8");
		estado("pala10");
		estado("pala11");
		estado("chancador1");
		estado("chancador2");
		chaxa_camion();
		movitec_camion();
		das_camion();
		consumo_agua("cnorte_consumo_agua");
		consumo_agua("cmovil_consumo_agua");
		consumo_agua("cachimba1_consumo_agua");
		consumo_agua("cachimba2_consumo_agua");
		consumo_agua("gerencia_consumo_agua");
		/*cnorte_consumo_agua();
		cmovil_consumo_agua();
		cachimba1_consumo_agua();
		cachimba2_consumo_agua();
		gerencia_consumo_agua();*/
		mp10();
	}

	void VariablesLinguisticas::estacion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 2.5, 14.5);
		variable->agregarValorLinguistico(new ValorLinguistico("fria", new FuncionTriangular(1.0, 4.0, 6.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("helada", new FuncionTriangular(4.0, 6.0, 8.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_helada", new FuncionTriangular(6.0, 8.0, 9.8)));
		variable->agregarValorLinguistico(new ValorLinguistico("calida", new FuncionTriangular(8.0, 9.8, 11.5)));
		variable->agregarValorLinguistico(new ValorLinguistico("calurosa", new FuncionTriangular(9.8, 11.5, 13.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_calurosa", new FuncionTriangular(11.5, 13.0, 17.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::hora(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 1.0, 25.0);
		variable->agregarValorLinguistico(new ValorLinguistico("madrugada", new FuncionTriangular(0.0, 2.0, 7.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("manana", new FuncionTriangular(2.0, 7.0, 12.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("mediodia", new FuncionTriangular(7.0, 12.0, 16.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("tarde", new FuncionTriangular(12.0, 16.0, 20.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("noche", new FuncionTriangular(16.0, 20.0, 24.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("medianoche", new FuncionTriangular(20.0, 24.0, 26.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::velocidad_viento(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 30.0);
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(0.0, 0.0, 2.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(0.0, 2.0, 30.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTrapezoidal(2.0, 30.0, 30.0, 30.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::direccion_viento(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 45.0, 405.0);
		variable->agregarValorLinguistico(new ValorLinguistico("norte", new FuncionTriangular(0.0, 90, 180.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("oeste", new FuncionTriangular(90.0, 180, 270.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("sur", new FuncionTriangular(180.0, 270.0, 360.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("este", new FuncionTriangular(270.0, 360.0, 450.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::temperatura(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 24.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(0.0, 0.0, 2.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(0.0, 2.0, 6.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("fresca", new FuncionTriangular(2.0, 6.0, 12.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("calida", new FuncionTriangular(6.0, 12.0, 18.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("calurosa", new FuncionTriangular(12.0, 18.0, 24.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_calurosa", new FuncionTriangular(18.0, 24.0, 24.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::humedad_relativa(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 100.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(0.0, 0.0, 25.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(0.0, 25.0, 50.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(25.0, 50.0, 75.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(50.0, 75.0, 100.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(75.0, 100.0, 100.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::radiacion_solar(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 1000.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(0.0, 0.0, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(0.0, 250.0, 500.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(250.0, 500.0, 750.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(500.0, 750.0, 1000.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(750.0, 1000.0, 1000.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::presion_atmosferica(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 570.0);
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(0.0, 0.0, 285.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(0.0, 285.0, 570.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(285.0, 570.0, 570.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::precipitacion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 45.0);
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(0.0, 0.0, 22.5)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(0.0, 22.5, 45.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(22.5, 45.0, 45.0)));

		variables[nombre] = variable;
	}


	void VariablesLinguisticas::evaporacion(string nombre)
	{
		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 150.0);
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(0.0, 0.0, 50.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(0.0, 50.0, 100.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(50.0, 100.0, 150.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(100.0, 150.0, 150.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::chaxa_camion(string nombre)
	{
		//vector<string> valores = { "baja", "media", "alta" };
		//funcionGaussiana(nombre, valores, 0.0, 7.0);

		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 7.0);
		variable->agregarValorLinguistico(new ValorLinguistico("bajo", new FuncionTriangular(0.0, 0.0, 3.5)));
		variable->agregarValorLinguistico(new ValorLinguistico("medio", new FuncionTriangular(0.0, 3.5, 7.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alto", new FuncionTriangular(3.5, 7.0, 7.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::movitec_camion(string nombre)
	{
		//vector<string> valores = { "baja", "media", "alta" };
		//funcionGaussiana(nombre, valores, 0.0, 8.0);

		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 8.0);
		variable->agregarValorLinguistico(new ValorLinguistico("bajo", new FuncionTriangular(0.0, 0.0, 4.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("medio", new FuncionTriangular(0.0, 4.0, 8.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alto", new FuncionTriangular(4.0, 8.0, 8.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::das_camion(string nombre)
	{
		//vector<string> valores = { "baja", "media", "alta" };
		//funcionGaussiana(nombre, valores, 0.0, 4.0);

		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 4.0);
		variable->agregarValorLinguistico(new ValorLinguistico("bajo", new FuncionTriangular(0.0, 0.0, 2.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("medio", new FuncionTriangular(0.0, 2.0, 4.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alto", new FuncionTriangular(2.0, 4.0, 4.0)));

		variables[nombre] = variable;
	}

	void VariablesLinguisticas::cnorte_consumo_agua(string nombre)
	{
		/*VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 90240.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(34.96, 250.0)));

		variables[nombre] = variable;*/
	}

	void VariablesLinguisticas::cmovil_consumo_agua(string nombre)
	{
		/*VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 4480.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(34.96, 250.0)));

		variables[nombre] = variable;*/
	}

	void VariablesLinguisticas::cachimba1_consumo_agua(string nombre)
	{
		/*VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 1500.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(34.96, 250.0)));

		variables[nombre] = variable;*/
	}

	void VariablesLinguisticas::cachimba2_consumo_agua(string nombre)
	{
		/*VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 2270.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(34.96, 250.0)));

		variables[nombre] = variable;*/
	}

	void VariablesLinguisticas::gerencia_consumo_agua(string nombre)
	{
		/*VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 27000.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_baja", new FuncionTriangular(34.96, 3.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("baja", new FuncionTriangular(34.96, 6.75)));
		variable->agregarValorLinguistico(new ValorLinguistico("media", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alta", new FuncionTriangular(34.96, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alta", new FuncionTriangular(34.96, 250.0)));

		variables[nombre] = variable;*/
	}

	void VariablesLinguisticas::mp10(string nombre)
	{
		/*vector<string> valores = { "sin_alerta", "alerta_1", "alerta_2", "alerta_3", "alerta_4" };
		funcionGaussiana("mp10", valores, 0.0, 800.0);*/

		VariableLinguistica* variable = new VariableLinguistica("mp10", 0.0, 800.0);
		variable->agregarValorLinguistico(new ValorLinguistico("sin_alerta", new FuncionTriangular(0.0, 0.0, 150.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_1", new FuncionTriangular(100.0, 150.0, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_2", new FuncionTriangular(200.0, 250.0, 350.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_3", new FuncionTriangular(300.0, 350.0, 500.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alerta_4", new FuncionTrapezoidal(450.0, 500.0, 800.0, 800.0)));

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

	void VariablesLinguisticas::consumo_agua(string nombre)
	{
		//vector<string> valores = { "bajo", "medio", "alto" };

		//funcionGaussiana(nombre, valores, 0.0, 1000.0);

		VariableLinguistica* variable = new VariableLinguistica(nombre, 0.0, 1000.0);
		variable->agregarValorLinguistico(new ValorLinguistico("muy_bajo", new FuncionTriangular(0.0, 0.0, 250.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("bajo", new FuncionTriangular(0.0, 250.0, 500.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("medio", new FuncionTriangular(250.0, 500.0, 750.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("alto", new FuncionTriangular(500.0, 750.0, 1000.0)));
		variable->agregarValorLinguistico(new ValorLinguistico("muy_alto", new FuncionTriangular(750.0, 1000.0, 1000.0)));

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

		if (num_valores == 2) ancho = rango * .4247;
		if (num_valores == 3) ancho = rango * .1699;
		else if (num_valores == 4) ancho = rango * .1416;
		else if (num_valores == 5) ancho = rango * .1062;
		else if (num_valores == 6) ancho = rango * .08493;

		for (vector<string>::iterator valor = valores.begin(); valor != valores.end(); ++valor)
		{
			variable->agregarValorLinguistico(new ValorLinguistico(*valor, new FuncionGaussiana(ancho, medio * pos_valor)));
			pos_valor += 1;
		}
		
		variables[nombre] = variable;
	}

	void VariablesLinguisticas::funcionTriangular(string nombre, double minimo, double maximo)
	{
		double rango = maximo - minimo;
		double espacio = rango / 2;

		VariableLinguistica* variable = new VariableLinguistica(nombre, minimo, maximo);

		variable->agregarValorLinguistico(new ValorLinguistico("bajo", new FuncionTriangular(minimo, minimo, (minimo + espacio))));
		variable->agregarValorLinguistico(new ValorLinguistico("medio", new FuncionTriangular(minimo, (minimo + espacio), maximo)));
		variable->agregarValorLinguistico(new ValorLinguistico("alto", new FuncionTriangular((minimo + espacio), maximo, maximo)));

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