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
using System.Diagnostics;
using BaseDeDatos;
using System.Globalization;

namespace UI
{
    /// <summary>
    /// Lógica de interacción para IngresoDatos.xaml
    /// </summary>
    public partial class IngresoDatos : UserControl
    {
        private int dias;
        public Dictionary<string, DateTime> fechas;
        public Dictionary<string, Dictionary<string, double>> datos;
        public List<string> diasPrediccion;
        public static RoutedEvent eventoGenerarPrediccion;
        private bool deshabilitarEventos = false;

        public IngresoDatos()
        {
            InitializeComponent();

            dias = 5;
            fechas = new Dictionary<string, DateTime>();
            datos = new Dictionary<string, Dictionary<string, double>>();
            diasPrediccion = new List<string>();

            DateTime hoy = DateTime.Now;
            DateTime anio_anterior = hoy.AddYears(-1);

            for (int i = 1; i <= dias; i++)
            {
                DateTime dia_siguiente = anio_anterior.AddDays(i);

                string dia_actual = "dia_" + i;
                datos.Add(dia_actual, new Dictionary<string, double>());

                DateTime fecha = new DateTime(dia_siguiente.Year, dia_siguiente.Month, dia_siguiente.Day, dia_siguiente.Hour, 0, 0);
                DateTime fecha_minuto = new DateTime(dia_siguiente.Year, dia_siguiente.Month, dia_siguiente.Day, dia_siguiente.Hour, 1, 0); // fix para la hora con un minuto.

                Dictionary<string, double[]> datos_dia = Consultas.getDatosValidacion(fecha, fecha_minuto);

                // solo se obtiene una fecha, por lo que las entradas se setearan una vez.
                foreach (KeyValuePair<string, double[]> d in datos_dia)
                    setEntradas(dia_actual, fecha.AddYears(1), d.Value);
            }

            boxDias.SelectedIndex = 4;
            //boxRNAs.SelectedIndex = 2;

            chBoxDia1.IsChecked = true;
            chBoxDia2.IsChecked = true;
            chBoxDia3.IsChecked = true;
            chBoxDia4.IsChecked = true;
            chBoxDia5.IsChecked = true;

            eventoGenerarPrediccion = EventManager.RegisterRoutedEvent("generarPrediccion", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(IngresoDatos));
        }

        private void setDatosDia(object sender, SelectionChangedEventArgs e)
        {
            ComboBox box = ((ComboBox)sender);
            string dia = "dia_" + box.SelectedValue.ToString();

            deshabilitarEventos = true;

            setEntradas(dia);

            deshabilitarEventos = false;
        }

        private void setFecha(object sender, SelectionChangedEventArgs e)
        {
            if (boxDias.SelectedValue != null)
            {
                DatePicker box = (DatePicker)sender;
                string dia_actual = "dia_" + boxDias.SelectedValue.ToString();
            
                DateTime fecha = (DateTime)box.SelectedDate;
                datos[dia_actual]["estacion"] = fecha.Month;
            }
        }

        private void setValor(object sender, RoutedEventArgs e)
        {
            NumberStyles estilo = NumberStyles.Number | NumberStyles.AllowCurrencySymbol;
            CultureInfo culture = CultureInfo.CreateSpecificCulture("es-ES");
            string dia_actual = "dia_" + boxDias.SelectedValue.ToString();
            TextBox box = ((TextBox)sender);
            double valor = 0;

            if (! Double.TryParse(box.Text, estilo, culture, out valor))
                box.Text = valor + "";

            //datos[dia_actual][(string)box.Tag] = Convert.ToDouble(box.Text);

            datos[dia_actual][(string)box.Tag] = valor;
        }

        private void setCheck(object sender, RoutedEventArgs e)
        {
            if (boxDias.SelectedValue != null && !deshabilitarEventos)
            {
                string dia_actual = "dia_" + boxDias.SelectedValue.ToString();
                CheckBox box = ((CheckBox)sender);

                if (datos.ContainsKey(dia_actual)) datos[dia_actual][(string)box.Tag] = 1.0;
            }
            
        }

