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

namespace UI
{
    /// <summary>
    /// Lógica de interacción para SOM.xaml
    /// </summary>
    public partial class SOM : UserControl
    {
        public string carpeta;

        public SOM()
        {
            carpeta = "_SOM";

            InitializeComponent();
        }

        public void validacion(object sender, RoutedEventArgs e)
        {
            
        }

        private string rutaArchivo(string archivo)
        {
            return carpeta + "/" + archivo;
        }
    }
}
