using Npgsql;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace BaseDeDatos
{
    public class Consultas
    {
        public static Dictionary<string, double[]> getDatosValidacion(DateTime inicio, DateTime fin)
        {
            Dictionary<string, double[]> metereologicos = Consultas.getDatosMeteorologicos(inicio, fin);

            return getDatos(metereologicos, inicio, fin, false);
        }

        public static Dictionary<string, double[]> getDatosEntrenamiento(DateTime inicio, DateTime fin)
        {
            Dictionary<string, double[]> metereologicos = Consultas.getDatosMeteorologicos(inicio, fin);

            return getDatos(metereologicos, inicio, fin, true);
        }

        public static Dictionary<string, double[]> getDatosAlerta4(DateTime inicio, DateTime fin, bool normalizar)
        {
            Dictionary<string, double[]> metereologicos = Consultas.getDatosMeteorologicos(inicio, fin, 500);

            return getDatos(metereologicos, inicio, fin, normalizar);
        }

        public static Dictionary<string, double[]> getDatosAlertas(DateTime inicio, DateTime fin, double limite_inferior, bool normalizar)
        {
            Dictionary<string, double[]> metereologicos = Consultas.getDatosMeteorologicos(inicio, fin, limite_inferior);

            return getDatos(metereologicos, inicio, fin, normalizar);
        }

        public static Dictionary<string, double[]> getDatosFecha(DateTime fecha, bool normalizar)
        {
            Dictionary<string, double[]> metereologicos = Consultas.getDatosMeteorologicosFecha(fecha);

            return getDatos(metereologicos, fecha, fecha, normalizar);
        }

        public static Dictionary<string, double[]> getDatos(Dictionary<string, double[]> metereologicos, DateTime inicio, DateTime fin, bool normalizar)
        {
            Dictionary<string, double[]> datos = new Dictionary<string, double[]>();
            Dictionary<string, List<DateTime>> palas = Consultas.getDatosPalas();
            Dictionary < string, List<DateTime> > chancadores = Consultas.getDatosChancadores();
            Dictionary<string, double[]> mitigacion = Consultas.getDatosMitigacion(inicio, fin);

            foreach (KeyValuePair<string, double[]> fila in metereologicos)
            {
                DateTime fecha_actual = DateTime.ParseExact(fila.Key, "yyyy-MM-dd HH:mm:ss", System.Globalization.CultureInfo.InvariantCulture);

                int num_columnas = 32;
                int indice = 0; // usado para los limites en la normalizacion.
                int columna_actual = 0;
                double valor_mp10 = 0;
                double[] dato = new double[num_columnas];
                double valor = 0;
                Entrada entrada = new Entrada();

                // datos metereologicos.
                valor = fecha_actual.Month;
                if (normalizar) valor = entrada.normalizar(valor, 0);

                dato[0] = valor; // estacion.

                valor = fecha_actual.Hour;
                if (normalizar) valor = entrada.normalizar(valor, 1);

                dato[1] = valor; // hora.

                columna_actual = 2;
                indice = columna_actual;

                for (int i = 0; i < 14; i++)
                {
                    valor = fila.Value[i];

                    if (normalizar) valor = entrada.normalizar(valor, indice);

                    if (i != 4 && i != 6 && i != 7)
                    {
                        if (fila.Value[i] == -1)
                            dato[columna_actual] = 0;
                        else
                            dato[columna_actual] = valor;

                        columna_actual += 1;
                    }
                    else if (i == 4)
                    {
                        valor_mp10 = valor;
                    }

                    indice += 1;
                }

                // palas.
                foreach (KeyValuePair<string, List<DateTime>> pala in palas)
                {
                    if (pala.Value.Contains(fecha_actual)) dato[columna_actual] = 1;
                    else dato[columna_actual] = 0;
                    columna_actual += 1;
                    indice += 1;
                }

                // chancadores.
                foreach (KeyValuePair<string, List<DateTime>> chancador in chancadores)
                {
                    if (chancador.Value.Contains(fecha_actual)) dato[columna_actual] = 1;
                    else dato[columna_actual] = 0;
                    columna_actual += 1;
                    indice += 1;
                }

                // mitigacion.
                string fecha = fecha_actual.ToString("yyyy-MM-dd");
                double[] fila_mitigacion;

                if (mitigacion.ContainsKey(fecha))
                    fila_mitigacion = mitigacion[fecha_actual.ToString("yyyy-MM-dd")];
                else
                    fila_mitigacion = new double[]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

                for (int i = 0; i < 4; i += 2)
                {
                    if (fecha_actual.Hour >= 8 && fecha_actual.Hour <= 18)
                        valor = fila_mitigacion[i];
                    else
                        valor = fila_mitigacion[i + 1];

                    if (normalizar) valor = entrada.normalizar(valor, indice);

                    dato[columna_actual] = valor;

                    columna_actual += 1;
                    indice += 1;
                }

                for (int i = 4; i < fila_mitigacion.Length; i++)
                {
                    valor = fila_mitigacion[i];

                    if (normalizar) valor = entrada.normalizar(valor, indice);

                    dato[columna_actual] = valor;
                    columna_actual += 1;
                    indice += 1;
                }

                dato[columna_actual] = valor_mp10;

                datos.Add(fila.Key, dato);
            }

            return datos;
        }

        public static Dictionary<string, double[]> getDatosMeteorologicosFecha(DateTime fecha)
        {
            Dictionary<string, double[]> datos = new Dictionary<string, double[]>();

            BD bd = new BD();

            if (bd.conectar())
            {
                bd.consulta("SELECT * FROM meteorologicohora WHERE fecha = @fecha");

                bd.setParamTimestamp("fecha");
                bd.prepare();
                bd.agregarParametro(0, fecha);

                NpgsqlDataReader resultados = bd.executeReader();

                datos = getDatosMeteorologicos(resultados);

                bd.cerrar();
            }

            return datos;
        }

        /// <summary>
        /// Obtiene los datos meteorologicos entre las fechas indicadas.
        /// </summary>
        /// <param name="inicio"></param>
        /// <param name="fin"></param>
        /// <returns></returns>
        public static Dictionary<string, double[]> getDatosMeteorologicos(DateTime inicio, DateTime fin)
        {
            Dictionary<string, double[]> datos = new Dictionary<string, double[]>();

            BD bd = new BD();

            if (bd.conectar())
            {
                bd.consulta("SELECT * FROM meteorologicohora WHERE fecha BETWEEN @fecha_inicio AND @fecha_final ORDER BY fecha ");

                bd.setParamTimestamp("fecha_inicio");
                bd.setParamTimestamp("fecha_final");
                bd.prepare();
                bd.agregarParametro(0, inicio);
                bd.agregarParametro(1, fin);

                NpgsqlDataReader resultados = bd.executeReader();

                datos = getDatosMeteorologicos(resultados);

                bd.cerrar();
            }

            return datos;
        }

        /// <summary>
        /// Obtiene los datos meteorologicos mayores a mp10 entre las fechas indicadas.
        /// </summary>
        /// <param name="inicio"></param>
        /// <param name="fin"></param>
        /// <param name="mp10"></param>
        /// <returns></returns>
        public static Dictionary<string, double[]> getDatosMeteorologicos(DateTime inicio, DateTime fin, double mp10)
        {
            Dictionary<string, double[]> datos = new Dictionary<string, double[]>();

            BD bd = new BD();

            if (bd.conectar())
            {
                bd.consulta("SELECT * FROM meteorologicohora WHERE fecha BETWEEN @fecha_inicio AND @fecha_final AND mp10 > @mp10 ORDER BY fecha ");

                bd.setParamTimestamp("fecha_inicio");
                bd.setParamTimestamp("fecha_final");
                bd.setParamDouble("mp10");
                bd.prepare();
                bd.agregarParametro(0, inicio);
                bd.agregarParametro(1, fin);
                bd.agregarParametro(2, mp10);

                NpgsqlDataReader resultados = bd.executeReader();

                datos = getDatosMeteorologicos(resultados);

                bd.cerrar();
            }

            return datos;
        }

        public static Dictionary<string, double[]> getDatosMeteorologicos(NpgsqlDataReader resultados)
        {
            Dictionary<string, double[]> datos = new Dictionary<string, double[]>();

            while (resultados.Read())
            {
                int num_columnas = 19;
                double[] columnas = new double[num_columnas];

                for (int i = 0; i < num_columnas; i++)
                    columnas[i] = resultados.GetDouble(i + 1);

                datos[resultados.GetTimeStamp(0).ToString()] = columnas;
            }

            return datos;
        }

        public static Dictionary<string, List<DateTime>> getDatosPalas()
        {
            Dictionary<string, List<DateTime>> palas = new Dictionary<string, List<DateTime>>();

            palas["pa01"] = new List<DateTime>();
            palas["pa03"] = new List<DateTime>();
            palas["pa04"] = new List<DateTime>();
            palas["pa05"] = new List<DateTime>();
            palas["pa07"] = new List<DateTime>();
            palas["cf08"] = new List<DateTime>();
            palas["cf10"] = new List<DateTime>();
            palas["cf11"] = new List<DateTime>();

            BD bd = new BD();

            if (bd.conectar())
            {
                bd.consulta("SELECT * FROM detencion_palas WHERE fecha_inicio is not null and fecha_termino is not null");

                NpgsqlDataReader resultados = bd.executeReader();

                while (resultados.Read())
                {
                    DateTime fechaInicio = (DateTime)resultados[3];
                    DateTime fechaTermino = (DateTime)resultados[4];
                    TimeSpan intervalo = fechaTermino - fechaInicio;
                    String equipo = (String) resultados[2];

                    if (intervalo.TotalDays < 10 && intervalo.TotalMilliseconds > 0)
                    {
                        bool encontrado = false;
                        int num_palas = 8;
                        String[] nombre_palas = { "01", "03", "04", "05", "07", "08", "10", "11" };

                        equipo = equipo.Replace("-", "").ToLower();

                        for (int i = 0; i < num_palas && !encontrado; i++)
                        {
                            string chancador_actual = "";

                            if (equipo.ToLower().Contains("pa") && (equipo.Contains(nombre_palas[i]) || equipo.Contains(nombre_palas[i].Replace("0", ""))))
                            {
                                chancador_actual = "pa" + nombre_palas[i];
                                encontrado = true;
                            }
                            else if (equipo.ToLower().Contains("cf") && equipo.Contains(nombre_palas[i]))
                            {
                                chancador_actual = "cf" + nombre_palas[i];
                                encontrado = true;
                            }

                            if (encontrado)
                            {
                                DateTime fechaActual = new DateTime(fechaInicio.Year, fechaInicio.Month, fechaInicio.Day, fechaInicio.Hour, 0, 0);

                                while (fechaTermino > fechaActual)
                                {
                                    if (!palas[chancador_actual].Contains(fechaActual))
                                    {
                                        palas[chancador_actual].Add(fechaActual);
                                    }

                                    fechaActual = fechaActual.AddHours(1);
                                }
                            }
                        }
                    }
                }

                bd.cerrar();
            }

            return palas;
        }

        public static Dictionary<string, List<DateTime>> getDatosChancadores()
        {
            Dictionary<string, List<DateTime>> chancadores = new Dictionary<string, List<DateTime>>();

            chancadores["ch01"] = new List<DateTime>();
            chancadores["ch02"] = new List<DateTime>();

            BD bd = new BD();

            if (bd.conectar())
            {
                bd.consulta("SELECT * FROM detencion_chancado WHERE fecha_inicio is not null and fecha_termino is not null");

                NpgsqlDataReader resultados = bd.executeReader();

                while (resultados.Read())
                {
                    DateTime fechaInicio = (DateTime)resultados[2];
                    DateTime fechaTermino = (DateTime)resultados[3];
                    TimeSpan intervalo = fechaTermino - fechaInicio;
                    String equipo = (String)resultados[1];

                    if (intervalo.TotalDays < 10)
                    {
                        bool encontrado = false;
                        int num_chancadores = 2;
                        String[] nombre_chancadores = { "01", "02" };

                        equipo = equipo.Replace("-", "").ToLower();

                        for (int i = 0; i < num_chancadores && !encontrado; i++)
                        {
                            string chancador_actual = "";

                            if (equipo.ToLower().Contains("ch") && (equipo.Contains(nombre_chancadores[i]) || equipo.Contains(nombre_chancadores[i].Replace("0", ""))))
                            {
                                chancador_actual = "ch" + nombre_chancadores[i];

                                DateTime fechaActual = new DateTime(fechaInicio.Year, fechaInicio.Month, fechaInicio.Day, fechaInicio.Hour, 0, 0);

                                while (fechaTermino > fechaActual)
                                {
                                    if (!chancadores[chancador_actual].Contains(fechaActual))
                                    {
                                        chancadores[chancador_actual].Add(fechaActual);
                                    }

                                    fechaActual = fechaActual.AddHours(1);
                                }

                                encontrado = true;
                            }
                        }
                    }
                }

                bd.cerrar();
            }

            return chancadores;
        }

        public static Dictionary<string, double[]> getDatosMitigacion(DateTime inicio, DateTime fin)
        {
            Dictionary<string, double[]> datos = new Dictionary<string, double[]>();

            BD bd = new BD();

            if (bd.conectar())
            {
                bd.consulta("SELECT * FROM mitigacion WHERE fecha BETWEEN @fecha_inicio AND @fecha_final ORDER BY fecha ASC");

                bd.setParamTimestamp("fecha_inicio");
                bd.setParamTimestamp("fecha_final");
                bd.prepare();
                bd.agregarParametro(0, inicio);
                bd.agregarParametro(1, fin);

                NpgsqlDataReader resultados = bd.executeReader();

                while (resultados.Read())
                {
                    int num_columnas = 10;
                    double[] columnas = new double[num_columnas];

                    for (int i = 0; i < num_columnas; i++)
                        columnas[i] = resultados.GetDouble(i + 1);

                    datos[resultados.GetTimeStamp(0).ToString()] = columnas;
                }

                bd.cerrar();
            }

            return datos;
        }
    }
}
