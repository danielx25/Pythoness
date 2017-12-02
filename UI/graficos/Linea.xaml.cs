using System;
using System.Collections.Generic;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.ComponentModel;
using LiveCharts;
using LiveCharts.Wpf;
using LiveCharts.Configurations;

namespace UI.graficos
{
    /// <summary>
    /// Lógica de interacción para Linea.xaml
    /// </summary>
    public partial class Linea : UserControl, INotifyPropertyChanged
    {
        private int _axisXMax;
        private int _axisXMin;
        private int _axisYMax;
        private int _axisYMin;
        private string _labelAxisX;
        private string _labelAxisY;
        //private double _trend;

        public Linea()
        {
            InitializeComponent();

            var mapper = Mappers.Xy<Coordenadas>()
                .X(model => model.X)
                .Y(model => model.Y);

            //lets save the mapper globally.
            Charting.For<Coordenadas>(mapper);

            //the values property will store our values array
            ChartValues = new ChartValues<Coordenadas>();

            //lets set how to display the X Labels
            RegistrosFormatter = value => value.ToString();

            //AxisStep forces the distance between each separator in the X axis
            AxisXStep = 1;
            AxisYStep = 100;
            //AxisUnit forces lets the axis know that we are plotting seconds
            //this is not always necessary, but it can prevent wrong labeling
            AxisXUnit = 1;
            AxisYUnit = 1;

            //SetAxisXLimits(0, 10);
            //SetAxisYLimits(0, 10);

            //The next code simulates data changes every 300 ms
            DataContext = this;
        }

        public ChartValues<Coordenadas> ChartValues { get; set; }
        public Func<int, string> RegistrosFormatter { get; set; }
        public int AxisXStep { get; set; }
        public int AxisYStep { get; set; }
        public int AxisXUnit { get; set; }
        public int AxisYUnit { get; set; }

        public int AxisXMax
        {
            get { return _axisXMax; }
            set
            {
                _axisXMax = value;
                OnPropertyChanged("AxisXMax");
            }
        }
        public int AxisXMin
        {
            get { return _axisXMin; }
            set
            {
                _axisXMin = value;
                OnPropertyChanged("AxisXMin");
            }
        }

        public int AxisYMax
        {
            get { return _axisYMax; }
            set
            {
                _axisYMax = value;
                OnPropertyChanged("AxisYMax");
            }
        }

        public int AxisYMin
        {
            get { return _axisYMin; }
            set
            {
                _axisYMin = value;
                OnPropertyChanged("AxisYMin");
            }
        }

        public string LabelAxisX
        {
            get { return _labelAxisX; }
            set
            {
                _labelAxisX = value;
                OnPropertyChanged("LabelAxisX");
            }
        }

        public string LabelAxisY
        {
            get { return _labelAxisY; }
            set
            {
                _labelAxisY = value;
                OnPropertyChanged("LabelAxisY");
            }
        }

        public void SetAxisXLimits(int min, int max)
        {
            AxisXMax = max;
            AxisXMin = min;
        }

        public void SetAxisYLimits(int min, int max)
        {
            AxisYMax = max;
            AxisYMin = min;
        }

        /*private void InjectStopOnClick(object sender, RoutedEventArgs e)
        {
            IsReading = !IsReading;
            if (IsReading) Task.Factory.StartNew(Read);
        }*/

        #region INotifyPropertyChanged implementation

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName = null)
        {
            if (PropertyChanged != null)
                PropertyChanged.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion
    }
}
