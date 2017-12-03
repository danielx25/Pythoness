﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using iTextSharp.text.pdf;
using iTextSharp.text;

namespace Reportes
{
    public class Fuentes
    {
        static public Font Cursiva(int size)
        {
            BaseFont bfTimes = BaseFont.CreateFont(BaseFont.TIMES_ROMAN, BaseFont.CP1252, false);
            Font fuente = new iTextSharp.text.Font(bfTimes, size, Font.ITALIC, BaseColor.BLACK);
            return (fuente);
        }

        static public Font Subrayado(int size)
        {
            BaseFont bfTimes = BaseFont.CreateFont(BaseFont.TIMES_ROMAN, BaseFont.CP1252, false);
            Font fuente = new iTextSharp.text.Font(bfTimes, size, Font.UNDERLINE, BaseColor.BLACK);
            return (fuente);
        }

        static public Font Negrita(int size)
        {
            BaseFont bfTimes = BaseFont.CreateFont(BaseFont.TIMES_ROMAN, BaseFont.CP1252, false);
            Font fuente = new iTextSharp.text.Font(bfTimes, size, Font.BOLD, BaseColor.BLACK);
            return (fuente);
        }

        static public Font Normal(int size)
        {
            BaseFont bfTimes = BaseFont.CreateFont(BaseFont.TIMES_ROMAN, BaseFont.CP1252, false);
            Font fuente = new iTextSharp.text.Font(bfTimes, size, Font.NORMAL, BaseColor.BLACK);
            return (fuente);
        }

        static public Font Delineado(int size)
        {
            BaseFont bfTimes = BaseFont.CreateFont(BaseFont.HELVETICA, BaseFont.CP1252, false);
            Font fuente = new iTextSharp.text.Font(bfTimes, size, Font.NORMAL, BaseColor.BLACK);
            return (fuente);
        }
    }
}
