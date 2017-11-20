using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArbolDeDecision
{
    [Serializable]
    public class Nodo
    {
        private bool esHoja = false;
        private bool esContinuo = false;
        private String clase;
        private List<String> atributosDiscretos;
        private List<double> atributosContinuos;
#pragma warning disable CS0169 // El campo 'Nodo.division' nunca se usa
        private double division;
#pragma warning restore CS0169 // El campo 'Nodo.division' nunca se usa
        private List<Nodo> punteros = new List<Nodo>();

#pragma warning disable CS0414 // El campo 'Nodo.radioGanacia' está asignado pero su valor nunca se usa
        private double radioGanacia = 0.0; 
#pragma warning restore CS0414 // El campo 'Nodo.radioGanacia' está asignado pero su valor nunca se usa
        private double ganancia = 0.0;
#pragma warning disable CS0414 // El campo 'Nodo.distancia' está asignado pero su valor nunca se usa
        private double distancia = 0.0;
#pragma warning restore CS0414 // El campo 'Nodo.distancia' está asignado pero su valor nunca se usa

        public Nodo(String clase, List<String> atributosDiscretos)
        {
            this.clase = clase;
            this.atributosDiscretos = atributosDiscretos;
            esContinuo = false;
            punteros = new List<Nodo>();
        }

        public Nodo(String atributo_salida)
        {
            clase = atributo_salida;
            esHoja = true;
            esContinuo = false;
            atributosDiscretos = null;
            punteros = null;
        }

        public Nodo(String clase, List<double> atributos)
        {
            this.clase = clase;
            esContinuo = true;
            punteros = new List<Nodo>();
            this.atributosContinuos = atributos;
        }

        public Nodo this[int indice]
        {
            get
            {
                return punteros[indice];
            }

            set
            {
            }
        }

        public bool IsContinuo
        {
            get
            {
                return esContinuo;
            }
        }

        public void agregarNodo(Nodo nodo)
        {
            punteros.Add(nodo);
        }

        public Nodo getNodo(int i)
        {
            return punteros[i];
        }

        public Nodo getNodo(string atributo)
        {
            int i = atributosDiscretos.IndexOf(atributo);
            return punteros[i];
        }

        public String getNombreClase()
        {
            return clase;
        }

        public bool getEsHoja()
        {
            return this.esHoja;
        } 

        public int getCountPuntero()
        {
            return punteros.Count();
        }

        public List<String> getatributosDiscretos()
        {
            return atributosDiscretos;
        }

        public List<double> getatributosContinuos()
        {
            return atributosContinuos;
        }

        public void setGanancia(double ganancia)
        {
            this.ganancia = ganancia;
        }
    }
}
