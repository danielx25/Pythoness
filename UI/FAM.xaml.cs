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

namespace UI
{
    /// <summary>
    /// Lógica de interacción para FAM.xaml
    /// </summary>
    public partial class FAM : UserControl
    {
        public string carpeta;
        public string archv_dataset;
        public string archv_validacion;
        public bool desnormalizar;

        public FAM()
        {
            carpeta = "_FAM";

            if (!Directory.Exists(carpeta)) Directory.CreateDirectory(carpeta);

            archv_dataset = "";
            archv_validacion = "";
            desnormalizar = false;
            InitializeComponent();

            // agregamos la hora a los combobox.
            List<string> horas = new List<string>();

            for(int i = 0; i <= 24; i++)
            {
                string hora = "";

                hora += i;
                horas.Add(hora);
            }

            horaInicial.ItemsSource = horas;
            horaFinal.ItemsSource = horas;
        }

        public void seleccionarArchivo(object sender, RoutedEventArgs e)
        {
            TextBox box = (TextBox)sender;
            string archivo = box.Text;

            archivo = Dialogo.seleccionArchivo(archivo);

            if (box.Name == boxDataset.Name) archv_dataset = archivo;
            else if (box.Name == boxDatosVal.Name) archv_validacion = archivo;

            box.Text = archivo;
        }

        public void setDesnormalizacion(object sender, RoutedEventArgs e)
        {
            desnormalizar = true;
        }

        public void unSetDesnormalizacion(object sender, RoutedEventArgs e)
        {
            desnormalizar = false;
        }

        public void generarReglas(object sender, RoutedEventArgs e)
        {
            GeneracionReglas genReglas = new GeneracionReglas(archv_dataset, rutaArchivo("dataset_dis.csv"), rutaArchivo("reglas.txt"), desnormalizar);
        }

        public void validacionBD(object sender, RoutedEventArgs e)
        {
            DateTime inicial = (DateTime)fechaInicial.SelectedDate;
            DateTime final = (DateTime)fechaFinal.SelectedDate;
            string hora_inicial = (string)horaInicial.SelectedValue;
            string hora_final = (string)horaFinal.SelectedValue;
            DateTime fecha_inicial = new DateTime(inicial.Year, inicial.Month, inicial.Day, Convert.ToInt32(hora_inicial), 0, 0);
            DateTime fecha_final = new DateTime(final.Year, final.Month, final.Day, Convert.ToInt32(hora_final), 0, 0);

            Consulta consulta = new Consulta(fecha_inicial, fecha_final, rutaArchivo("validacion.csv"));

            //graficoValidacion.validacion();
        }

        public void validacionArchivo(object sender, RoutedEventArgs e)
        {
            //graficoValidacion.validacion();
        }

        private string rutaArchivo(string archivo)
        {
            return carpeta + "/" + archivo;
        }
    }

}
