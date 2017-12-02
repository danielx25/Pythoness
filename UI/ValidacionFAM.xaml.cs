using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using UI.graficos;
//using Controladores;

namespace UI
{
    /// <summary>
    /// Lógica de interacción para ValidacionFAM.xaml
    /// </summary>
    public partial class ValidacionFAM : UserControl
    {
        string[] variables;

        public ValidacionFAM()
        {
            InitializeComponent();
        }

        public void validacion(string archv_validacion, string archv_progreso)
        {
            //ControladorFAM cfam = new ControladorFAM();
            /*string[] filas = File.ReadAllLines(archv_validacion);
            int progreso = 0;
            int respaldo = 0;
            int registro = 0;
            int aciertos = 0;
            int linea_actual = 0;
            int rango = 10;

            //cfam

            setVariables();

            graficoValidacion.SetAxisLimits(1, rango);

            // cargamos el progreso previo si existiera alguno.
            Tuple<int, int> datos_progreso = getProgreso(archv_progreso);

            respaldo = datos_progreso.Item1;
            aciertos = datos_progreso.Item2;

            for (int i = (respaldo- 1); i < filas.Length; i++)
            {
                registro += 1;

                if (respaldo == 0 || registro > respaldo)
                {
                    string[] datos = filas[i].Split(';');
                    int posicion = 0;
                    double valor_mp10 = 0;

                    for (int j = 0; j < datos.Length; j++)
                    {
                        double valor = Convert.ToDouble(datos[j]);
                        string nom_var = variables[posicion];

                        if (nom_var != "mp10")
                        {
                            

                            posicion += 1;
                        }
                        else
                        {
                            valor_mp10 = valor;
                        }
                    }
                }

                //Thread.Sleep(150);
                graficoValidacion.ChartValues.Add(new Coordenadas
                {
                    X = i,
                    Y = i
                });

                if (graficoValidacion.ChartValues.Count > rango)
                {
                    int max = graficoValidacion.AxisMax + 1;
                    int min = graficoValidacion.AxisMin + 1;

                    graficoValidacion.SetAxisLimits(min, max);
                    graficoValidacion.ChartValues.RemoveAt(0);
                }
            }*/
        }

        private Tuple<int, int> getProgreso(string archivo)
        {
            int registros = 1;
            int aciertos = 0;

            if (File.Exists(archivo))
            {
                string[] lineas = File.ReadAllLines(archivo);
                string[] datos_progreso = lineas[0].Split(';');

                registros = Convert.ToInt32(datos_progreso[0]);
                aciertos = Convert.ToInt32(datos_progreso[1]);
            }

            Tuple<int, int> datos = new Tuple<int, int>(registros, aciertos);

            return datos;
        }
    
        private void setVariables()
        {
            variables[0] = "estacion"; 
            variables[1] = "hora"; 
            variables[2] = "velocidad_viento"; 
            variables[3] = "direccion_viento"; 
            variables[4] = "temperatura"; 
            variables[5] = "humedad_relativa"; 
            variables[6] = "radiacion_solar"; 
            variables[7] = "precipitacion_dia1"; 
            variables[8] = "precipitacion_dia2"; 
            variables[9] = "precipitacion_dia3"; 
            variables[10] = "precipitacion_dia4"; 
            variables[11] = "precipitacion_dia5"; 
            variables[12] = "evaporacion"; 
            variables[13] = "pala1"; 
            variables[14] = "pala3"; 
            variables[15] = "pala4"; 
            variables[16] = "pala5"; 
            variables[17] = "pala7"; 
            variables[18] = "pala8"; 
            variables[19] = "pala10"; 
            variables[20] = "pala11"; 
            variables[21] = "chancador1"; 
            variables[22] = "chancador2"; 
            variables[23] = "chaxa_camion"; 
            variables[24] = "movitec_camion"; 
            variables[25] = "das_camion"; 
            variables[26] = "cnorte_consumo_agua"; 
            variables[27] = "cmovil_consumo_agua"; 
            variables[28] = "cachimba1_consumo_agua"; 
            variables[29] = "cachimba2_consumo_agua"; 
            variables[30] = "gerencia_consumo_agua"; 
            variables[31] = "mp10"; 
        }
    }
}
