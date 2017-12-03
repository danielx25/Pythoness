using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using iTextSharp.text.pdf;
using iTextSharp.text;
using System.IO;

namespace Reportes
{
    public class Reporte
    {

        static public void generar(string rutaFichero, List<string> diasPrediccion, Dictionary<string, Dictionary<string, double>> datos, double[] predicciones)
        {
            PdfPTable table = new PdfPTable(datos.Count + 1);
            Document reporte = Reporte.crearPDF(rutaFichero);
            string[] variables = Reporte.getVariables();
            string[] dias = new string[] { "dia_1", "dia_2", "dia_3", "dia_4", "dia_5" };

            reporte.Open();

            tituloReporte(reporte);

            table.AddCell("Variable");

            for (int i = 0; i < dias.Length; i++)
            {
                if (diasPrediccion.Contains(dias[i]))
                {
                    table.AddCell("Día " + (i + 1));
                }
            }

            for (int i = 0; i < variables.Length; i++)
            {
                string variable = variables[i];

                table.AddCell(variable);

                for (int j = 0; j < dias.Length; j++)
                {
                    string dia = dias[j];

                    if (diasPrediccion.Contains(dia))
                    {
                        string valor = "";

                        if (variable == "mp10") valor += predicciones[j];
                        else valor += datos[dia][variable];

                        table.AddCell(valor);
                    }
                }
            }

            reporte.Add(table);

            reporte.Close();
        }

        static private Document crearPDF(string rutaFichero)
        {
            Document documento = new Document(iTextSharp.text.PageSize.LETTER, 10, 10, 42, 35);
            PdfWriter writer = PdfWriter.GetInstance(documento, new FileStream(rutaFichero, FileMode.Create));

            return documento;
        }

        static private void tituloReporte(Document reporte)
        {
            Paragraph titulo = new Paragraph("PREDICCIÓN NIVEL MP10", Fuentes.Cursiva(16));
            titulo.Alignment = Element.ALIGN_CENTER;
            reporte.Add(titulo);

            Paragraph separador = new Paragraph("_______________________________", Fuentes.Delineado(16));
            separador.Alignment = Element.ALIGN_CENTER;
            reporte.Add(separador);

            Paragraph espacios = new Paragraph("\n\n\n", Fuentes.Cursiva(16));
            espacios.Alignment = Element.ALIGN_CENTER;
            reporte.Add(espacios);
        }

        static private string[] getVariables()
        {
            string[] variables = new string[32];

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

            return variables;
        }
    }
}
