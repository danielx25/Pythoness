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
            ControladorRNA.validacion();
        }

        public static void guardarDatos()
        {
            DateTime inicio = new DateTime(2017, 1, 1, 0, 0, 0);
            DateTime fin = new DateTime(2017, 1, 1, 5, 0, 0);

            Dictionary<string, double[]> datos = Consultas.getDatosValidacion(inicio, fin);

            StreamWriter file = new System.IO.StreamWriter("validacion.csv");

            foreach (KeyValuePair<string, double[]> dato in datos)
            {
                String linea = String.Join(";", dato.Value);

                Console.WriteLine(linea);

                file.WriteLine(linea);
            }
        }
    }
}
