using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Controladores;

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

        private void FAM(object sender, DoWorkEventArgs e)
        {
            ControladorFAM cFAM = new ControladorFAM();

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

                    panelPrediccion.predicciones[indice_dia] = cFAM.prediccion();

                    w.ReportProgress(25 * indice_dia, String.Format("Realizando prediccion..."));
                }
            }
        }

        private void SOM(object sender, DoWorkEventArgs e)
        {

        }

    }
}
