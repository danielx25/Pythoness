using System;
using System.Collections.Generic;
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
using Controladores;
using ReglasFAM;
using System.IO;
using UI.eventos;
using UI.graficos;
using LiveCharts.Wpf;
using LiveCharts;
using System.Threading;
using System.Diagnostics;
using System.Windows.Controls.Primitives;
using System.Reflection;

namespace UI
{
    /// <summary>
    /// Lógica de interacción para FAM.xaml
    /// </summary>
    public partial class FAM : UserControl
    {
        public string carpeta;
        public string archv_dataset;
        public string archv_discretizado;
        public string archv_reglas;
        public string archv_validacion;
        public bool desnormalizar;
        string directorio;

        public FAM()
        {
            directorio = System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            carpeta = "_FAM";

            if (!Directory.Exists(carpeta)) Directory.CreateDirectory(carpeta);

            archv_dataset = directorio + "\\pesosRNA.csv";
            archv_reglas = directorio + "\\" + carpeta + "\\" + "reglas.pynoess";
            archv_validacion = "";
            desnormalizar = true;

            InitializeComponent();

            int num_nrns = getParametrosRNA();

            lblNumNrns.Content = num_nrns;
            slNumNrns.Value = num_nrns;
        }

        public void generarReglas(object sender, RoutedEventArgs e)
        {
            btnGenerarReglas.IsEnabled = false;
            btnValidacion.IsEnabled = false;
            int num_nrns = Int32.Parse(lblNumNrns.Content.ToString());
            string carpeta_archivos = directorio + "\\" + carpeta;
            string consola = directorio + "\\" + rutaArchivo("ConsolaFAM.exe");

            GeneracionReglas genReglas = new GeneracionReglas(carpeta_archivos, archv_dataset, consola, num_nrns, true);

            btnGenerarReglas.IsEnabled = true;
            btnValidacion.IsEnabled = true;
        }

        public void setNumNeuronas(object sender, DragCompletedEventArgs e)
        {
            lblNumNrns.Content = slNumNrns.Value.ToString();

            guardarParametrosRNA(Int32.Parse(lblNumNrns.Content.ToString()));
        }

        public void validacion(object sender, RoutedEventArgs e)
        {
            btnGenerarReglas.IsEnabled = false;
            btnValidacion.IsEnabled = false;
            directorio = System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            int num_nrns = Int32.Parse(lblNumNrns.Content.ToString());
            string carpeta_archivos = "\"" + directorio + "\\" + carpeta + "\"";

            Process process = new Process();
            process.StartInfo.FileName = directorio + "\\" + rutaArchivo("ConsolaFAM.exe");
            process.StartInfo.Arguments = "-v " + carpeta_archivos + " " + num_nrns;
            //process.StartInfo.WindowStyle = ProcessWindowStyle.Maximized;
            process.Start();
            btnGenerarReglas.IsEnabled = true;
            btnValidacion.IsEnabled = true;
        }

        private string rutaArchivo(string archivo)
        {
            return carpeta + "\\" + archivo;
        }

        private void guardarParametrosRNA(int num_nrns)
        {
            StreamWriter archivo = new StreamWriter(rutaArchivo("configuracionRNA.conf"));

            archivo.WriteLine("NUMERO_NEURONAS = " + num_nrns);

            archivo.Close();
        }

        private int getParametrosRNA()
        {
            IEnumerable<string> lineas = File.ReadLines(directorio + "\\" + rutaArchivo("configuracionRNA.conf"));
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
    }

}
