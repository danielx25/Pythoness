using ArbolDeDecision;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArbolDeDecision
{
    public class C45: ID3_
    {
        private double promedioGanancia = 0;
        //public Nodo algoritmoC45()
        //{
        //    return null;
        //}

        public void cargarTablaC45(Tabla tabla)
        {
            this.tabla = tabla;
            arbol = new Arbol_("C45");
            promedioGanancia = promedioGanancias(this.tabla);
        }

        public void iniciarC45(string archv_salida)
        {
            //inicio cronometro
            //Stopwatch stopwatch = new Stopwatch();
            //stopwatch.Restart();

            arbol.setRaiz(algoritmoC45(tabla, tabla.getClases()));
            //System.Console.WriteLine(arbol);
            //arbol.guardarArbol("arbolC45.txt");
            arbol.guardarReglas(archv_salida);

            // termino cronometro + resultados C4.5
            /*stopwatch.Stop();
            TimeSpan tiempoC45 = stopwatch.Elapsed;
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            tiempoC45.Hours, tiempoC45.Minutes, tiempoC45.Seconds,
            tiempoC45.Milliseconds / 10);
            string elapsedMilisecons = String.Format(" {0} ", tiempoC45.Milliseconds);
            Console.WriteLine("RunTime: " + elapsedTime);
            Console.WriteLine("Runtime: " + elapsedMilisecons + " miliseconds");
            arbol.Tiempo = tiempoC45.Milliseconds;*/
        }

        public Nodo algoritmoC45(Tabla tabla, List<String> atributos)
        {
            Nodo raiz = null;
            if (siTodosEjemplosSonLosMismos(tabla) != -1)
            {
                Columna columna = tabla.getColumnaAtributoSalida();
                String aSalida = (String)columna[0];
                raiz = new Nodo(aSalida);
                return raiz;
            }
            if (atributos.Count == 1)//si no existe ningun atributo
            {
                //elAtributoSAlidoMayorNumero()
                //el mayor numero de valor de salida
                raiz = new Nodo(elAtributoSAlidoMayorNumero(tabla));
                return raiz;
            }
            int indiceClase = this.seleccionarAtributoMayorRatio(tabla);
            Columna clase = tabla.getColumna(indiceClase);

            int countAtributos = 0;

            if (clase.IsContinuo)
            {
                List<double> atributosClase1 = clase.getAtributosContinuos();
                raiz = new Nodo(clase.getClase(), atributosClase1); // el nodo viene a ser la "clase" y los atributos las ramas
                countAtributos = atributosClase1.Count + 1;

            }
            else
            {
                List<String> atributosClase2 = clase.getAtributosDiscretos();
                raiz = new Nodo(clase.getClase(), atributosClase2);
                countAtributos = atributosClase2.Count;
            }

            Tabla nuevaTabla = null;

            for (int i = 0; i < countAtributos; i++)
            {
                nuevaTabla = (Tabla)tabla.Clone();
                if (clase.IsContinuo)
                {
                    particionarTabla(nuevaTabla, indiceClase, i);

                }
                else
                    particionarTabla(nuevaTabla, indiceClase, clase.getAtributosDiscretos()[i]);

                if (nuevaTabla.getCountfilas() == 0)//ejemplos estan vacios
                {
                    raiz.agregarNodo(new Nodo(elAtributoSAlidoMayorNumero(tabla)));
                }
                else
                {
                    nuevaTabla.eliminarColumna(indiceClase);
                    raiz.agregarNodo(algoritmoC45(nuevaTabla, nuevaTabla.getClases()));
                }
            }
            return raiz;
        }

        public double informacionDivision(Columna columna) // split information
        {
            double divDeLaInformacion = 0.0;
            double probb = 0.0;
            int contadorAtributos1 = 0;
  
            if (columna.IsContinuo)
                contadorAtributos1 = columna.getAtributosContinuos().Count + 1;
            else
                contadorAtributos1 = columna.getAtributosDiscretos().Count;


            //Console.WriteLine("clase: "+columna.getClase());
            for ( int i = 0; i < contadorAtributos1; i++ ) {
                //Console.WriteLine("infoDiv = ("+atributos[i]+")"+ columna.getFrecuenciaAtributo(atributos[i])+" / "+columna.getTam());
                if(columna.IsContinuo)
                    probb = (double)((double)(columna.getFrecuenciaAtributo(i)) / (double)(columna.getTam()));
                else
                    probb = (double)((double)(columna.getFrecuenciaAtributo(columna.getAtributosDiscretos()[i])) 
                        / (double)(columna.getTam()));
                //Console.WriteLine("probb = "+probb);
                divDeLaInformacion -= (double)(probb*(Math.Log(probb,2.0)));
            }
            return divDeLaInformacion;
        }

        public double ratioDeGanancia(Tabla tabla, Columna columna) //GainRatio
        {
            double Ganancia = (double)this.gananciaClase(columna, tabla.getColumnaAtributoSalida());
            double DivInformacion = (double)this.informacionDivision(columna);

            //Console.WriteLine("El ratio de ganancia es = " + (double)((double)Ganancia / (double)DivInformacion));

            if(Ganancia >= promedioGanancia)
            {
                return Ganancia;
            }
            else
            {
                return (double)((double)Ganancia / (double)DivInformacion);
            }
        }

        public double[] ratioDeCadaClase(Tabla tabla)
        {
            double[] ratios = new double[tabla.getCountColumna()-1];

            for (int i = 0; i < tabla.getCountColumna() - 1; i++)
            {
                //Console.WriteLine("Para clase {0}", i);
                //Console.WriteLine("Ratio=" + this.ratioDeGanancia(tabla, tabla.getColumna(i)));
                ratios[i] = ((double)this.ratioDeGanancia(tabla, tabla.getColumna(i)));
            }
            return ratios;
        }

        public int seleccionarAtributoMayorRatio(Tabla tabla) // retorna el indice de la columna
        {
            double[] ratios = this.ratioDeCadaClase(tabla);

            return Array.IndexOf(ratios, ratios.Max());
        }

        public double promedioGanancias(Tabla tabla)
        {
            double gananciaTotal = 0;
            for(int i=0; i<tabla.getCountColumna(); i++)
            {
                gananciaTotal+= (double)this.gananciaClase(tabla.getColumna(i), tabla.getColumnaAtributoSalida());
            }

            return gananciaTotal/(tabla.getCountColumna()-1);
        }
    }
}
