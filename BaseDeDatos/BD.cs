using Npgsql;
using NpgsqlTypes;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace BaseDeDatos
{
    public class BD
    {
        private string host;
        private string port;
        private string usuario;
        private int tiempo_espera;
        private string password;
        private string base_de_datos;
        private NpgsqlConnection conexion;
        NpgsqlCommand cmd;

        public BD()
        {
            IEnumerable<string> lineas = File.ReadLines("_conf");
            string[] datos = new string[6];
            int contador = 0;

            foreach (string linea in lineas)
            {
                datos[contador] = linea;
                contador += 1;
            }

            this.host = datos[0];
            this.port = datos[1];
            this.usuario = datos[2];
            this.password = datos[3];
            this.base_de_datos = datos[4];
            this.tiempo_espera = Int32.Parse(datos[5]);
        }

        public BD(String host, String port, String usuario, String password, String baseDatos, int tiempo_espera)
        {
            this.host = host;
            this.port = port;
            this.usuario = usuario;
            this.password = password;
            this.base_de_datos = baseDatos;
            this.tiempo_espera = tiempo_espera;
        }

        public bool conectar()
        {
            string datos_conexion = "Host=" + host + ";Username=" + usuario + ";Password=" + password + ";Database=" + base_de_datos + ";CommandTimeout=" + tiempo_espera;

            conexion = new NpgsqlConnection(datos_conexion);
            conexion.Open();

            if (conexion.State == System.Data.ConnectionState.Open)
                return true;

            return false;
        }

        public bool cerrar()
        {
            if (conexion.State == System.Data.ConnectionState.Open)
            {
                conexion.Close();

                return true;
            }

            return false;
        }

        public void consulta(string sql)
        {
            cmd = new NpgsqlCommand(sql, conexion);
        }

        public void agregarParametro(int indice, int valor)
        {
            cmd.Parameters[indice].Value = valor;
        }

        public void agregarParametro(int indice, double valor)
        {
            cmd.Parameters[indice].Value = valor;
        }

        public void agregarParametro(int indice, string valor)
        {
            cmd.Parameters[indice].Value = valor;
        }

        public void agregarParametro(int indice, DateTime valor)
        {
            cmd.Parameters[indice].Value = valor.ToString("yyyy-MM-dd HH:mm:ss");
        }

        public void setParamInt(string parametro)
        {
            cmd.Parameters.Add(parametro, NpgsqlDbType.Integer);
        }

        public void setParamDouble(string parametro)
        {
            cmd.Parameters.Add(parametro, NpgsqlDbType.Double);
        }

        public void setParamString(string parametro)
        {
            cmd.Parameters.Add(parametro, NpgsqlDbType.Text);
        }

        public void setParamTimestamp(string parametro)
        {
            cmd.Parameters.Add(parametro, NpgsqlDbType.Timestamp);
        }

        public void prepare()
        {
            cmd.Prepare();
        }

        public void executeNonQuery()
        {
            cmd.ExecuteNonQuery();
        }

        public NpgsqlDataReader executeReader()
        {
            return cmd.ExecuteReader();
        }
    }
}
