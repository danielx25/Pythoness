using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Controladores;
using ReglasFAM;
using System.Diagnostics;

namespace UI.eventos
{
    public class GeneracionReglas : Progreso
    {
        string dataset;
        string carpeta;
        string carpeta_extraccion;
        string salida_dataset;
        string consola;
        int num_nrns;
        bool desnormalizar;

        public GeneracionReglas(string carpeta, string dataset, string consola, int num_nrns, bool desnormalizar) : base()
        {
            this.carpeta = carpeta;
            this.carpeta_extraccion = carpeta + "\\_extraccion";
            this.dataset = dataset;
            this.salida_dataset = carpeta_extraccion + "\\discretizado.csv";
            this.consola = consola;
            this.num_nrns = num_nrns;
            this.desnormalizar = desnormalizar;
            worker.RunWorkerAsync();
        }

        protected override void doWork(object sender, DoWorkEventArgs e)
        {
            string archv_val_vars = carpeta_extraccion + "\\valores_variables.csv";
            int profundidad = 32;
            var w = sender as BackgroundWorker;
            Reglas reglas;

            w.ReportProgress(0, String.Format("Discretizando dataset..."));

            ControladorFAM.discretizacion(num_nrns, ref dataset, ref salida_dataset, desnormalizar);

            w.ReportProgress(20, String.Format("Discretizando dataset..."));

            reglas = new Reglas(archv_val_vars, profundidad, "sin_alerta");
            reglas.extraccionReglas(salida_dataset, carpeta_extraccion + "\\sa.pynoess");

            w.ReportProgress(40, String.Format("Discretizando dataset..."));

            reglas = new Reglas(archv_val_vars, 10, "alerta_1");
            reglas.extraccionReglas(salida_dataset, carpeta_extraccion + "\\a1.pynoess");

            w.ReportProgress(60, String.Format("Discretizando dataset..."));

            reglas = new Reglas(archv_val_vars, profundidad, "alerta_2");
            reglas.extraccionReglas(salida_dataset, carpeta_extraccion + "\\a2.pynoess");

            w.ReportProgress(80, String.Format("Discretizando dataset..."));

            reglas = new Reglas(archv_val_vars, profundidad, "alerta_3");
            reglas.extraccionReglas(salida_dataset, carpeta_extraccion + "\\a3.pynoess");

            w.ReportProgress(100, String.Format("Discretizando dataset..."));

            reglas = new Reglas(archv_val_vars, profundidad, "alerta_4");
            reglas.extraccionReglas(salida_dataset, carpeta_extraccion + "\\a4.pynoess");

            string carpeta_archivos = "\"" + carpeta + "\"";
            Process process = new Process();
            process.StartInfo.FileName = consola;
            process.StartInfo.Arguments = "-e " + carpeta_archivos + " " + num_nrns;
            //process.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            process.Start();
        }
    }
}
