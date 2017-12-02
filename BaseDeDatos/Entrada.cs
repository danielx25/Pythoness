using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BaseDeDatos
{
    public class Entrada
    {
        private Tuple<double, double>[] limites;

        public Entrada()
        {
            setLimitesEntradas();
        }

        /// <summary>
        /// Normaliza el valor segun el indice de la variable de entrada
        /// </summary>
        /// <param name="valor">Valor a normalizar</param>
        /// <param name="indice">Indice de la variable de entrada (velocidad viento, direccion viento, etc).</param>
        /// <returns></returns>
        public double normalizar(double valor, int indice)
        {
            Tuple<double, double> limites = getLimiteEntrada(indice);

            return Entrada.normalizar(valor, limites.Item1, limites.Item2);
        }


        public static double normalizar(double valor, double minimo, double maximo)
        {
            //(X_i - X.min) / (X.max - X.min)
            double valorNormalizado = (valor - minimo) / (maximo - minimo);

            return valorNormalizado;
        }

        /// <summary>
        /// Normaliza el valor segun el indice de la variable de entrada
        /// </summary>
        /// <param name="valor">Valor a desnormalizar</param>
        /// <param name="indice">Indice de la variable de entrada (velocidad viento, direccion viento, etc).</param>
        /// <returns></returns>
        public double desnormalizar(double valor, int indice)
        {
            Tuple<double, double> limites = getLimiteEntrada(indice);

            return Entrada.desnormalizar(valor, limites.Item1, limites.Item2);
        }

        public static double desnormalizar(double normalizado, double minimo, double maximo)
        {
            double valor = (normalizado * (maximo - minimo)) + minimo;

            return valor;
        }


        public Tuple<double, double> getLimiteEntrada(int indice)
        {
            return limites[indice];
        }

        public void setLimitesEntradas()
        {
            int num_entradas = 38;
            limites = new Tuple<double, double>[num_entradas];

            limites[0] = new Tuple<double, double>(0.0, 12.0);
            limites[1] = new Tuple<double, double>(0.0, 24.0);
            limites[2] = new Tuple<double, double>(0.0, 30.0);
            limites[3] = new Tuple<double, double>(0.0, 360.0);
            limites[4] = new Tuple<double, double>(-10.0, 55.0);
            limites[5] = new Tuple<double, double>(0.0, 100.0);
            limites[6] = new Tuple<double, double>(0.0, 1600.0);
            limites[7] = new Tuple<double, double>(0.0, 1700.0);

            limites[8] = new Tuple<double, double>(0.0, 0.0);

            limites[9] = new Tuple<double, double>(0.0, 2860.0);
            limites[10] = new Tuple<double, double>(0.0, 2860.0);
            limites[11] = new Tuple<double, double>(0.0, 2860.0);
            limites[12] = new Tuple<double, double>(0.0, 2860.0);
            limites[13] = new Tuple<double, double>(0.0, 2860.0);
            limites[14] = new Tuple<double, double>(-1.0, 255.0);

            limites[15] = new Tuple<double, double>(0.0, 0.0);
            limites[16] = new Tuple<double, double>(0.0, 0.0);
            limites[17] = new Tuple<double, double>(0.0, 0.0);
            limites[18] = new Tuple<double, double>(0.0, 0.0);
            limites[19] = new Tuple<double, double>(0.0, 0.0);

            limites[20] = new Tuple<double, double>(0.0, 1.0);
            limites[21] = new Tuple<double, double>(0.0, 1.0);
            limites[22] = new Tuple<double, double>(0.0, 1.0);
            limites[23] = new Tuple<double, double>(0.0, 1.0);
            limites[24] = new Tuple<double, double>(0.0, 1.0);
            limites[25] = new Tuple<double, double>(0.0, 1.0);
            limites[26] = new Tuple<double, double>(0.0, 1.0);
            limites[27] = new Tuple<double, double>(0.0, 1.0);
            limites[28] = new Tuple<double, double>(0.0, 1.0);
            limites[29] = new Tuple<double, double>(0.0, 1.0);
            limites[30] = new Tuple<double, double>(-1.0, 7.0);
            limites[31] = new Tuple<double, double>(-1.0, 8.0);
            limites[32] = new Tuple<double, double>(-1.0, 4.0);
            limites[33] = new Tuple<double, double>(0.0, 90240.0);
            limites[34] = new Tuple<double, double>(0.0, 4480.0);
            limites[35] = new Tuple<double, double>(0.0, 1500.0);
            limites[36] = new Tuple<double, double>(0.0, 2270.0);
            limites[37] = new Tuple<double, double>(0.0, 27000.0);
        }
    }
}
