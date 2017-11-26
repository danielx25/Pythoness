using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using ArbolDeDecision;

namespace PruebasCS
{
    public class PruebasReglas
    {
        Columna[] columnas;
        int num_filas;
        int num_variables;
        String[] variables;
        String[] datos;
        Dictionary<String, List<String>> valores_variables;
        Tabla dataset;

        public PruebasReglas()
        {
            dataset = new Tabla();
            valores_variables = new Dictionary<string, List<string>>();
            setValoresVariables("valores_variables.csv");
            setVariables();
        }

        public void extraccionReglas(String archv_datos, String archv_reglas)
        {
            datos = File.ReadAllLines(archv_datos);
            num_filas = datos.Count();
            columnas = new Columna[num_variables];

            // seteamos los atributos.
            for (int i = 0; i < num_variables; i++)
                setAtributo(i, variables[i]);

            // agregamos los valores a las columnas (variables).
            for (int i = 0; i < num_filas; i++)
            {
                String[] valores = datos[i].Split(';');

                for (int j = 0; j < valores.Count(); j++)
                    columnas[j][i] = valores[j];
            }

            for (int i = 0; i < num_variables; i++)
                dataset.agregarColumna(columnas[i]);

            C45 c45 = new C45();
            c45.cargarTablaC45(dataset);
            c45.iniciarC45("reglasC45.txt");
        }

        public void setAtributo(int columna, String nombre)
        {
            List<String> attrs = valores_variables[nombre];
            columnas[columna] = new Columna(nombre, num_filas, false);
            columnas[columna].addAtributo(attrs);
        }

        public void setValoresVariables(String archivo)
        {
            String[] filas = File.ReadAllLines(archivo);
            int fila_actual = 0;

            foreach(String fila in filas)
            {
                String[] valores = fila.Split(';');
                List<String> attrs = new List<string>();

                for(int i = 1; i < valores.Count(); i++)
                    attrs.Add(valores[i]);

                valores_variables.Add(valores[0], attrs);

                fila_actual += 1;
            }

            num_variables = fila_actual;
        }

        public void setVariables()
        {
            variables = new String[num_variables];

            variables[0] = "estacion";
            variables[1] = "hora";
            variables[2] = "velocidad_viento";
            variables[3] = "direccion_viento";
            variables[4] = "temperatura";
            variables[5] = "humedad_relativa";
            variables[6] = "radiacion_solar";
            variables[7] = "precipitacion_dia1";
            variables[8] = "precipitacion_dia2";
            variables[9] = "precipitacion_dia3";
            variables[10] = "precipitacion_dia4";
            variables[11] = "precipitacion_dia5";
            variables[12] = "evaporacion";
            variables[13] = "pala1";
            variables[14] = "pala3";
            variables[15] = "pala4";
            variables[16] = "pala5";
            variables[17] = "pala7";
            variables[18] = "pala8";
            variables[19] = "pala10";
            variables[20] = "pala11";
            variables[21] = "chancador1";
            variables[22] = "chancador2";
            variables[23] = "chaxa_camion";
            variables[24] = "movitec_camion";
            variables[25] = "das_camion";
            variables[26] = "cnorte_consumo_agua";
            variables[27] = "cmovil_consumo_agua";
            variables[28] = "cachimba1_consumo_agua";
            variables[29] = "cachimba2_consumo_agua";
            variables[30] = "gerencia_consumo_agua";
            variables[31] = "mp10";
        }
    }
}
