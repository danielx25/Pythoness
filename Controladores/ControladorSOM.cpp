#include "stdafx.h"
#include "ControladorSOM.h"
#include <msclr\marshal_cppstd.h>
namespace Controladores {

	ControladorSOM::ControladorSOM()
	{
	}


	void ControladorSOM::obtenerValoresConfiguracion()
	{
		FicheroRNA::leerConfiguracion();
	}

	String^ ControladorSOM::getDireccion()
	{
		return msclr::interop::marshal_as<String^>(Configuracion::RUTA_ARCHIVO);
	}
	int ControladorSOM::getNumeroEntradas()
	{
		return Configuracion::NUMERO_ENTRADAS;
	}
	int ControladorSOM::getNumetoNeuronas()
	{
		return Configuracion::NUMERO_NEURONAS;
	}
	int ControladorSOM::getLargo()
	{
		return Configuracion::LARGO;
	}
	int ControladorSOM::getAncho()
	{
		return Configuracion::ANCHO;
	}
	double ControladorSOM::getAlfa()
	{
		return Configuracion::ALFA;
	}
	double ControladorSOM::getBeta()
	{
		return Configuracion::BETA;
	}
	int ControladorSOM::getRangoVecindad()
	{
		return Configuracion::RANGO_VECINDAD;
	}


	void ControladorSOM::cambiarValoresConfiguracion(String^ direc, int n_entrada, int n_neurona, int largo, int ancho, double alfa, double beta, int rangoVecindad)
	{
		Configuracion::RUTA_ARCHIVO = msclr::interop::marshal_as<std::string>(direc);
		Configuracion::NUMERO_ENTRADAS = n_entrada;
		Configuracion::NUMERO_NEURONAS = n_neurona;
		Configuracion::LARGO = largo;
		Configuracion::ANCHO = ancho;
		Configuracion::ALFA = alfa;
		Configuracion::BETA = beta;
		Configuracion::RANGO_VECINDAD = rangoVecindad;
		FicheroRNA::crearConfiguracion();

	}

	void ControladorSOM::iniciarSOM()
	{
		FicheroRNA::crearConfiguracion();
		/*double ejemplo1[30][4] = {
		{ 0.25, 0.375, 0.428571428571, 0.25 },
		{ 0.583333333333, 0.625, 0.428571428571, 0.598484848485 },
		{ 0.333333333333, 1.0, 0.571428571429, 0.719696969697 },
		{ 0.75, 0.625, 0.428571428571, 0.704545454545 },
		{ 0.5, 0.0, 0.428571428571, 0.204545454545 },
		{ 0.333333333333, 1.0, 0.428571428571, 0.643939393939 },
		{ 0.25, 0.125, 0.857142857143, 0.340909090909 },
		{ 0.75, 0.375, 0.0, 0.340909090909 },
		{ 0.25, 0.75, 0.714285714286, 0.606060606061 },
		{ 0.666666666667, 0.125, 0.142857142857, 0.227272727273 },
		{ 0.583333333333, 0.25, 0.428571428571, 0.393939393939 },
		{ 0.166666666667, 0.5, 0.714285714286, 0.416666666667 },
		{ 0.166666666667, 0.5, 0.714285714286, 0.416666666667 },
		{ 0.583333333333, 0.375, 0.857142857143, 0.689393939394 },
		{ 0.5, 0.625, 0.142857142857, 0.393939393939 },
		{ 0.0, 0.875, 0.0, 0.136363636364 },
		{ 1.0, 0.375, 0.285714285714, 0.651515151515 },
		{ 0.416666666667, 0.0, 0.142857142857, 0.0 },
		{ 0.0, 0.625, 0.285714285714, 0.151515151515 },
		{ 0.166666666667, 0.5, 1.0, 0.568181818182 },
		{ 0.75, 0.125, 0.142857142857, 0.280303030303 },
		{ 0.666666666667, 0.875, 0.571428571429, 0.863636363636 },
		{ 0.166666666667, 0.125, 0.571428571429, 0.136363636364 },
		{ 0.0833333333333, 0.25, 1.0, 0.378787878788 },
		{ 0.416666666667, 1.0, 1.0, 1.0 },
		{ 0.333333333333, 0.625, 0.142857142857, 0.287878787879 },
		{ 0.0, 0.375, 0.428571428571, 0.0909090909091 },
		{ 0.5, 0.5, 0.142857142857, 0.325757575758 },
		{ 1.0, 0.375, 0.714285714286, 0.878787878788 },
		{ 0.0833333333333, 0.375, 1.0, 0.44696969697 }
		};

		double **matriz = new double*[30];

		for (int i = 0; i < 30; i++)
		{
		matriz[i] = new double[4];
		}

		GestionadorSOM* managerSom = new GestionadorSOM();
		managerSom->inicializarSOM(matriz, 30, 4);
		//managerSom->empezarEntrenamiento();
		throw gcnew System::NotImplementedException();*/
	}



}
