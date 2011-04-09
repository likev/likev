using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ContourTracker01
{
    public class BussinessContour
    {
        private const int NOfContourLevel = 10;
        private const float Excursion = 0.001f;     //修正值

        private AccessContour _accessContour;
        private bool _isSetDefaultContourLevel = true;  //是否设置成为默认的等值线等级，默认为10等分
                                                        //等值线表－－就是要求的等值线的集合

        //每条边上的信息（有无等值点，有时点在何处（_rate）
        struct EdgeIsoInfo         
        {
            public float _rate;
            public bool _isIsoPoint;   //在此边上是否有等值点
        }

        private EdgeIsoInfo[,] _xSide;
        private EdgeIsoInfo[,] _ySide;

        private float _deltX;
        private float _deltY;

        private string _preString;      //先前的文件名，来决定是否再次读取数据

        private float _curFollowingValue;       //当前正在追踪的等值线值
        private IsoPoint _preIsoPoint;
        private IsoPoint _curIsoPoint;
        private IsoPoint _nextIsoPoint;

        public struct IsoPointListInfo     //等值线的信息
        {
            public List<IsoPoint> _aIsoPointList;
            public float _value;     //指示当前等值线的值
        }

        private IsoPointListInfo _isoPointListInfo;    //当前等值线
        private List<IsoPointListInfo> _allIsoPointList;                //所有等值线链表

        public event FollowingFinish FollowingFinishHandle;

        public BussinessContour()
        {
            _accessContour = new AccessContour();
        }

        //一系列得到等值线操作的启动器
        public void BeginSeriesAction()
        {
            _allIsoPointList = new List<IsoPointListInfo>();

            if(_preString!=_accessContour.FileName)
                _accessContour.GetGridData();

            if (_isSetDefaultContourLevel)
                SetDefaultContourLevel();
            else
                SetContourLevel();      //用户修改

            _deltX = (_accessContour.GridInfo._xMax - _accessContour.GridInfo._xMin) / (_accessContour.GridInfo._columns - 1);
            _deltY = (_accessContour.GridInfo._yMax - _accessContour.GridInfo._yMin) / (_accessContour.GridInfo._rows - 1);

            AllocateMemory();       //分配边信息内存

            for (int i = 0; i < NOfContourLevel; i++)
            {
                _curFollowingValue = _accessContour.ContourLevel[i];

                InterpolateTracingValue(); //扫描并计算纵、横边上等值点的情况

                TracingNonClosedContour();  //追踪开等值线

                TrackingClosedContour();    //追踪封闭等值线
            }

            FollowingFinishHandle();
        }

        private void AllocateMemory()
        {
            _xSide = new EdgeIsoInfo[_accessContour.GridInfo._rows, _accessContour.GridInfo._columns - 1];
            _ySide = new EdgeIsoInfo[_accessContour.GridInfo._rows - 1, _accessContour.GridInfo._columns];
        }

        //扫描并计算横、纵边上等值点的情况（得到_xSide, _ySide的值）
        private void InterpolateTracingValue()
        {
            /*      网格点标识如下:
        
            (i+1,j)·--------·(i+1,j+1)
                    |        |
                    |        |
                    ·       |
	                |        |
	         (i,j) ·--------·(i,j+1)

              i:表示行号(向上增加)
			  j:表示列号(向右增加)
			  标识一个网格交点时，行号在前，列号在右，如：(i,j)
            */

            /*
             * 其中对水平方向h0--(i, j)   h1--(i, j+1)  _xSide, _ySide中的_rate为(value-h0)/(h1-h0)
             */
            if (_xSide == null || _ySide == null)
                throw new Exception("分配内存错误！");

            int i = 0;
            int j = 0;
            float h0, h1;       //计录一条边上的两个值
            float flag;        //中间值

            GridPoint[] gridPoints = _accessContour.GridPoints;

            int rows = _accessContour.GridInfo._rows;               //网格的行列数
            int columns = _accessContour.GridInfo._columns;         //这里增加这两个变量，仅仅是为了减少程序的中转
                                                                    //增加效率

            int edgeRows= _accessContour.GridInfo._rows;              //这里的行列数是根据横，纵边来定的
            int edgeColumns = _accessContour.GridInfo._columns - 1;     //这里先计算的是横向的

            //扫描每一条边
            for (i = 0; i < edgeRows; i++)
            {
                for (j = 0; j < edgeColumns; j++)
                {
                    //x边的两端点
                    h0 = gridPoints[i * columns + j]._z;
                    h1 = gridPoints[i * columns + j + 1]._z;

                    if (Math.Abs(h0 - h1) < AccessContour.Epsilon)
                    {
                        _xSide[i, j]._rate = -2.0f;
                        _xSide[i, j]._isIsoPoint = false;
                    }
                    else
                    {
                        flag = (_curFollowingValue - h0) * (_curFollowingValue - h1);

                        if (flag > 0) //同时大于或小于两端点
                        {
                            _xSide[i, j]._rate = -2.0f;
                            _xSide[i, j]._isIsoPoint = false;
                        }
                        else if (flag < 0) //在两点之间
                        {
                            _xSide[i, j]._rate = (_curFollowingValue - h0) / (h1 - h0);
                            _xSide[i, j]._isIsoPoint = true;
                        }
                        else //与其中一个相等
                        {
                            //修正
                            if (Math.Abs(_curFollowingValue - h0) < AccessContour.Epsilon )
                                h0 += Excursion;
                            else
                                h1 += Excursion;

                            _xSide[i, j]._rate = (_curFollowingValue - h0) / (h1 - h0);

                            if (_xSide[i, j]._rate < 0 || _xSide[i, j]._rate > 1)
                                _xSide[i, j]._isIsoPoint = false;
                            else
                                _xSide[i, j]._isIsoPoint = true;
                        }
                    }
                }
            }

            edgeRows = _accessContour.GridInfo._rows - 1;
            edgeColumns = _accessContour.GridInfo._columns;               //再计算纵向的

            for (i = 0; i < edgeRows; i++)
            {
                for (j = 0; j < edgeColumns; j++)
                {
                    h0 = gridPoints[i * columns + j]._z;
                    h1 = gridPoints[(i + 1) * columns + j]._z;

                    if (Math.Abs(h0 - h1) < AccessContour.Epsilon)
                    {
                        _ySide[i, j]._rate = -2.0f;
                        _ySide[i, j]._isIsoPoint = false;
                    }
                    else
                    {
                        flag = (_curFollowingValue - h0) * (_curFollowingValue - h1);

                        if (flag > 0)
                        {
                            _ySide[i, j]._rate = -2.0f;
                            _ySide[i, j]._isIsoPoint = false;
                        }
                        else if (flag < 0)
                        {
                            _ySide[i, j]._rate = (_curFollowingValue - h0) / (h1 - h0);
                            _ySide[i, j]._isIsoPoint = true;
                        }
                        else
                        {
                            if (Math.Abs(_curFollowingValue - h0) < AccessContour.Epsilon)
                                h0 += Excursion;
                            else
                                h1 += Excursion;

                            _ySide[i, j]._rate = (_curFollowingValue - h0) / (h1 - h0);

                            if (_ySide[i, j]._rate < 0 || _ySide[i, j]._rate > 1)
                                _ySide[i, j]._isIsoPoint = false;
                            else
                                _ySide[i, j]._isIsoPoint = true;
                        }
                    }
                }
            }
        }

        //追踪开等值线
        private void TracingNonClosedContour()
        {
            /*
             * 这里的内存布局可以认为是     ^   |-------------|
             * 在竖直方向向上递增           |   |      |      |
             * 在水平方向向右递增           |   |-------------|
             *                              |   |      |      |
             *                              |   |-------------|
             *                              |-------------------->
             *由于在追踪时的方向不同，就要分成不同的情况
             */
            int edgeRows = _accessContour.GridInfo._rows - 1;
            int edgeColumns = _accessContour.GridInfo._columns - 1;
            
            //约定俗成i表示行，j表示列
            

            //追踪左边框
            for (int i = 0; i < edgeRows; i++)
            {
                if (_ySide[i, 0]._isIsoPoint)
                {
                    _preIsoPoint._row = i;
                    _preIsoPoint._column = -1;
                    _preIsoPoint._isHorizon = false;
                    _curIsoPoint._row = i;
                    _curIsoPoint._column = 0;
                    _curIsoPoint._isHorizon = false;

                    TracingOneNonClosedContour();
                }
            }

            //追踪上边框
            for (int j = 0; j < edgeColumns; j++)
            {
                if (_xSide[edgeRows, j]._isIsoPoint)
                {
                    _preIsoPoint._row = edgeRows;
                    _preIsoPoint._column = j;
                    _preIsoPoint._isHorizon = true;
                    _curIsoPoint._row = edgeRows;
                    _curIsoPoint._column = j;
                    _curIsoPoint._isHorizon = true;

                    TracingOneNonClosedContour();
                }
            }

            //追踪右边框
            for (int i = 0; i < edgeRows; i++)
            {
                if (_ySide[i, edgeColumns]._isIsoPoint)
                {
                    _preIsoPoint._row = i;
                    _preIsoPoint._column = edgeColumns;
                    _preIsoPoint._isHorizon = false;
                    _curIsoPoint._row = i;
                    _curIsoPoint._column = edgeColumns;
                    _curIsoPoint._isHorizon = false;

                    TracingOneNonClosedContour();
                }
            }

            //追踪底边框
            for (int j = 0; j < edgeColumns; j++)
            {
                if (_xSide[0, j]._isIsoPoint)
                {
                    _preIsoPoint._row = -1;
                    _preIsoPoint._column = j;
                    _preIsoPoint._isHorizon = true;
                    _curIsoPoint._row = 0;
                    _curIsoPoint._column = j;
                    _curIsoPoint._isHorizon = true;

                    TracingOneNonClosedContour();
                }
            }
        }

        //追踪一条开等值线
        //这个函数要完成一条等值线追踪的所有操作
        private void TracingOneNonClosedContour()
        {
            int rows = _accessContour.GridInfo._rows;       //这里是网格点的行列数
            int columns = _accessContour.GridInfo._columns;

            _isoPointListInfo = new IsoPointListInfo();
            List<IsoPoint> isoPointList = new List<IsoPoint>();
            _isoPointListInfo._aIsoPointList = isoPointList;
            _isoPointListInfo._value = _curFollowingValue;

            CalcCoord(_curIsoPoint._row, _curIsoPoint._column, _curIsoPoint._isHorizon);

            if (_curIsoPoint._isHorizon)
                _xSide[_curIsoPoint._row, _curIsoPoint._column]._isIsoPoint = false;
            else
                _ySide[_curIsoPoint._row, _curIsoPoint._column]._isIsoPoint = false;

            bool isFinish = false;

            while (!isFinish)
            {
                TracingNextPoint();

                _preIsoPoint = _curIsoPoint;
                _curIsoPoint = _nextIsoPoint;

                isFinish = (_curIsoPoint._row == 0 && _curIsoPoint._isHorizon) || (_curIsoPoint._column == 0 && !_curIsoPoint._isHorizon)
                || (_curIsoPoint._row == rows - 1) || (_curIsoPoint._column == columns - 1);
            }

            _allIsoPointList.Add(_isoPointListInfo);
        }

        //追踪封闭等值线
        //沿着x方向从右至左追踪()
        private void TrackingClosedContour()
        {
            int rows = _accessContour.GridInfo._rows - 1;
            int columns = _accessContour.GridInfo._columns - 1;

            int i = 0;
            int j = 0;

            for (j = 1; j < columns; j++)
            {
                for (i = 0; i < rows; i++)
                {
                    if (_ySide[i, j]._isIsoPoint)
                    {
                        _preIsoPoint._row = i;
                        _preIsoPoint._column = 0;
                        _preIsoPoint._isHorizon = false;
                        _curIsoPoint._row = i;
                        _curIsoPoint._column = j;
                        _curIsoPoint._isHorizon = false;

                        TracingOneClosedContour();
                    }
                }
            }
        }

        //追踪一条封闭的等值线
        private void TracingOneClosedContour()
        {
            int rows = _accessContour.GridInfo._rows;       //这里是网格点的行列数
            int columns = _accessContour.GridInfo._columns;

            int startI = _curIsoPoint._row;
            int startJ = _curIsoPoint._column;

            _isoPointListInfo = new IsoPointListInfo();
            List<IsoPoint> isoPointList = new List<IsoPoint>();
            _isoPointListInfo._aIsoPointList = isoPointList;
            _isoPointListInfo._value = _curFollowingValue;

            CalcCoord(_curIsoPoint._row, _curIsoPoint._column, false);

            bool isClosed = false;

            while (!isClosed)
            {
                TracingNextPoint();

                _preIsoPoint = _curIsoPoint;
                _curIsoPoint = _nextIsoPoint;

                isClosed = (_curIsoPoint._row == startI) && (_curIsoPoint._column == startJ) && (false == _curIsoPoint._isHorizon);
            }

            _allIsoPointList.Add(_isoPointListInfo);
        }


        //追踪下一点
        private void TracingNextPoint()
        {
            //判断从网格哪边进入
            if (_curIsoPoint._row > _preIsoPoint._row)
            {
                TracingFromBottom2Top();
                return;
            }
            else if (_curIsoPoint._column > _preIsoPoint._column)
            {
                TracingFromLeft2Right();
                return;
            }
            else if (_curIsoPoint._isHorizon)
            {
                TracingFromTop2Bottom();
                return;
            }
            else
            {
                TracingFromRight2Left();
                return;
            }
        }

        //自下向上追踪函数
        private void TracingFromBottom2Top()
        {
            int row = _curIsoPoint._row;
            int column = _curIsoPoint._column;

            if (_ySide[row, column]._isIsoPoint)
            {
                if (_xSide[row + 1, column]._isIsoPoint)
                {
                    if (_ySide[row, column]._rate < _ySide[row, column + 1]._rate)
                    {
                        HandlingAfterNextPointFound(row, column, false);
                        return;
                    }
                    else if (_ySide[row, column]._rate > _ySide[row, column + 1]._rate)
                    {
                        HandlingAfterNextPointFound(row, column + 1, false);
                        return;
                    }
                    else
                    {
                        if (_ySide[row + 1, column]._rate < 0.5f)
                        {
                            HandlingAfterNextPointFound(row, column, false);
                            return;
                        }
                        else
                        {
                            HandlingAfterNextPointFound(row, column + 1, false);
                            return;
                        }
                    }
                }
                else
                {
                    HandlingAfterNextPointFound(row, column, false);
                    return;
                }
            }
            else if (_xSide[row + 1, column]._isIsoPoint)
            {
                HandlingAfterNextPointFound(row + 1, column, true);
                return;
            }
            else
                HandlingAfterNextPointFound(row, column + 1, false);
        }

        //自左向右追踪函数
        private void TracingFromLeft2Right()
        {
            int row = _curIsoPoint._row;
            int column = _curIsoPoint._column;

            if (_xSide[row + 1, column]._isIsoPoint)
            {
                if (_ySide[row, column + 1]._isIsoPoint)
                {
                    float b = _xSide[row + 1, column]._rate - _xSide[row, column]._rate;
                    if (b<0) //斜向上
                    {
                        HandlingAfterNextPointFound(row + 1, column, true);
                        return;
                    }
                    else if (b>0) //斜向下
                    {
                        HandlingAfterNextPointFound(row, column, true);
                        return;
                    }
                    else //
                    {
                        if (_xSide[row, column + 1]._rate < 0.5f)
                        {
                            HandlingAfterNextPointFound(row + 1, column, true);
                            return;
                        }
                        else
                        {
                            HandlingAfterNextPointFound(row, column, true);
                            return;
                        }
                    }
                }
                else
                {
                    HandlingAfterNextPointFound(row + 1, column, true);
                    return;
                }
            }
            else if (_ySide[row, column + 1]._isIsoPoint)
            {
                HandlingAfterNextPointFound(row, column + 1, false);
                return;
            }
            else
            {
                HandlingAfterNextPointFound(row, column, true);
                return;
            }
        }
        
        //自上向下追踪函数
        private void TracingFromTop2Bottom()
        {
            int row = _curIsoPoint._row;
            int column = _curIsoPoint._column;

            if (_ySide[row - 1, column + 1]._isIsoPoint)
            {
                if (_xSide[row - 1, column]._isIsoPoint)
                {
                    if (_ySide[row - 1, column]._rate < _ySide[row - 1, column + 1]._rate)      //这里要注意与由上到下的不同的处理
                    {
                        HandlingAfterNextPointFound(row - 1, column + 1, false);
                        return;
                    }
                    else if (_ySide[row - 1, column]._rate > _ySide[row - 1, column + 1]._rate)
                    {
                        HandlingAfterNextPointFound(row - 1, column, false);
                        return;
                    }
                    else
                    {
                        if (_xSide[row - 1, column]._rate < 0.5f)
                        {
                            HandlingAfterNextPointFound(row - 1, column, false);
                            return;
                        }
                        else
                        {
                            HandlingAfterNextPointFound(row - 1, column + 1, false);
                            return;
                        }
                    }

                }
                else
                {
                    HandlingAfterNextPointFound(row - 1, column + 1, false);
                    return;
                }
            }
            else if (_xSide[row - 1, column]._isIsoPoint)
            {
                HandlingAfterNextPointFound(row - 1, column, true);
                return;
            }
            else
            {
                HandlingAfterNextPointFound(row - 1, column, false);
                return;
            }
        }

        //自右向左追踪函数
        private void TracingFromRight2Left()
        {
            int row = _curIsoPoint._row;
            int column = _curIsoPoint._column;

            if (_xSide[row, column - 1]._isIsoPoint)
            {
                if (_ySide[row, column - 1]._isIsoPoint)
                {
                    if (_xSide[row, column - 1]._rate < _xSide[row + 1, column - 1]._rate)
                    {
                        HandlingAfterNextPointFound(row + 1, column - 1, true);
                        return;
                    }
                    else if (_xSide[row, column - 1]._rate > _xSide[row + 1, column - 1]._rate)
                    {
                        HandlingAfterNextPointFound(row, column - 1, true);
                        return;
                    }
                    else
                    {
                        if (_ySide[row, column - 1]._rate < 0.5f)
                        {
                            HandlingAfterNextPointFound(row, column - 1, true);
                            return;
                        }
                        else
                        {
                            HandlingAfterNextPointFound(row + 1, column - 1, true);
                            return;
                        }
                    }
                }
                else
                {
                    HandlingAfterNextPointFound(row, column - 1, true);
                    return;
                }
            }
            else if (_ySide[row, column - 1]._isIsoPoint)
            {
                HandlingAfterNextPointFound(row, column - 1, false);
                return;
            }
            else
            {
                HandlingAfterNextPointFound(row + 1, column - 1, true);
                return;
            }
        }

        private void HandlingAfterNextPointFound(int row, int column, bool isHorizon)
        {
            _nextIsoPoint._row = row;
            _nextIsoPoint._column = column;
            _nextIsoPoint._isHorizon = isHorizon;

            CalcCoord(row, column, isHorizon);

            if (isHorizon)
                _xSide[row, column]._isIsoPoint = false;
            else
                _ySide[row, column]._isIsoPoint = false;
        }

        //计算某点坐标
        private void CalcCoord(int row, int column, bool isHorizon)
        {
            IsoPoint isoPoint = new IsoPoint();
            isoPoint._column = column;
            isoPoint._row = row;
            isoPoint._isHorizon = isHorizon;

            if (isHorizon)
            {
                isoPoint._x = _accessContour.GridInfo._xMin + (column + _xSide[row, column]._rate) * _deltX;
                isoPoint._y = _accessContour.GridInfo._yMin + row * _deltY;
            }
            else
            {
                isoPoint._x = _accessContour.GridInfo._xMin + column * _deltX;
                isoPoint._y = _accessContour.GridInfo._yMin + (row + _ySide[row, column]._rate) * _deltY;
            }

            _isoPointListInfo._aIsoPointList.Add(isoPoint);
        }

        //用户修改等值线等级表
        private void SetContourLevel()
        {
            for (int i = 0; i < 9; i++)
                _accessContour.ContourLevel[i] = i * 10 + 20;
        }

        //默认的等值线（10等分）
        private void SetDefaultContourLevel()
        {
            _accessContour.ContourLevel = new float[NOfContourLevel];

            for (int i = 0; i < NOfContourLevel; i++)
            {
                _accessContour.ContourLevel[i] = (_accessContour.GridInfo._zMax * i + (NOfContourLevel - i - 1) * _accessContour.GridInfo._zMin)
                                                    / (NOfContourLevel - 1);
            }
        }

        public void SetFileName(string fileName)
        {
            _preString = _accessContour.FileName;
            _accessContour.FileName = fileName;
        }

        public List<IsoPointListInfo> AllIsoPointList
        {
            get
            {
                return _allIsoPointList;
            }
        }

        public bool IsDefaultContourLevel
        {
            set
            {
                _isSetDefaultContourLevel = value;
            }
        }

        /*   
        N：已知节点数N+1   
        R：欲求插值点数R+1   
        x，y为给定函数f(x)的节点值{x(i)}   (x(i)<x(i+1))   ,以及相应的函数值{f(i)}     0<=i<=N   
        P0=f(x0)的二阶导数；Pn=f(xn)的二阶导数   
        u:存插值点{u(i)}       0<=i<=R   
        求得的结果s(ui)放入s[R+1]       0<=i<=R   
        返回0表示成功，1表示失败   
        */   
        public static int SPL(int N, int R, double[] x, double[] y, double P0, double Pn, double[] u, double[] s)
        {
            double[] h = new double[N];
            double[] a = new double[N + 1];
            double[] c = new double[N];
            double[] g = new double[N + 1];
            double[] af = new double[N + 1];
            double[] ba = new double[N];
            double[] m = new double[N + 1];

            int i, k;
            double p1, p2, p3, p4;

            /*第一步：计算方程组的系数*/
            for (k = 0; k < N; k++)
                h[k] = x[k + 1] - x[k];
            for (k = 1; k < N; k++)
            {
                if (((h[k] + h[k - 1]) < 0.000001) && ((h[k] + h[k - 1]) > -0.000001))
                {
                    a[k] = h[k] / 0.001;
                    continue;
                }
                a[k] = h[k] / (h[k] + h[k - 1]);
            }
            for (k = 1; k < N; k++)
                c[k] = 1 - a[k];
            for (k = 1; k < N; k++)
                g[k] = 3 * (c[k] * (y[k + 1] - y[k]) / h[k] + a[k] * (y[k] - y[k - 1]) / h[k - 1]);
            c[0] = a[N] = 1;
            g[0] = 3 * (y[1] - y[0]) / h[0] - P0 * h[0] / 2;
            g[N] = 3 * (y[N] - y[N - 1]) / h[N - 1] + Pn * h[N - 1] / 2;

            /*第二步：用追赶法解方程组求{m(i)}     */
            ba[0] = c[0] / 2;
            g[0] = g[0] / 2;
            for (i = 1; i < N; i++)
            {
                af[i] = 2 - a[i] * ba[i - 1];
                g[i] = (g[i] - a[i] * g[i - 1]) / af[i];
                ba[i] = c[i] / af[i];
            }
            af[N] = 2 - a[N] * ba[N - 1];
            g[N] = (g[N] - a[N] * g[N - 1]) / af[N];

            m[N] = g[N];                   /*P110   公式：6.32*/
            for (i = N - 1; i >= 0; i--)
                m[i] = g[i] - ba[i] * m[i + 1];

            /*第三步：求值*/
            for (i = 0; i <= R; i++)
            {
                /*判断u(i)属于哪一个子区间，即确定k   */
                if (u[i] < x[0] || u[i] > x[N])
                {
                    return 1;
                }
                k = 0;
                while (u[i] > x[k + 1])
                    k++;


                p1 = (h[k] + 2 * (u[i] - x[k])) * Math.Pow((u[i] - x[k + 1]), 2) * y[k] / Math.Pow(h[k], 3);
                p2 = (h[k] - 2 * (u[i] - x[k + 1])) * Math.Pow((u[i] - x[k]), 2) * y[k + 1] / Math.Pow(h[k], 3);
                p3 = (u[i] - x[k]) * Math.Pow((u[i] - x[k + 1]), 2) * m[k] / Math.Pow(h[k], 2);
                p4 = (u[i] - x[k + 1]) * Math.Pow((u[i] - x[k]), 2) * m[k + 1] / Math.Pow(h[k], 2);
                s[i] = p1 + p2 + p3 + p4;
            }

            return 0;
        }   

    }

    public delegate void FollowingFinish();
}
