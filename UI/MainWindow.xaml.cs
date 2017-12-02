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
using UI.eventos;

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
                string RNA = panelIngresoDatos.boxRNAs.SelectedValue.ToString();

                tabPrincipal.SelectedIndex = 1;

                GenerarPrediccion generarPrediccion = new GenerarPrediccion(RNA, panelIngresoDatos, panelPrediccion);
            }

            e.Handled = true;
        }
    }
}
