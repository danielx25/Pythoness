#pragma once
//#include "gestionadorsom.h"
#include "configuracion.h"
#include "ficherorna.h"
#include <string>

using namespace System;
using namespace std;

namespace Controladores {

	public class config
	{
	public:
		string direc1;
		int n_entrada;
		int n_neurona;
		int largo;
		int ancho;
		double alfa;
		double beta;
		int rangoVecindad;
	};


	public ref class ControladorSOM
	{
	public:
		ControladorSOM();
		static void iniciarSOM();
		static void cambiarValoresConfiguracion(String^ direc, int n_entrada, int n_neurona, int largo, int ancho, double alfa, double beta, int rangoVecindad);
		static void obtenerValoresConfiguracion();

		static String^ getDireccion();
		static int getNumeroEntradas();
		static int getNumetoNeuronas();
		static int getLargo();
		static int getAncho();
		static double getAlfa();
		static double getBeta();
		static int getRangoVecindad();
	
	};

}


