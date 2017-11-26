using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using BaseDeDatos;
using Controladores;

namespace PruebasCS
{
    class PruebasMP10
    {
        public static void validacion()
        {
            if (!File.Exists("validacion.csv"))
            {
                PruebasMP10.guardarDatos();
                Console.WriteLine("Datos de validacion leidos y almacenados.");
            }

            /*Console.WriteLine("Validacion en proceso...");
            ControladorRNA.validacion();
            Console.WriteLine("Validacion completa.");*/
        }

        public static void guardarDatos()
        {
            DateTime inicio = new DateTime(2014, 1, 1, 0, 0, 0);
            DateTime fin = new DateTime(2017, 12, 31, 0, 0, 0);

            Dictionary<string, double[]> datos = Consultas.getDatosAlerta4(inicio, fin, false);

            StreamWriter file = new StreamWriter("validacion.csv");

            foreach (KeyValuePair<string, double[]> dato in datos)
            {
                String linea = String.Join(";", dato.Value);

                //Console.WriteLine(linea);

                file.WriteLine(linea);
            }

            file.Close();
        }
    }
}
