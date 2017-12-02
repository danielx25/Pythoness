using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BaseDeDatos;
using System.IO;

namespace UI.eventos
{
    public class Consulta : Progreso
    {
        DateTime inicial;
        DateTime final;
        string archv_salida;

        public Consulta(DateTime inicial, DateTime final, string archv_salida) : base()
        {
            this.inicial = inicial;
            this.final = final;
            this.archv_salida = archv_salida;
            worker.RunWorkerAsync();
        }

        protected override void doWork(object sender, DoWorkEventArgs e)
        {
            var w = sender as BackgroundWorker;

            w.ReportProgress(0, String.Format("Cargando datos desde la base de datos..."));

            Dictionary<string, double[]> datos = Consultas.getDatosValidacion(inicial, final);

            w.ReportProgress(50, String.Format("Almacenando datos..."));

            guardarDatos(archv_salida, datos);

            w.ReportProgress(100, String.Format("Datos cargados..."));
        }

        private void guardarDatos(string archivo, Dictionary<string, double[]> datos)
        {
            StreamWriter file = new StreamWriter(archivo);

            foreach (KeyValuePair<string, double[]> dato in datos)
            {
                String linea = String.Join(";", dato.Value);

                file.WriteLine(linea);
            }

            file.Close();
        }
    }
}
