using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ContourTracker01
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class Window1 : Window
    {
        private BussinessContour _bussinessContour;

        public Window1()
        {
            InitializeComponent();

            _bussinessContour = new BussinessContour();
            _bussinessContour.FollowingFinishHandle += new FollowingFinish(_bussinessContour_FollowingFinishHandle);
        }

        private void _openFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog openFileDialog = new OpenFileDialog();
                openFileDialog.InitialDirectory = @"..\..\" ;
                openFileDialog.Filter = "txt files (*.txt)|*.txt|dat files (*.dat)|*.dat|All files (*.*)|*.*";
                openFileDialog.RestoreDirectory = true;

                if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    _bussinessContour.SetFileName(openFileDialog.FileName);
                    _bussinessContour.BeginSeriesAction();          //这里就开始得到等值线的一系列操作
                }
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show(ex.Message);
            }
        }
        

        private void _editContourLevelButton_Click(object sender, RoutedEventArgs e)
        {
            int count = _canvas.Children.Count;
            _canvas.Children.RemoveRange(0, count);

            _bussinessContour.IsDefaultContourLevel = false;
            _bussinessContour.BeginSeriesAction();
        }

        private void _bussinessContour_FollowingFinishHandle()
        {
            Polyline polyLine;

            List<IsoPoint> isoPointList;
            for (int i = 0; i < _bussinessContour.AllIsoPointList.Count; i++)
            {
                polyLine = new Polyline();
                polyLine.Stroke = Brushes.Red;
                polyLine.StrokeThickness = 1;

                isoPointList = _bussinessContour.AllIsoPointList[i]._aIsoPointList;
                for (int j = 0; j < isoPointList.Count; j++)
                {
                    polyLine.Points.Add(new Point(isoPointList[j]._x, isoPointList[j]._y));
                }

                _canvas.Children.Add(polyLine);
            }

            //isoPointList = _bussinessContour.AllIsoPointList[0]._aIsoPointList;
            //double[] x = new double[25];
            //double[] y = new double[25];
            //for (int i = 0; i < 25; i++)
            //{
            //    x[i] = isoPointList[i]._x;
            //    y[i] = isoPointList[i]._y;
            //}
            //double[] u = new double[x.Length * 4 - 3];
            //double[] s = new double[u.Length];

            //int n = 0;
            //float interval = 0;
            //for (int i = 0; i < u.Length - 1; i++)
            //{
            //    n = i / 4;
            //    interval = (isoPointList[n + 1]._x - isoPointList[n]._x) / 4;
            //    u[i] = isoPointList[n]._x + i % 4 * interval;
            //}
            //u[u.Length - 1] = isoPointList[25 - 1]._x;

            //BussinessContour.SPL(x.Length - 1, s.Length - 1, x, y, 0, 0, u, s);

            //polyLine = new Polyline();
            //polyLine.Stroke = Brushes.Blue;

            //for (int i = 0; i < u.Length; i++)
            //{
            //    polyLine.Points.Add(new Point(u[i], s[i]));
            //}

            //_canvas.Children.Add(polyLine);

            _editContourLevelButton.IsEnabled = true;
        }
    }
}
