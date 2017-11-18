using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PruebasCS
{
    class Program
    {
        static void Main(string[] args)
        {
            PruebasReglas pReglas = new PruebasReglas(); pReglas.extraccionReglas("dataset.csv", "reglasC45.txt");
            //PruebasMP10.validacion();
            //PruebasBD.datosValidacion();
            //PruebasBD.meteorologicos();
            //PruebasBD.mitigacion();
            //PruebasBD.palas();
            //PruebasBD.chancadores();

            Console.WriteLine("Prueba terminada, presione una tecla para continuar.");
            Console.ReadLine();
        }
    }
}
