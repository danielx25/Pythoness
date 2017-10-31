#include "stdafx.h"
#include "Normalizacion.h"

namespace Datos
{
	double Normalizacion::desnormalizar(double normalizado, double minimo, double maximo)
	{
		double valor = (normalizado * (maximo - minimo)) + minimo;

		return valor;
	}

}