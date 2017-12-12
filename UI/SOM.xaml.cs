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

namespace UI
{
    /// <summary>
    /// Lógica de interacción para SOM.xaml
    /// </summary>
    public partial class SOM : UserControl
    {
        public string carpeta;
        public static RoutedEvent eventoCambiarTab;

        public SOM()
        {
            carpeta = "_SOM";

            InitializeComponent();
            cargarValoresConfig();

            eventoCambiarTab = EventManager.RegisterRoutedEvent("cambiarTab", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(SOM));
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
    }
}
