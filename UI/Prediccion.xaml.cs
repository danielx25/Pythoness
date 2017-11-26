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

        public Prediccion()
        {
            InitializeComponent();

            dias = 5;
            predicciones = new double[dias];

            for (int i = 0; i < dias; i++)
                predicciones[i] = -1;

            graficoPrediccion.SetAxisXLimits(1, predicciones.Length);
            graficoPrediccion.SetAxisYLimits(0, 800);
            graficoPrediccion.LabelAxisX = "Dias";
            graficoPrediccion.LabelAxisY = "MP10";
        }

        public void graficarPredicciones()
        {
            for (int i = 0; i < predicciones.Length; i++)
            {
                if (predicciones[i] > -1)
                {
                    graficoPrediccion.ChartValues.Add(new Coordenadas
                    {
                        X = i + 1,
                        Y = predicciones[i]
                    });
                }
            }
        }
    }
}
