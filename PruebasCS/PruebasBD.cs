using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BaseDeDatos;
using System.IO;

namespace PruebasCS
{
    public class PruebasBD
    {
        public static void datosValidacion()
        {
            /*DateTime inicio = new DateTime(2017, 1, 1, 0, 0, 0);
            DateTime fin = new DateTime(2017, 1, 1, 5, 0, 0);

            PruebasBD.imprimir(Consultas.getDatosValidacion(inicio, fin), 37);*/

            Dictionary<string, double[]> alerta_4 = Consultas.getDatosAlerta4(new DateTime(2014, 1, 1, 0, 0, 0), new DateTime(2017, 12, 1, 0, 0, 0), false);
            Dictionary<string, double[]> alerta_3 = Consultas.getDatosAlerta3(new DateTime(2014, 1, 1, 0, 0, 0), new DateTime(2017, 12, 1, 0, 0, 0), false);
            Dictionary<string, double[]> alerta_2 = Consultas.getDatosAlerta2(new DateTime(2014, 1, 1, 0, 0, 0), new DateTime(2017, 12, 1, 0, 0, 0), false);
            Dictionary<string, double[]> alerta_1 = Consultas.getDatosAlerta1(new DateTime(2014, 1, 1, 0, 0, 0), new DateTime(2017, 12, 1, 0, 0, 0), false);

            guardarDatos(alerta_4, "alertas_4.csv");
            guardarDatos(alerta_3, "alertas_3.csv");
            guardarDatos(alerta_2, "alertas_2.csv");
            guardarDatos(alerta_1, "alertas_1.csv");
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

        public static void guardarDatos(Dictionary<string, double[]> datos, string archivo)
        {
            // = new DateTime(2010, 1, 1, 0, 0, 0);
            // = new DateTime(2017, 12, 31, 0, 0, 0);

            StreamWriter file = new StreamWriter(archivo);

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