        private void setUncheck(object sender, RoutedEventArgs e)
        {
            if (boxDias.SelectedValue != null && !deshabilitarEventos)
            {
                string dia_actual = "dia_" + boxDias.SelectedValue.ToString();
                CheckBox box = ((CheckBox)sender);

                if (datos.ContainsKey(dia_actual)) datos[dia_actual][(string)box.Tag] = 0.0;
            }
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

        private void setEntradas(string dia, DateTime fecha, double[] datos)
        {
            fechas.Add(dia, fecha);

            boxFecha.SelectedDate = fecha;

            this.datos[dia].Add("estacion", datos[0]);
            this.datos[dia].Add("hora", datos[1]);
            setEntrada(dia, "velocidad_viento", datos[2]);
            setEntrada(dia, "direccion_viento", datos[3]);
            setEntrada(dia, "temperatura", datos[4]);
            setEntrada(dia, "humedad_relativa", datos[5]);
            setEntrada(dia, "radiacion_solar", datos[6]);
            setEntrada(dia, "precipitacion_dia1", datos[7]);
            setEntrada(dia, "precipitacion_dia2", datos[8]);
            setEntrada(dia, "precipitacion_dia3", datos[9]);
            setEntrada(dia, "precipitacion_dia4", datos[10]);
            setEntrada(dia, "precipitacion_dia5", datos[11]);
            setEntrada(dia, "evaporacion", datos[12]);
            setEntrada(dia, "pala1", datos[13]);
            setEntrada(dia, "pala3", datos[14]);
            setEntrada(dia, "pala4", datos[15]);
            setEntrada(dia, "pala5", datos[16]);
            setEntrada(dia, "pala7", datos[17]);
            setEntrada(dia, "pala8", datos[18]);
            setEntrada(dia, "pala10", datos[19]);
            setEntrada(dia, "pala11", datos[20]);
            setEntrada(dia, "chancador1", datos[21]);
            setEntrada(dia, "chancador2", datos[22]);
            setEntrada(dia, "chaxa_camion", datos[23]);
            setEntrada(dia, "movitec_camion", datos[24]);
            setEntrada(dia, "das_camion", datos[25]);
            setEntrada(dia, "cnorte_consumo_agua", datos[26]);
            setEntrada(dia, "cmovil_consumo_agua", datos[27]);
            setEntrada(dia, "cachimba1_consumo_agua", datos[28]);
            setEntrada(dia, "cachimba2_consumo_agua", datos[29]);
            setEntrada(dia, "gerencia_consumo_agua", datos[30]);
        }

        private void setEntradas(string dia)
        {
            boxFecha.SelectedDate = fechas[dia];

            foreach (KeyValuePair<string, double> dato in datos[dia])
            {
                setEntrada(dato.Key, dato.Value);
            }
        }

        private void setEntrada(string dia, string entrada, double valor)
        {
            setValorTextBox(entrada, valor);
            setValorCheckBox(entrada, valor);

            if (datos[dia].ContainsKey(entrada)) datos[dia][entrada] = valor;
            else datos[dia].Add(entrada, valor);
        }

        private void setEntrada(string entrada, double valor)
        {
            setValorTextBox(entrada, valor);
            setValorCheckBox(entrada, valor);
        }

        private void setValorTextBox(string entrada, double valor)
        {
            List<Grid> grids = new List<Grid> { gridMeteorologicos, gridMitigacion };
            TextBox box = null;

            foreach (Grid grid in grids)
            {
                if (box == null)
                {
                    box = grid.Children.OfType<TextBox>().Where(x => x.Tag.ToString() == entrada).FirstOrDefault();
                }
            }

            if (box != null)
            {
                box.Text = valor + "";
            }
        }

        private void setValorCheckBox(string entrada, double valor)
        {
            List<Grid> grids = new List<Grid> { gridPalas, gridChancadores };
            CheckBox box = null;

            foreach (Grid grid in grids)
            {
                if (box == null)
                {
                    box = grid.Children.OfType<CheckBox>().Where(x => x.Tag.ToString() == entrada).FirstOrDefault();
                }
            }

            if (box != null)
            {
                if (Convert.ToDouble(valor) == 1.0)
                    box.IsChecked = true;
                else
                    box.IsChecked = false;
            }
        }
    }
}
