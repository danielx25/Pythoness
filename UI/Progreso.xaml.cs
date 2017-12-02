using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace UI
{
    /// <summary>
    /// Lógica de interacción para Progreso.xaml
    /// </summary>
    public partial class Progreso : Window
    {
        protected BackgroundWorker worker = new BackgroundWorker();

        public Progreso()
        {
            InitializeComponent();

            worker = new BackgroundWorker();

            worker.RunWorkerCompleted += completado;
            worker.WorkerReportsProgress = true;
            worker.DoWork += doWork;
            worker.ProgressChanged += actualizar;
            this.Show();
        }

        protected void actualizar(object sender, ProgressChangedEventArgs e)
        {
            barraProgreso.Value = e.ProgressPercentage;
            lblProgreso.Content = (string)e.UserState;
        }

        protected virtual void completado(object sender, RunWorkerCompletedEventArgs e)
        {
            this.Close();
        }

        protected virtual void doWork(object sender, DoWorkEventArgs e)
        {

        }
    }
}
