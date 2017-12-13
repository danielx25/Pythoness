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
            int ancho = datos.Count + 3;
            PdfPTable table = new PdfPTable(ancho);
            Document reporte = Reporte.crearPDF(rutaFichero);
            Tuple<string, string>[] variables = Reporte.getVariables();
            string[] dias =new string[] { "dia_1", "dia_2", "dia_3", "dia_4", "dia_5" };

            reporte.Open();

            //tituloReporte(reporte);

            PdfPCell celda_titulo = new PdfPCell(new Phrase("PREDICCIÓN MP10"));
            celda_titulo.Colspan = ancho;
            celda_titulo.HorizontalAlignment = 1;
            table.AddCell(celda_titulo);
            PdfPCell celda_var = new PdfPCell(new Phrase("Variable"));
            celda_var.Colspan = 2;
            table.AddCell(celda_var);
            table.AddCell("Unidad");

            for (int i = 0; i < dias.Length; i++)
            {
                if (diasPrediccion.Contains(dias[i]))
                {
                    table.AddCell("Día " + (i + 1));
                }
            }

            for (int i = 0; i < variables.Length; i++)
            {
                string variable =variables[i].Item1;
                string unidad = variables[i].Item2;
                PdfPCell nom_var = new PdfPCell(new Phrase(variable));
                nom_var.Colspan = 2;
                table.AddCell(nom_var);
                table.AddCell(unidad);

                for (int j = 0; j < dias.Length; j++)
                {
                    string dia =dias[j];

                    if (diasPrediccion.Contains(dia))
                    {
                        string valor ="";

                        if (variable == "mp10") valor += Math.Round(predicciones[j]);
                        else valor += Math.Round(datos[dia][variable], 2);

                        table.AddCell(valor);
                    }
                }
            }

            reporte.Add(table);

            reporte.Close();
        }

        static private Document crearPDF(string rutaFichero)
        {
            Document documento =new Document(iTextSharp.text.PageSize.LETTER, 10, 10, 42, 35);
            PdfWriter writer =PdfWriter.GetInstance(documento, new FileStream(rutaFichero, FileMode.Create));

            return documento;
        }

        static private void tituloReporte(Document reporte)
        {
            Paragraph titulo =new Paragraph("PREDICCIÓN NIVEL MP10", Fuentes.Cursiva(16));
            titulo.Alignment =Element.ALIGN_CENTER;
            reporte.Add(titulo);

            Paragraph separador =new Paragraph("_______________________________", Fuentes.Delineado(16));
            separador.Alignment =Element.ALIGN_CENTER;
            reporte.Add(separador);

            Paragraph espacios =new Paragraph("\n\n\n", Fuentes.Cursiva(16));
            espacios.Alignment =Element.ALIGN_CENTER;
            reporte.Add(espacios);
        }

        static private Tuple<string, string>[] getVariables()
        {
            Tuple<string, string>[] variables = new Tuple<string, string>[32];

            variables[0] = Tuple.Create("estacion", "mes");
            variables[1] = Tuple.Create("hora", "");
            variables[2] = Tuple.Create("velocidad_viento", "m/s");
            variables[3] = Tuple.Create("direccion_viento", "grados");
            variables[4] = Tuple.Create("temperatura", "°C");
            variables[5] = Tuple.Create("humedad_relativa", "%");
            variables[6] = Tuple.Create("radiacion_solar", "W/m2");
            variables[7] = Tuple.Create("precipitacion_dia1", "mm");
            variables[8] = Tuple.Create("precipitacion_dia2", "mm");
            variables[9] = Tuple.Create("precipitacion_dia3", "mm");
            variables[10] = Tuple.Create("precipitacion_dia4", "mm");
            variables[11] = Tuple.Create("precipitacion_dia5", "mm");
            variables[12] = Tuple.Create("evaporacion", "mm");
            variables[13] = Tuple.Create("pala1", "");
            variables[14] = Tuple.Create("pala3", "");
            variables[15] = Tuple.Create("pala4", "");
            variables[16] = Tuple.Create("pala5", "");
            variables[17] = Tuple.Create("pala7", "");
            variables[18] = Tuple.Create("pala8", "");
            variables[19] = Tuple.Create("pala10", "");
            variables[20] = Tuple.Create("pala11", "");
            variables[21] = Tuple.Create("chancador1", "");
            variables[22] = Tuple.Create("chancador2", "");
            variables[23] = Tuple.Create("chaxa_camion", "cantidad");
            variables[24] = Tuple.Create("movitec_camion", "cantidad");
            variables[25] = Tuple.Create("das_camion", "cantidad");
            variables[26] = Tuple.Create("cnorte_consumo_agua", "m3");
            variables[27] = Tuple.Create("cmovil_consumo_agua", "m3");
            variables[28] = Tuple.Create("cachimba1_consumo_agua", "m3");
            variables[29] = Tuple.Create("cachimba2_consumo_agua", "m3");
            variables[30] = Tuple.Create("gerencia_consumo_agua", "m3");
            variables[31] = Tuple.Create("mp10", "");

            return variables;
        }
    }
}
