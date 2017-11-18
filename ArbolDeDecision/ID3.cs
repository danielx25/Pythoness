using ArbolDeDecision;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArbolDeDecision
{
    public class ID3_
    {
        protected Tabla tabla = null;
        protected Arbol_ arbol;
        public void cargarTabla(Tabla tabla)
        {
            this.tabla = tabla;
            arbol = new Arbol_("ID3");
        }

        public Arbol_ Arbol
        {
            get
            {
                return arbol;
            }
        }
        

        public void iniciarID3()
        {
            tabla.ToString();
            //inicio cronometro
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Restart();

            arbol.setRaiz(algoritmoID3(tabla, tabla.getClases()));
            System.Console.WriteLine(arbol);
            arbol.guardarArbol("arbolID3.txt");
            //Nodo s=algoritmoID3(this.tabla, tabla.getClases());
            //System.Console.WriteLine(s.getNombreClase());

            // termino cronometro + resultados ID3
            stopwatch.Stop();
            TimeSpan tiempoID3 = stopwatch.Elapsed;
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
            tiempoID3.Hours, tiempoID3.Minutes, tiempoID3.Seconds,
            tiempoID3.Milliseconds / 10);
            string elapsedMilisecons = String.Format(" {0} ",tiempoID3.Milliseconds);
            Console.WriteLine("RunTime: " + elapsedTime);
            Console.WriteLine("Runtime: " + elapsedMilisecons + " miliseconds");
            arbol.Tiempo = tiempoID3.Milliseconds;
        }
        
        public Nodo algoritmoID3(Tabla tabla, List<String> atributos)
        {
            System.Console.WriteLine();
            tabla.ToString();
            System.Console.WriteLine();
            Nodo raiz = null;

            int indice = siTodosEjemplosSonLosMismos(tabla);
            if(indice != -1)
            {
                Columna columna = tabla.getColumnaAtributoSalida();
                String aSalida = (String) columna[0];
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
            int indiceClase = seleccionarAtributoConMayorGanancia(tabla, atributos, raiz);
            Columna clase = tabla.getColumna(indiceClase);
            System.Console.WriteLine("Clase: " +clase.getClase());
            int countAtributos = 0;
            
            if (clase.IsContinuo)
            {
                List<double> atributosClase1 = clase.getAtributosContinuos();
                raiz = new Nodo(clase.getClase(), atributosClase1); // el nodo viene a ser la "clase" y los atributos las ramas
                countAtributos = atributosClase1.Count+1;
                
            }
            else
            {
                List<String> atributosClase2 = clase.getAtributosDiscretos();
                raiz = new Nodo(clase.getClase(), atributosClase2);
                countAtributos = atributosClase2.Count;
            }
            

            Tabla nuevaTabla = null;

            for (int i=0; i<countAtributos; i++)
            {
                //System.Console.WriteLine(clase.getAtributosDiscretos()[i]);
                nuevaTabla = (Tabla)tabla.Clone();
                if (clase.IsContinuo)
                {
                    particionarTabla(nuevaTabla, indiceClase, i);
                    
                }
                else
                    particionarTabla(nuevaTabla, indiceClase, clase.getAtributosDiscretos()[i]);
                nuevaTabla.ToString();
                if (nuevaTabla.getCountfilas() ==0)//ejemplos estan vacios
                {
                    raiz.agregarNodo(new Nodo(elAtributoSAlidoMayorNumero(tabla)));
                }
                else
                { 
                    nuevaTabla.eliminarColumna(indiceClase);
                    raiz.agregarNodo(algoritmoID3(nuevaTabla, nuevaTabla.getClases()));
                }
            }
            return raiz;
        }

        public int siTodosEjemplosSonLosMismos(Tabla tabla)
        {
            Columna columna = tabla.getColumnaAtributoSalida();
            int frecuencia = 0;
            if(columna.IsContinuo)
            {
                for(int i=0; i<columna.getAtributosContinuos().Count+1;i++)
                {
                    frecuencia = columna.getFrecuenciaAtributo(i);
                    if (frecuencia == columna.getTam())
                        return i;

                    if (frecuencia > 0)
                        return -1;
                }
                
            }
            else
            {
                for (int i = 1; i < columna.getAtributosDiscretos().Count; i++)
                {
                    frecuencia = columna.getFrecuenciaAtributo(columna.getAtributosDiscretos()[i]);
                    if (frecuencia == columna.getTam())
                        return i;

                    if (frecuencia > 0)
                        return -1;
                }
            }

            return -1;
        }

        public string elAtributoSAlidoMayorNumero(Tabla tabla)
        {
            Columna columna = tabla.getColumnaAtributoSalida();
            List<String> atributos = columna.getAtributosDiscretos();
            int[] contadorAtributos = new int[atributos.Count];
            //atributo = (String)columna[0];


            int frecuencia = 0;
            if (columna.IsContinuo)
            {
                for (int i = 0; i < columna.getAtributosContinuos().Count + 1; i++)
                {
                    contadorAtributos[i]= columna.getFrecuenciaAtributo(i);
                }

            }
            else
            {
                for (int i = 0; i < columna.getTam(); i++)
                {
                    String atributoC = (String)columna[i];
                    for (int j = 0; j < atributos.Count; j++)
                    {
                        if (String.Equals(atributoC, atributos[j], StringComparison.Ordinal))
                            contadorAtributos[j] += 1;
                    }
                }
            }

            int indice = Array.IndexOf(contadorAtributos, contadorAtributos.Max());

            return atributos[indice];
        }

        public int seleccionarAtributoConMayorGanancia(Tabla tabla, List<String> atributos, Nodo nodo)
        {
            double[] ganaciasClases = new double[tabla.getCountColumna() - 1];

            for(int i=0; i<tabla.getCountColumna()-1; i++)
            {
                ganaciasClases[i] = gananciaClase(tabla.getColumna(i), tabla.getColumnaAtributoSalida());
                //System.Console.WriteLine("ganancia: "+ganaciasClases[i]);
            }
            int indice = Array.IndexOf(ganaciasClases, ganaciasClases.Max());
            //nodo.setGanancia(ganaciasClases.Max());
            return indice;
        }

        public double gananciaClase(Columna clase, Columna atributoObjetivo)
        {
            double resultado = 0.0;
            //List<String> atributos = clase.getAtributosDiscretos();
            double[] entropiaAtributos =null;
            double entropiaGeneral = this.entropiaGeneral(atributoObjetivo);

            if(clase.IsContinuo)
            {
                entropiaAtributos = new double[clase.getCountAtributos()+1];
                for (int i = 0; i < clase.getCountAtributos() + 1; i++)
                {
                    entropiaAtributos[i] = entropiaAtributo(clase, atributoObjetivo, i);
                    resultado += -((double)clase.getFrecuenciaAtributo(i) / clase.getTam()) * entropiaAtributos[i];
                }
            }
            else
            {
                entropiaAtributos = new double[clase.getCountAtributos()];
                for (int i = 0; i < clase.getCountAtributos(); i++)
                {
                    entropiaAtributos[i] = entropiaAtributo(clase, atributoObjetivo, i);
                    resultado += -((double)clase.getFrecuenciaAtributo(clase.getAtributosDiscretos()[i]) /
                        clase.getTam()) * entropiaAtributos[i];
                }
            }
                

            //System.Console.WriteLine();
            resultado += entropiaGeneral;
            return resultado;
        }

        public double entropiaGeneral(Columna atributoObjetivo)
        {
            int[] contadorAtributos = null;

            if (atributoObjetivo.IsContinuo)
            {
                contadorAtributos = new int[atributoObjetivo.getAtributosContinuos().Count + 1];
                for (int i = 0; i < atributoObjetivo.getAtributosContinuos().Count + 1; i++)
                {
                    contadorAtributos[i] = atributoObjetivo.getFrecuenciaAtributo(i);
                }

            }
            else {
                contadorAtributos = new int[atributoObjetivo.getAtributosDiscretos().Count];
                for (int i = 0; i < atributoObjetivo.getAtributosDiscretos().Count; i++)
                {
                    contadorAtributos[i] = atributoObjetivo.getFrecuenciaAtributo(atributoObjetivo.getAtributosDiscretos()[i]);
                }
            }
                

            double resultado = 0.0;

            for (int i = 0; i < contadorAtributos.Length; i++)
            {
                
                double division = (double)contadorAtributos[i] / atributoObjetivo.getTam();
                if (division>0)
                resultado +=-division* Math.Log(division, 2.0);
            }
            return resultado;
        }

        public double entropiaAtributo(Columna clase, Columna atributoObjetivo, int indiceAtributo)
        {
            //Double.PositiveInfinity;
            List<String> atributos = atributoObjetivo.getAtributosDiscretos();
            int[] contadorAtributos = null;

            if(clase.IsContinuo)
            {
                contadorAtributos = contadorAtributosContinuos(clase, atributoObjetivo, indiceAtributo);
            }
            else
            {
                contadorAtributos = contadorAtributosDiscretos(clase, atributoObjetivo, indiceAtributo);
            }
            

            double resultado = 0.0;
            int total = contadorAtributos.Sum();
            for (int i = 0; i < contadorAtributos.Length; i++)
            {

                double division = (contadorAtributos[i] / (double)total);
                if(division>0)
                resultado+=(-division) * (Math.Log(division)/Math.Log(2.0));
            }
            return resultado;
        }

        public int [] contadorAtributosDiscretos(Columna clase, Columna atributoObjetivo, int indiceAtributo)
        {
            int[] contador_atributos = null;

            if (atributoObjetivo.IsContinuo)
            {
                

                List<String> atributos = atributoObjetivo.getAtributosDiscretos();
                contador_atributos = new int[atributoObjetivo.getAtributosContinuos().Count+1];
                for (int i = 0; i < atributoObjetivo.getTam(); i++)
                {
                    double atributoS = System.Convert.ToDouble(atributoObjetivo[i]); 
                     String atributoC = (String)clase[i];

                    for (int j = 0; j < atributoObjetivo.getAtributosContinuos().Count + 1; j++)
                    {
                        double limitInferior = -1 * Double.PositiveInfinity;
                        double limitSuperior = Double.PositiveInfinity;
                        if (j > 0)
                            limitInferior = atributoObjetivo.getAtributosContinuos()[j - 1];
                        if (j < atributoObjetivo.getAtributosContinuos().Count)
                            limitSuperior = atributoObjetivo.getAtributosContinuos()[j];

                        if ((atributoS >= limitInferior && atributoS < limitSuperior) && String.Equals(atributoC,
                            clase.getAtributosDiscretos()[j], StringComparison.Ordinal))
                        {
                            contador_atributos[j] += 1;
                            break;
                        }

                    }
                }
            }
            else
            {
                List<String> atributos = atributoObjetivo.getAtributosDiscretos();
                 contador_atributos = new int[atributos.Count];
                for (int i = 0; i < atributoObjetivo.getTam(); i++)
                {
                    String atributoS = (String)atributoObjetivo[i];
                    String atributoC = (String)clase[i];

                    for (int j = 0; j < atributos.Count; j++)
                    {
                        if (String.Equals(atributoS, atributos[j], StringComparison.Ordinal) && String.Equals(atributoC,
                            clase.getAtributosDiscretos()[indiceAtributo], StringComparison.Ordinal))
                        {
                            contador_atributos[j] += 1;
                            break;
                        }

                    }
                }
            }

            
            return contador_atributos;
        }

        public int[] contadorAtributosContinuos(Columna clase, Columna atributoObjetivo, int indiceAtributo)
        {
           
            int[] contador_atributos = null;

            if(atributoObjetivo.IsContinuo)
            {
                contador_atributos = new int[atributoObjetivo.getAtributosContinuos().Count+1];

                double limitInferior = -1 * Double.PositiveInfinity;
                double limitSuperior = Double.PositiveInfinity;
                if (indiceAtributo > 0)
                    limitInferior = clase.getAtributosContinuos()[indiceAtributo - 1];
                if (indiceAtributo < clase.getAtributosContinuos().Count)
                    limitSuperior = clase.getAtributosContinuos()[indiceAtributo];

                for (int i = 0; i < atributoObjetivo.getTam(); i++)
                {
                    double atributoS = System.Convert.ToDouble(atributoObjetivo[i]);
                    double atributoC = System.Convert.ToDouble(clase[i]);

                    

                    for (int j = 0; j < atributoObjetivo.getAtributosContinuos().Count+1; j++)
                    {
                        double limitInferior1 = -1 * Double.PositiveInfinity;
                        double limitSuperior1 = Double.PositiveInfinity;
                        if (j > 0)
                            limitInferior1 = atributoObjetivo.getAtributosContinuos()[j - 1];
                        if (j < atributoObjetivo.getAtributosContinuos().Count)
                            limitSuperior1 = atributoObjetivo.getAtributosContinuos()[j];

                        if ((atributoC >= limitInferior && atributoC < limitSuperior) &&
                            (atributoS >= limitInferior1 && atributoS < limitSuperior1))
                        {
                            contador_atributos[j] += 1;
                            break;
                        }

                    }
                }
            }
            else
            {
                List<String> atributos = atributoObjetivo.getAtributosDiscretos();
                contador_atributos = new int[atributos.Count];

                double limitInferior = -1 * Double.PositiveInfinity;
                double limitSuperior = Double.PositiveInfinity;
                if (indiceAtributo > 0)
                    limitInferior = clase.getAtributosContinuos()[indiceAtributo - 1];
                if (indiceAtributo < clase.getAtributosContinuos().Count)
                    limitSuperior = clase.getAtributosContinuos()[indiceAtributo];

                for (int i = 0; i < atributoObjetivo.getTam(); i++)
                {
                    String atributoS = (String)atributoObjetivo[i];
                    double atributoC = System.Convert.ToDouble(clase[i]);

                    for (int j = 0; j < atributos.Count; j++)
                    {
                        if ((atributoC >= limitInferior && atributoC < limitSuperior) &&
                            String.Equals(atributoS, atributos[j], StringComparison.Ordinal))
                        {
                            contador_atributos[j] += 1;
                            break;
                        }

                    }
                }
            }

            
            
            return contador_atributos;
        }


        public void particionarTabla(Tabla tabla, int indiceClase, String atributo)
        {
            Columna clase = tabla.getColumna(indiceClase);

            for (int i = 0; i < clase.getTam(); i++)
            {
                String cadena = (String)clase[i];
                if (cadena.Equals(atributo) == false)
                {
                    tabla.eliminarFilas(i);
                    i -= 1;
                }
            }
        }

        public void particionarTabla(Tabla tabla, int indiceClase, int indexAtributo)
        {
            System.Console.WriteLine("indice: " + indexAtributo);
            Columna clase = tabla.getColumna(indiceClase);
            double limitInferior = -1 * Double.PositiveInfinity;
            double limitSuperior = Double.PositiveInfinity;
            if (indexAtributo > 0)
                limitInferior = clase.getAtributosContinuos()[indexAtributo - 1];
            if (indexAtributo < clase.getAtributosContinuos().Count)
                limitSuperior = clase.getAtributosContinuos()[indexAtributo];
            double atributoC;
            System.Console.WriteLine("inferior: "+limitInferior);
            System.Console.WriteLine("superior: " + limitSuperior);
            for (int i = 0; i < clase.getTam(); i++)
            {
                atributoC = System.Convert.ToDouble(clase[i]);
                System.Console.WriteLine("aceptable: " + atributoC);
                if (atributoC >= limitInferior && atributoC < limitSuperior)
                {
                    
                    tabla.eliminarFilas(i);
                    i -= 1;
                }
                    
            }
        }

    }
}
