using ArbolDeDecision;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace ArbolDeDecision
{
    class Archivo
    {
        public static void Serializar(Arbol_ datos, string archivo)
        {
            FileStream archivoGuardar = new FileStream(archivo, FileMode.Create);
            BinaryFormatter binario = new BinaryFormatter();
            binario.Serialize(archivoGuardar, datos);
            archivoGuardar.Close();
        }

        public static Arbol_ Deserializar(string archivo)
        {
            FileStream archivoAbrir = new FileStream(archivo, FileMode.Open);
            BinaryFormatter binario = new BinaryFormatter();
            Arbol_ datos = binario.Deserialize(archivoAbrir) as Arbol_;
            archivoAbrir.Close();
            return datos;
        }
    }
}
