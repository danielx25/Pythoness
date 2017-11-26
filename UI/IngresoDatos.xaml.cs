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
        private int dias;
        public DateTime[] fechas;
        public Dictionary<string, Dictionary<string, double>> datos;
        public List<string> diasPrediccion;
        public static RoutedEvent eventoGenerarPrediccion;

        public IngresoDatos()
        {
            InitializeComponent();

            dias = 5;
            datos = new Dictionary<string, Dictionary<string, double>>();

            eventoGenerarPrediccion = EventManager.RegisterRoutedEvent("generarPrediccion", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(IngresoDatos));

            /*for (int i = 1; i <= dias; i++)
            {
                meteorologicos["dia_" + i]["velocidad_viento"] = 0;
                meteorologicos["dia_" + i]["direccion_viento"] = 0;
                meteorologicos["dia_" + i]["humedad"] = 0;
                meteorologicos["dia_" + i]["radiacion_solar"] = 0;
                meteorologicos["dia_" + i]["precipitacion_1"] = 0;
                meteorologicos["dia_" + i]["precipitacion_2"] = 0;
                meteorologicos["dia_" + i]["precipitacion_3"] = 0;
                meteorologicos["dia_" + i]["precipitacion_4"] = 0;
                meteorologicos["dia_" + i]["precipitacion_5"] = 0;
                meteorologicos["dia_" + i]["evaporacion"] = 0;
            }*/
        }

        private void setValor(object sender, RoutedEventArgs e)
        {
            string dia_actual = "dia_" + (string)boxDias.SelectedValue;
            TextBox box = ((TextBox)sender);

            datos[dia_actual][(string)box.Tag] = Convert.ToDouble(box.Text);

        }

        private void setCheck(object sender, RoutedEventArgs e)
        {
            string dia_actual = "dia_" + (string)boxDias.SelectedValue;
            CheckBox box = ((CheckBox)sender);

            datos[dia_actual][(string)box.Tag] = 1.0;
        }

        private void setUncheck(object sender, RoutedEventArgs e)
        {
            string dia_actual = "dia_" + (string)boxDias.SelectedValue;
            CheckBox box = ((CheckBox)sender);

            datos[dia_actual][(string)box.Tag] = 0.0;
        }

        private void checkDiaSeleccion(object sender, RoutedEventArgs e)
        {
            CheckBox box = ((CheckBox)sender);
            string dia = (string)box.Tag;

            if (!diasPrediccion.Contains(dia)) diasPrediccion.Add(dia);
        }

        private void unCheckDiaSeleccion(object sender, RoutedEventArgs e)
        {
            CheckBox box = ((CheckBox)sender);
            string dia = (string)box.Tag;

            if (diasPrediccion.Contains(dia)) diasPrediccion.Remove(dia);
        }

        private void clickGenerarPrediccion(object sender, RoutedEventArgs e)
        {
            RoutedEventArgs e1 = new RoutedEventArgs(eventoGenerarPrediccion);

            RaiseEvent(e1);
        }

        public event RoutedEventHandler generarPrediccion
        {
            add { base.AddHandler(eventoGenerarPrediccion, value); }
            remove { base.RemoveHandler(eventoGenerarPrediccion, value); }
        }
    }
}
