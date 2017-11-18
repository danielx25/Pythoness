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
using MahApps.Metro.Controls;


namespace UI
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        public IngresoDatos[] dias;

        public MainWindow()
        {
            InitializeComponent();

            dias = new IngresoDatos[5];
        }

        private void seleccionDia(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cmb = sender as ComboBox;

            setDatosIngresos(cmb.SelectedIndex);
        }

        private void setDatosIngresos(int dia)
        {
            panelIngresoDatos.boxVelocidadV.Text = dias[dia].velocidadV + "";
        }
    }
}
