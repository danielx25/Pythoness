using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Controladores;
using ReglasFAM;

namespace UI
{
    public class GeneracionReglas : Progreso
    {
        string dataset;
        string salida_dataset;
        string salida_reglas;
        bool desnormalizar;

        public GeneracionReglas(string dataset, string salida_dataset, string salida_reglas, bool desnormalizar) : base()
        {
            this.dataset = dataset;
            this.salida_dataset = salida_dataset;
            this.salida_reglas = salida_reglas;
            this.desnormalizar = desnormalizar;
            worker.RunWorkerAsync();
        }

        protected override void doWork(object sender, DoWorkEventArgs e)
        {
            var w = sender as BackgroundWorker;
            w.ReportProgress(0, String.Format("Discretizando dataset..."));

            ControladorFAM.discretizacion(ref dataset, ref salida_dataset, desnormalizar);

            w.ReportProgress(50, String.Format("Generando reglas..."));

            Reglas reglas = new Reglas();
            reglas.extraccionReglas(salida_dataset, salida_reglas);

            w.ReportProgress(100, String.Format("Reglas generadas..."));
        }
    }
}
