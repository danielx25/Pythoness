using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BaseDeDatos;

namespace PruebasCS
{
    public class PruebasBD
    {
        public static void datosValidacion()
        {
            DateTime inicio = new DateTime(2017, 1, 1, 0, 0, 0);
            DateTime fin = new DateTime(2017, 1, 1, 5, 0, 0);

            PruebasBD.imprimir(Consultas.getDatosValidacion(inicio, fin), 37);
        }

        public static void meteorologicos()
        {
            DateTime inicio = new DateTime(2010, 1, 1, 1, 0, 0);
            DateTime fin = new DateTime(2010, 1, 2, 0, 0, 0);

            PruebasBD.imprimir(Consultas.getDatosMeteorologicos(inicio, fin), 19);
        }

        public static void mitigacion()
        {
            DateTime inicio = new DateTime(2014, 12, 1, 0, 0, 0);
            DateTime fin = new DateTime(2014, 12, 30, 0, 0, 0);

            PruebasBD.imprimir(Consultas.getDatosMitigacion(inicio, fin), 10);
        }

        public static void palas()
        {
            Dictionary<string, List<DateTime>> palas = Consultas.getDatosPalas();

            for(int i = 0; i < 20; i++)
                Console.WriteLine(palas["pa04"].ElementAt(i).ToString("yyyy-MM-dd HH:mm:ss"));
            //foreach (DateTime fecha in palas["pa04"])
            //Console.WriteLine(fecha.ToString("yyyy-MM-dd HH:mm:ss"));
        }

        public static void chancadores()
        {
            Dictionary<string, List<DateTime>> palas = Consultas.getDatosChancadores();

            for (int i = 0; i < 20; i++)
                Console.WriteLine(palas["ch01"].ElementAt(i).ToString("yyyy-MM-dd HH:mm:ss"));
            //foreach (DateTime fecha in palas["pa04"])
            //Console.WriteLine(fecha.ToString("yyyy-MM-dd HH:mm:ss"));
        }

        public static void imprimir(Dictionary<string, double[]> datos, int num_column)
        {
            foreach(KeyValuePair<string, double[]> dato in datos)
            {
                Console.WriteLine(dato.Key);

                for (int i=0; i < num_column; i++)
                    Console.Write(dato.Value[i] + " ");

                Console.Write("\n");
            }
        }
    }
}
