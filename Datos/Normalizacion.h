#pragma once

#ifndef __NORMALIZACION_H__
#define __NORMALIZACION_H__

namespace Datos
{
	class Normalizacion
	{
	public:
		static double desnormalizar(double normalizado, double minimo, double maximo);
	};
}

#endif