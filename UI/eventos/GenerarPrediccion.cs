using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Controladores;
using System.Windows.Controls;
using System.Diagnostics;
using System.IO;

namespace UI.eventos
{
    public class GenerarPrediccion : Progreso
    {
        IngresoDatos panelIngresoDatos;
        Prediccion panelPrediccion;
        string RNA;

        public GenerarPrediccion(string RNA, IngresoDatos panelIngresoDatos, Prediccion panelPrediccion)
        {
            this.RNA = RNA;
            this.panelIngresoDatos = panelIngresoDatos;
            this.panelPrediccion = panelPrediccion;
            worker.RunWorkerAsync();
        }

        protected override void doWork(object sender, DoWorkEventArgs e)
        {
            if ( RNA == "FAM")
            {
                FAM(sender, e);
            }
            else if (RNA == "SOM")
            {
                SOM(sender, e);
            }
        }

        protected override void completado(object sender, RunWorkerCompletedEventArgs e)
        {
            panelPrediccion.graficarPredicciones();

            this.Close();
        }

        private Tuple<double, double> getMaximaPrediccion(ControladorFAM cFAM)
        {
            string variable = "hora";
            double maximo = 0;
            double hora_maxima = 0;

            for (double hora = 0; hora < 24; hora++)
            {
                double prediccion = 0;
                cFAM.setValorVariable(ref variable, hora);

                prediccion = cFAM.prediccion();

                if (prediccion > maximo)
                {
                    maximo = prediccion;
                    hora_maxima = hora;
                }
            }

            Tuple<double, double> prediccion_hora = Tuple.Create(maximo, hora_maxima);

            return prediccion_hora;
        }

        private string rutaArchivoFAM(string archivo)
        {
            return "_FAM" + "\\" + archivo;
        }
        private int getParametrosFAM()
        {
            IEnumerable<string> lineas = File.ReadLines(rutaArchivoFAM("configuracionRNA.conf"));
            int num_nrns = 3;

            foreach (string linea in lineas)
            {
                string[] parametros = linea.Split('=');

                if (parametros.Length == 2)
                {
                    parametros[0] = parametros[0].Replace(" ", "");
                    parametros[1] = parametros[1].Replace(" ", "");

                    if (parametros[0] == "NUMERO_NEURONAS") num_nrns = Int32.Parse(parametros[1]);
                }
            }

            return num_nrns;
        }

        private void FAM(object sender, DoWorkEventArgs e)
        {
            int num_nrns = getParametrosFAM();
            ControladorFAM cFAM = new ControladorFAM(num_nrns);

            var w = sender as BackgroundWorker;
            w.ReportProgress(0, String.Format("Realizando prediccion..."));

            foreach (KeyValuePair<string, Dictionary<string, double>> datos_dia in panelIngresoDatos.datos)
            {
                if (panelIngresoDatos.diasPrediccion.Contains(datos_dia.Key))
                {
                    string dia = datos_dia.Key;
                    dia = dia.Replace("dia_", "");
                    int indice_dia = Int32.Parse(dia) - 1;

                    foreach (KeyValuePair<string, double> dato in datos_dia.Value)
                    {
                        string variable = dato.Key;

                        cFAM.setValorVariable(ref variable, dato.Value);
                    }

                    Tuple<double, double> prediccion_hora = getMaximaPrediccion(cFAM);

                    panelPrediccion.predicciones[indice_dia] = prediccion_hora.Item1;
                    panelPrediccion.horas[indice_dia] = prediccion_hora.Item2;

                    //panelPrediccion.predicciones[indice_dia] = cFAM.prediccion();

                    w.ReportProgress(25 * indice_dia, String.Format("Realizando prediccion..."));
                }
            }
        }

        private void SOM(object sender, DoWorkEventArgs e)
        {

        }

    }
}
