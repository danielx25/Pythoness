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
using Controladores;

namespace UI
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {

        public MainWindow()
        {
            InitializeComponent();
            panelIngresoDatos.AddHandler(IngresoDatos.eventoGenerarPrediccion, new RoutedEventHandler(generarPrediccion));
        }

        private void generarPrediccion(object sender, RoutedEventArgs e)
        {
            if (panelIngresoDatos.diasPrediccion.Count() > 0)
            {
                tabPrincipal.SelectedIndex = 1;

                ControladorFAM cFAM = new ControladorFAM();

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
                    }
                }

                panelPrediccion.graficarPredicciones();
            }

            e.Handled = true;
        }
    }
}
