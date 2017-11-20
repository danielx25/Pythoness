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

namespace UI
{
    /// <summary>
    /// Lógica de interacción para FAM.xaml
    /// </summary>
    public partial class FAM : UserControl
    {
        public string archv_dataset;
        public string archv_validacion;
        public bool desnormalizar;

        public FAM()
        {
            archv_dataset = "";
            archv_validacion = "";
            desnormalizar = false;
            InitializeComponent();
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
            GeneracionReglas genReglas = new GeneracionReglas(archv_dataset, "dataset_dis.csv", "reglas.txt", desnormalizar);
        }

    }

}
