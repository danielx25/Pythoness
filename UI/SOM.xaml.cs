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
using Controladores;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace UI
{
    /// <summary>
    /// Lógica de interacción para SOM.xaml
    /// </summary>
    public partial class SOM : UserControl
    {
        public string carpeta;
        public static RoutedEvent eventoCambiarTab;

        private int valorAncho, valorLargo;

        public SOM()
        {
            carpeta = "_SOM";

            InitializeComponent();
            cargarValoresConfig();

            eventoCambiarTab = EventManager.RegisterRoutedEvent("cambiarTab", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(SOM));
        }

        public void cambioNumeroCiclos(object sender, RoutedEventArgs e)
        {
            try
            {
                double alfa = Convert.ToDouble(t_alfa.Text);
                double beta = Convert.ToDouble(t_beta.Text);

                double numeroCiclos = alfa/beta;
                t_numeroCiclos.Text = Convert.ToString(numeroCiclos);
                System.Console.WriteLine("numero de ciclos");
            }
            catch (OverflowException)
            {
                //Console.WriteLine("{0} is outside the range of the Int32 type.", value);
            }
            catch (FormatException)
            {
                //Console.WriteLine("The {0} value '{1}' is not in a recognizable format.",
                //                  value.GetType().Name, value);
            }
            catch(NullReferenceException)
            {

            }
        }

        public void cambioValorAncho(object sender, RoutedEventArgs e)
        {
            try
            {
                valorAncho = Convert.ToInt16(t_ancho.Text);
                t_numeroNeuronas.Text = Convert.ToString(valorAncho * valorLargo);
                System.Console.WriteLine("cambio de valor1");
            }
            catch (OverflowException)
            {
                //Console.WriteLine("{0} is outside the range of the Int32 type.", value);
            }
            catch (FormatException)
            {
                //Console.WriteLine("The {0} value '{1}' is not in a recognizable format.",
                //                  value.GetType().Name, value);
            }
            
        }

        public void cambioValorLargo(object sender, RoutedEventArgs e)
        {
            try
            {
                valorLargo = Convert.ToInt16(t_largo.Text);
                t_numeroNeuronas.Text = Convert.ToString(valorAncho * valorLargo);
                System.Console.WriteLine("cambio de valor1");
            }
            catch (OverflowException)
            {
                //Console.WriteLine("{0} is outside the range of the Int32 type.", value);
            }
            catch (FormatException)
            {
                //Console.WriteLine("The {0} value '{1}' is not in a recognizable format.",
                //                  value.GetType().Name, value);

            }
        }

        public void validacion(object sender, RoutedEventArgs e)
        {
            Process process = Process.Start(@"SOM.exe");
            int id = process.Id;
            Process tempProc = Process.GetProcessById(id);
            this.btnValidacion.IsEnabled = false;
            tempProc.WaitForExit();
            this.btnValidacion.IsEnabled = true;

            RoutedEventArgs e1 = new RoutedEventArgs(eventoCambiarTab);

            RaiseEvent(e1);
        }

        public void guardarEstado(object sender, RoutedEventArgs e)
        {
            String direc = t_rutaEntrenamiento.Text;
            int numeroNeuronas = Convert.ToInt16(t_numeroNeuronas.Text);
            int numeroEntradas = Convert.ToInt16(t_numeroEntrada.Text);
            int largo = Convert.ToInt16(t_ancho.Text);
            int ancho = Convert.ToInt16(t_largo.Text);
            double alfa  = Convert.ToDouble(t_alfa.Text);
            double beta = Convert.ToDouble(t_beta.Text);
            int rangoVecindad = Convert.ToInt16(t_randoVecindad.Text);
            //ControladorSOM.iniciarSOM();
            ControladorSOM.cambiarValoresConfiguracion(direc, numeroEntradas, numeroNeuronas, largo, ancho, alfa, beta, rangoVecindad);
            System.Console.WriteLine("funciona!!!");
            System.Console.WriteLine(direc);
        }

        public void cargarValoresConfig()
        {
            Controladores.config valoresConfig;// = 
            ControladorSOM.obtenerValoresConfiguracion();
            t_rutaEntrenamiento.Text = Convert.ToString((String)ControladorSOM.getDireccion());
            t_numeroEntrada.Text = Convert.ToString(ControladorSOM.getNumeroEntradas());
            t_numeroNeuronas.Text = Convert.ToString(ControladorSOM.getNumetoNeuronas());
            t_ancho.Text = Convert.ToString(ControladorSOM.getAncho());
            t_largo.Text = Convert.ToString(ControladorSOM.getLargo());
            t_alfa.Text = Convert.ToString(ControladorSOM.getAlfa());
            t_beta.Text = Convert.ToString(ControladorSOM.getBeta());
            t_randoVecindad.Text = Convert.ToString(ControladorSOM.getRangoVecindad());
            valorAncho = ControladorSOM.getAncho();
            valorLargo = ControladorSOM.getLargo();
        }

        public event RoutedEventHandler cambiarTab
        {
            add { base.AddHandler(eventoCambiarTab, value); }
            remove { base.RemoveHandler(eventoCambiarTab, value); }
        }

        private string rutaArchivo(string archivo)
        {
            return carpeta + "/" + archivo;
        }

        private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }
    }
}
