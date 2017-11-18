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
    /// Lógica de interacción para IngresoDatos.xaml
    /// </summary>
    public partial class IngresoDatos : UserControl
    {
        public DateTime fecha;
        public double velocidadV;
        public double direccionV;
        public double humedad;
        public double radiacion;
        public double precipitacionM;
        public double precipitacionH;
        public double precipitacion1;
        public double precipitacion2;
        public double precipitacion3;
        public double evaporacion;
        public Dictionary<string, bool> chancadores;
        public Dictionary<string, bool> palas;
        public int chaxa;
        public int movitec;
        public int dasdia;
        public double cnorte;
        public double cmovil;
        public double cachimba1;
        public double cachimba2;
        public double gerencia;

        public IngresoDatos()
        {
            InitializeComponent();
        }

        private void setValor(object sender, RoutedEventArgs e)
        {
            TextBox textBox = ((TextBox)sender);

            if (textBox.Name == "boxVelocidadV") velocidadV = Convert.ToDouble(boxVelocidadV.Text);

        }
    }
}
