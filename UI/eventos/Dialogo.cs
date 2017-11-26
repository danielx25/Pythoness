using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MahApps.Metro.Controls.Dialogs;

namespace UI.eventos
{
    public class Dialogo
    {
        public static string seleccionArchivo(string defecto)
        {
            string archivo = defecto;
            OpenFileDialog dialogo = new OpenFileDialog();

            dialogo.Filter = "Text Files (.txt)|*.txt|All Files (*.*)|*.*";
            dialogo.FilterIndex = 1;

            //openFileDialog1.Multiselect = true;

            bool? userClickedOK = dialogo.ShowDialog();

            if (userClickedOK == true) archivo = dialogo.FileName;

            return archivo;
        }
    }
}
