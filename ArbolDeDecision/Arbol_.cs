using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArbolDeDecision
{
    [Serializable]
    public class Arbol_
    {
        private string nombreAlgortimo = "ID3s";
        private Nodo raiz = null;
        private double tiempo = 0;
        private int profundidadArbol = 0;
        private int numeroHojas = 0;
        private int numeroNodos = 0;

        public Arbol_(string nombreAlgoritmo1)
        {
            this.nombreAlgortimo = nombreAlgoritmo1;
        }

        public void setRaiz(Nodo nodo)
        {
            raiz = nodo;
        }

        public string NombreAlgoritmo
        {
            get
            {
                return nombreAlgortimo;
            }
        }

        public void agregarNodo()
        {

        }

        public override string ToString()
        {
            List<string> lista = new List<string>();
            mostrarArbol(raiz, "", lista);
            foreach(string linea in lista)
            {
                System.Console.Write(linea);
            }
            return null;
        }

        public void mostrarArbol(Nodo nodo, string spacio, List<string> lista)
        {
            //System.Console.WriteLine(spacio+"nombre: " + nodo.getNombreClase());
            lista.Add(spacio + "nombre: " + nodo.getNombreClase()+"\n");
            if (nodo.getEsHoja() == false)
            {
                if(nodo.IsContinuo)
                {
                    List<double> atributos = nodo.getatributosContinuos();
                    for (int i = 0; i < nodo.getCountPuntero(); i++)
                    {
                        double limitInferior = -1 * Double.PositiveInfinity;
                        double limitSuperior = Double.PositiveInfinity;
                        if (i > 0)
                            limitInferior = atributos[i - 1];
                        if (i < atributos.Count)
                            limitSuperior = atributos[i];


                        Nodo nuevoNodo = (Nodo)nodo[i];
                        //System.Console.WriteLine(spacio + "  atrr:"+atributos[i]);
                        lista.Add(spacio + "  atrr:" + limitInferior+"< x <"+limitSuperior + "\n");
                        mostrarArbol(nuevoNodo, spacio + "     ", lista);
                       
                    }
                }
                else
                {

                    List<String> atributos = nodo.getatributosDiscretos();
                    for (int i = 0; i < nodo.getCountPuntero(); i++)
                    {
                        Nodo nuevoNodo = (Nodo)nodo[i];
                        //System.Console.WriteLine(spacio + "  atrr:"+atributos[i]);
                        lista.Add(spacio + "  atrr:" + atributos[i] + "\n");
                        mostrarArbol(nuevoNodo, spacio + "     ", lista);

                    }

                }
            }
            

        }
        public void analisisArbol()
        {
            numeroHojas = 0;
            numeroNodos = 0;
            analisisArbol(raiz, 0);
        }
        private void analisisArbol(Nodo nodo, int nivel)
        {
            numeroNodos += 1;
            nivel += 1;
            if (nodo.getEsHoja() == false)
                for (int i = 0; i < nodo.getCountPuntero(); i++)
                {
                    analisisArbol((Nodo)nodo[i], nivel);
                }
            else
            {
                if (profundidadArbol < nivel)
                    profundidadArbol = nivel;
                numeroHojas += 1;
            }
        }

        public int NumeroNodos
        {
            get
            {
                return numeroNodos;
            }
        }

        /*public void produccionReglas(Nodo nodo,  List<string> lista)
        {
            
            if (!nodo.getEsHoja())
                lista.Add(" AND "+nodo.getNombreClase() + " == ");
            else
                lista.Add(" THEN VALUE = "+)
            if (nodo.getEsHoja() == false)
                for (int i = 0; i < nodo.getCountPuntero(); i++)
                {
                    List<String> atributos = nodo.getatributosDiscretos();
                    Nodo nuevoNodo = (Nodo)nodo[i];
                    if (nuevoNodo.getEsHoja())
                    lista.Add( "  atrr:" + atributos[i] + "\n");
                    produccionReglas (nuevoNodo, lista);
                }
            else
            {

            }
        }*/
        public Nodo Raiz
        {
            get
            {
                return raiz;
            }
        }

        public double Tiempo
        {
            set
            {
                tiempo = value;
            }

            get
            {
                return tiempo;
            }
        }

        public int ProfundidadArbol
        {
            set
            {
                profundidadArbol = value;
            }

            get
            {
                return profundidadArbol;
            }
        }

        public int NumeroHojas
        {
            set
            {
                numeroHojas = value;
            }

            get
            {
                return numeroHojas;
            }
        }

        public void guardarArbol(string fileName)
        {
            
                TextWriter tw = new StreamWriter(fileName, true);
                List<string> lista = new List<string>();
                mostrarArbol(raiz, "", lista);
                foreach (string linea in lista)
                {
                    tw.Write(linea);
                }
                
                tw.Close();
            
        }

        public void guardarReglas(string archivo)
        {
            TextWriter tw = new StreamWriter(archivo);
            List<string> lista = new List<string>();
            produccionReglas(raiz, lista, "Si ");
            foreach (string linea in lista)
            {
                tw.WriteLine(linea);
            }

            tw.Close();
        }

        public void produccionReglas(Nodo nodo, List<string> lista, string regla_actual)
        {
            if (nodo.getEsHoja() == false)
            {
                regla_actual += nodo.getNombreClase() + " es ";
                if (nodo.IsContinuo)
                {
                    List<double> atributos = nodo.getatributosContinuos();
                    for (int i = 0; i < nodo.getCountPuntero(); i++)
                    {
                        double limitInferior = -1 * Double.PositiveInfinity;
                        double limitSuperior = Double.PositiveInfinity;
                        if (i > 0)
                            limitInferior = atributos[i - 1];
                        if (i < atributos.Count)
                            limitSuperior = atributos[i];


                        Nodo nuevoNodo = (Nodo)nodo[i];
                        //System.Console.WriteLine(spacio + "  atrr:"+atributos[i]);
                        lista.Add("  atrr:" + limitInferior + "< x <" + limitSuperior + "\n");
                        mostrarArbol(nuevoNodo, "     ", lista);

                    }
                }
                else
                {

                    List<String> atributos = nodo.getatributosDiscretos();
                    for (int i = 0; i < nodo.getCountPuntero(); i++)
                    {
                        Nodo nuevoNodo = (Nodo)nodo[i];
                        //regla_actual += atributos[i] + " y ";
                        produccionReglas(nuevoNodo, lista, regla_actual + atributos[i] + " y ");

                    }

                }
            }
            else
            {
                regla_actual += "entonces mp10 " + nodo.getNombreClase();
                lista.Add(regla_actual);
            }
        }
    }
}
