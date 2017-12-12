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
using Reportes;
using UI.eventos;
using Microsoft.Win32;

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
            panelPrediccion.AddHandler(Prediccion.eventoGenerarReporte, new RoutedEventHandler(generarReporte));
        }

        private void generarPrediccion(object sender, RoutedEventArgs e)
        {
            if (panelIngresoDatos.diasPrediccion.Count() > 0)
            {
                //string RNA = panelIngresoDatos.boxRNAs.SelectedValue.ToString();
                string RNA = "FAM";

                limpiarGrafico();

                tabPrincipal.SelectedIndex = 1;

                GenerarPrediccion generarPrediccion = new GenerarPrediccion(RNA, panelIngresoDatos, panelPrediccion);
            }

            e.Handled = true;
        }

        private void generarReporte(object sender, RoutedEventArgs e)
        {
            bool prediccion_realizada = false;

            // si al menos una prediccion se realizo, se puede generar el reporte.
            for(int i = 0; i < panelPrediccion.predicciones.Length; i++)
            {
                if (panelPrediccion.predicciones[i] > -1)
                {
                    prediccion_realizada = true;
                }
            }

            if (prediccion_realizada)
            {
                SaveFileDialog saveFileDialog1 = new SaveFileDialog();

                saveFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
                saveFileDialog1.FilterIndex = 2;
                saveFileDialog1.RestoreDirectory = true;

                if (saveFileDialog1.ShowDialog() == true)
                {
                    Reporte.generar(saveFileDialog1.FileName, panelIngresoDatos.diasPrediccion, panelIngresoDatos.datos, panelPrediccion.predicciones);
                }
            }

            e.Handled = true;
        }

        private void limpiarGrafico()
        {
            int elementos_grafico = panelPrediccion.graficoPrediccion.ChartValues.Count;

            if (elementos_grafico > 0)
            {
                panelPrediccion.graficoPrediccion.ChartValues.Clear();

                for (int i = 0; i < panelPrediccion.predicciones.Length; i++)
                {
                    string dia = "dia" + (i + 1);
                    Label nivel = (Label)panelPrediccion.gridPrediccion.FindName("mp10_" + dia);
                    Label alerta = (Label)panelPrediccion.gridPrediccion.FindName("alerta_" + dia);
                    Label hora = (Label)panelPrediccion.gridPrediccion.FindName("hora_" + dia);

                    nivel.Content = "";
                    alerta.Content = "";
                    hora.Content = "";
                    panelPrediccion.predicciones[i] = -1;
                    panelPrediccion.horas[i] = 0;
                }
            }
        }

        private void panelRedNeuronal_Loaded(object sender, RoutedEventArgs e)
        {

        }
    }
}
