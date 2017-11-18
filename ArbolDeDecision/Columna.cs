using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArbolDeDecision
{
    public class Columna
    {
        private List<string> atributosDiscretos = null;
        private List<double> atributosContinuos = null;
        private bool isContinuo = false;
        private ArrayList lista;

        private String clase;
        
        public Columna(String clase, int numFilas, bool isContinuo)
        {
            this.clase = clase;
            this.isContinuo = isContinuo;
            lista = new ArrayList();
            for (int i=0; i<numFilas; i++)
            {
                if (isContinuo == true)
                    lista.Add(0);
                else
                    lista.Add("none");
            }
        }

        public bool IsContinuo
        {
            get
            {
                return isContinuo;
            }
        }

        public object this[int indice]
        {
            get
            {
                return lista[indice];
            }

            set
            {
                lista[indice] = value;
            }
        }

        public List<String> getAtributosDiscretos()
        {
            return atributosDiscretos;
        }


        public List<double> getAtributosContinuos()
        {
            return atributosContinuos;
        }

        public void addAtributo(List<String> attrs)
        {
            this.atributosDiscretos = attrs;
        }

        public void addAtributo(List<double> attrs)
        {
            this.atributosContinuos = attrs;
        }

        public String getClase()
        {
            return this.clase;
        }

        public int getTam()
        {
            return lista.Count;
        }

        public int getFrecuenciaAtributo(String atributo)
        {
            int contador = 0;
            for(int i=0; i<lista.Count;i++)
            {
                if(atributo.Equals(lista[i]))
                {
                    contador += 1;
                }
            }
            return contador;
        }

        public int getFrecuenciaAtributo(int indexAtributo)
        {
            double limitInferior = -1 * Double.PositiveInfinity;
            double limitSuperior = Double.PositiveInfinity;
            if (indexAtributo > 0)
                limitInferior = atributosContinuos[indexAtributo - 1];
            if (indexAtributo < atributosContinuos.Count)
                limitSuperior = atributosContinuos[indexAtributo];
            double atributoC;
            int contador = 0;
            for (int i = 0; i < lista.Count; i++)
            {
                atributoC = System.Convert.ToDouble(lista[i]);
                if (atributoC >= limitInferior && atributoC < limitSuperior)
                    contador += 1;
            }
            return contador;
        }

        public void eliminarFila(int indice)
        {
            lista.RemoveAt(indice);
        }

        protected void setValores(ArrayList array, List<string> atrr)
        {
            lista = new ArrayList(array);
            atributosDiscretos = new List<string>(atrr);
        }

        protected void setValores(ArrayList array, List<double> atrr)
        {
            lista = new ArrayList(array);
            atributosContinuos = new List<double>(atrr);
        }

        public void analizarDatos()
        {
            if (isContinuo == false)
                atributosDiscretos = lista.Cast<String>().Distinct().ToList();
            //else
            //    atributosContinuos = lista.Cast<double>().Distinct().ToList();

        }

        public Columna Clone()
        {
            Columna columna = new Columna(this.clase, lista.Count, this.isContinuo);
            if(isContinuo)
                columna.setValores(lista, atributosContinuos);
            else
                columna.setValores(lista, atributosDiscretos);
            return columna;
        }

        public int getCountAtributos()
        {
            if (isContinuo)
                return atributosContinuos.Count;
            else
                return atributosDiscretos.Count;
        }

    }
}