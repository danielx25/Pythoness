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
using System.Threading;
using UI.graficos;

namespace UI
{
    /// <summary>
    /// Lógica de interacción para Prediccion.xaml
    /// </summary>
    public partial class Prediccion : UserControl
    {
        private int dias;
        public double[] predicciones;
        public double[] horas;
        public static RoutedEvent eventoGenerarReporte;
        public string ruta_reporte;

        public Prediccion()
        {
            InitializeComponent();

            dias = 5;
            predicciones = new double[dias];
            horas = new double[dias];

            for (int i = 0; i < dias; i++)
            {
                predicciones[i] = -1;
                horas[i] = 0;
            }

            graficoPrediccion.SetAxisXLimits(1, predicciones.Length);
            graficoPrediccion.SetAxisYLimits(0, 800);
            graficoPrediccion.LabelAxisX = "Dias";
            graficoPrediccion.LabelAxisY = "MP10";

            eventoGenerarReporte = EventManager.RegisterRoutedEvent("generarReporte", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(Prediccion));
        }

        public void graficarPredicciones()
        {
            for (int i = 0; i < predicciones.Length; i++)
            {
                string dia = "dia" + (i + 1);
                Label nivel = (Label)gridPrediccion.FindName("mp10_" + dia);
                Label alerta = (Label)gridPrediccion.FindName("alerta_" + dia);
                Label hora = (Label)gridPrediccion.FindName("hora_" + dia);

                if (predicciones[i] > -1)
                {
                    graficoPrediccion.ChartValues.Add(new Coordenadas
                    {
                        X = i + 1,
                        Y = predicciones[i]
                    });

                    nivel.Content = Math.Round(predicciones[i]) + "";
                    alerta.Content = getAlerta(predicciones[i]);
                    hora.Content = horas[i] + "";
                }
                else
                {
                    nivel.Content = "";
                    alerta.Content = "";
                    hora.Content = "";
                }
            }
        }

        private string getAlerta(double mp10)
        {
            string alerta = "";

            if(mp10 <= 150)
            {
                alerta = "Sin alerta";
            }
            else if (mp10 <= 250)
            {
                alerta = "Alerta 1";
            }
            else if(mp10 <= 350)
            {
                alerta = "Alerta 2";
            }
            else if (mp10 <= 500)
            {
                alerta = "Alerta 3";
            }
            else
            {
                alerta = "Alerta 4";
            }

            return alerta;
        }

        private void clickGenerarReporte(object sender, RoutedEventArgs e)
        {
            RoutedEventArgs e1 = new RoutedEventArgs(eventoGenerarReporte);

            RaiseEvent(e1);
        }
    }
}
