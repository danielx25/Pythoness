#pragma once

#include <string>
#include <vector>
#include <utility>
#include "VariableLinguistica.h"
#include "SistemaFAM.h"

using namespace std;
using namespace LogicaDifusa;
using namespace STMFAM;

namespace ValidacionRNA
{
	class ValidacionFAM
	{
	public:
		ValidacionFAM(string carpeta_archivos, string archivo_validacion, string archivo_reglas, string archivo_activadas = "");

		~ValidacionFAM();

		void ejecutar(int neuronas, bool mostrar_progreso = false);

		// ordena las reglas de mayor a menor activacion.
		static void ordenarReglasActivacion(vector<pair<int, int>>& activaciones);

		static bool compararActivacion(pair<int, int>& primer_elemento, pair<int, int>& segundo_elemento);

		// agrega las variables linguisticas al Sistema FAM.
		void setVariables(map<string, VariableLinguistica*>& vars, int neuronas);
		
		// agrega las reglas al Sistema FAM.
		void setReglas(vector<string>& reglas);

		// obtiene la estación con un ajuste aplicado.
		double getEstacion(double valor);

		// obtiene la hora con un ajuste aplicado.
		double getHora(double valor);

		// obtiene la direccion del viento con un ajuste aplicado.
		double getDViento(double valor);

		void getRegistros(string archv_validacion, vector<string>& registros);

		string getAlerta(double nivel_mp10);

		bool getAciertoAlerta(double prediccion, double valor_real);

		bool getAciertoNivel(double prediccion, double valor_real);

		void getProgreso(int& registro, double& aciertos_alerta, double& acertividad_alerta, double& aciertos_nivel, double& acertividad_nivel);

		void getProgresoActivaciones(vector<pair<int, int>>& activaciones);

		void actualizarAciertos(double prediccion, double valor_real, double& aciertos_alerta, double& aciertos_nivel);

		void guardarProgreso(double registro, double aciertos_alerta, double acertividad_alerta, double aciertos_nivel, double acertividad_nivel);

		// guarda wl numero de registros, aciertos y la acertividad final.
		void guardarAcertividad(string archivo, double registro, double aciertos_alerta, double acertividad_alerta, double aciertos_nivel, double acertividad_nivel);

		void guardarProgresoActivaciones(vector<pair<int, int>>& activaciones);

		void guardarReglasActivadas(vector<string>& reglas, vector<pair<int, int>>& activaciones, int limite_reglas = 0);

		void variables(vector<string>& variables);

	private:
		string carpeta;
		string archv_reglas;
		string archv_validacion;
		string archv_progreso;
		string archv_aciertos;
		string archv_acertividad;
		string archv_reglas_activadas;
		string archv_progreso_activaciones;
		vector<string> registros;
		SistemaFAM* sfam;
		bool debug_sfam;
	};
}
