using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace ContourFill01
{
    public partial class Form1 : Form
    {
        private const float Precision = 1E-6f;
        private const int Alpha = 255 << 24;

        List<List<PointF>> _contourLists;

        enum ContourType
        {
            EdgeContour,        //a类等值线
            CornerContour,      //b类
            BridgeContour,      //c类
            ClosedContour      //d类
        }

        enum EdgeType
        {
            Left,Top,Right,Buttom,Closed
        }

        class ExtContourList
        {
            public List<PointF> contourList;
            public ContourType contourType;
        }

        List<ExtContourList> _leftContourLists;   //起点在左边上的等值线的集合（同时包含了它的类型（指a,b,c,d类型））
        List<ExtContourList> _topContourLists;    //起点在上边上的等值线的集合
        List<ExtContourList> _rightContourLists;  //起点在右边上的等值线的集合
        List<ExtContourList> _buttomContourLists; //起点在下边上的等值线的集合
        List<ExtContourList> _closedContourLists; //封闭等值线的集合

        float _xMin = 0;
        float _xMax = 450.0f;
        float _yMin = 0;
        float _yMax = 350.0f;

        public Form1()
        {
            InitializeComponent();
            this.Text = "等值线填充";
            this.BackColor = Color.Azure;
            this.Size = new Size(640, 480);

            _leftContourLists = new List<ExtContourList>();
            _topContourLists = new List<ExtContourList>();
            _rightContourLists = new List<ExtContourList>();
            _buttomContourLists = new List<ExtContourList>();
            _closedContourLists = new List<ExtContourList>();
            
            GetContourData();
            ClassifyContour();
            SortContourList();

            this.Refresh();
        }

        //从文件中得到等值线数据
        //以分号（；）分隔，每一段代表一条等值线
        //每一段中的每一行就是等值点的坐标位置
        //每一行中有X，Y，用空格分隔
        private void GetContourData()
        {
            _contourLists = new List<List<PointF>>();

            try
            {
                StreamReader streamReader = new StreamReader(@"..\..\contourdata.txt", Encoding.Default);
                string content = streamReader.ReadToEnd();
                content=content.Replace("\r\n","\n");
                string[] stringLines = content.Trim().Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);         //得到分号分隔的每一段

                string[] contourLinesString;
                string[] lineString;
                for (int i = 0; i < stringLines.Length; i++)
                {
                    contourLinesString = stringLines[i].Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);  //每一段中的所有行
                    List<PointF> contourList = new List<PointF>();
                    for (int j = 0; j < contourLinesString.Length; j++)
                    {
                        lineString = contourLinesString[j].Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                        contourList.Add(new PointF(Convert.ToSingle(lineString[0]),Convert.ToSingle(lineString[1])));
                    }
                    _contourLists.Add(contourList);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        //对等值线进行分类，参照论文，将其分成a,b,c,d四类
        //这里将所有的等值线带上a,b,c,d的分类后，保存另一链表
        private void ClassifyContour()
        {
            List<PointF> contourList;
            for (int i = 0; i < _contourLists.Count; i++)
            {
                contourList = _contourLists[i];

                ExtContourList extContourList = new ExtContourList();
                extContourList.contourList = contourList;

                //由起始，终止点所在的边来决定是那一种等值线类型
                //例如，起始点在左边（EdgeType.Left)，而终止点在上边（EdgeType.Top）
                //这样的情况下的等值线类型就是b类（ContourType.CornerContour）（边角等值线）
                switch (GetEdgeType(contourList[0]))//起点的边类型
                {
                    case EdgeType.Left:
                        switch (GetEdgeType(contourList[contourList.Count-1]))//终止点的边类型
                        {
                            case EdgeType.Left:
                                extContourList.contourType = ContourType.EdgeContour;       //如果是a类型等值线，就不需要加入点
                                break;
                            case EdgeType.Top:
                                extContourList.contourType = ContourType.CornerContour;
                                contourList.Add(new PointF(_xMin, _yMax));                      //加入左上角点（b类型）
                                break;
                            case EdgeType.Buttom:
                                extContourList.contourType = ContourType.CornerContour;     //加入左下角点（b类型）
                                contourList.Add(new PointF(_xMin, _yMin));
                                break;
                            case EdgeType.Right:
                                extContourList.contourType = ContourType.BridgeContour;
                                contourList.Add(new PointF(_xMax, _yMax));                  //加入两个点
                                contourList.Add(new PointF(_xMin, _yMax));
                                break;
                            default:
                                throw new Exception("等值线追踪出错");
                        }
                        _leftContourLists.Add(extContourList);
                        break;
                    case EdgeType.Top:
                        switch (GetEdgeType(contourList[contourList.Count - 1]))//终止点的边类型
                        {
                            case EdgeType.Left:
                                extContourList.contourType = ContourType.CornerContour;
                                break;
                            case EdgeType.Right:
                                extContourList.contourType = ContourType.CornerContour;
                                contourList.Add(new PointF(_xMax, _yMax));
                                break;
                            case EdgeType.Top:
                                extContourList.contourType = ContourType.EdgeContour;
                                break;
                            case EdgeType.Buttom:
                                extContourList.contourType = ContourType.BridgeContour;
                                contourList.Add(new PointF(_xMax, _yMin));
                                contourList.Add(new PointF(_xMax, _yMax));
                                break;
                            default:
                                throw new Exception("等值线追踪出错");
                        }
                        _topContourLists.Add(extContourList);
                        break;
                    case EdgeType.Right:
                        switch (GetEdgeType(contourList[contourList.Count - 1]))//终止点的边类型
                        {
                            case EdgeType.Top:
                                extContourList.contourType = ContourType.CornerContour;
                                break;
                            case EdgeType.Buttom:
                                extContourList.contourType = ContourType.CornerContour;
                                contourList.Add(new PointF(_xMax, _yMin));
                                break;
                            case EdgeType.Right:
                                extContourList.contourType = ContourType.EdgeContour;
                                break;
                            case EdgeType.Left:
                                extContourList.contourType = ContourType.BridgeContour;
                                contourList.Add(new PointF(_xMax, _yMax));
                                contourList.Add(new PointF(_xMin, _yMax));
                                break;
                            default:
                                throw new Exception("等值线追踪出错");
                        }
                        _rightContourLists.Add(extContourList);
                        break;
                    case EdgeType.Buttom:
                        switch (GetEdgeType(contourList[contourList.Count - 1]))//终止点的边类型
                        {
                            case EdgeType.Left:
                                extContourList.contourType = ContourType.CornerContour;
                                contourList.Add(new PointF(_xMin, _yMin));
                                break;
                            case EdgeType.Right:
                                extContourList.contourType = ContourType.CornerContour;
                                contourList.Add(new PointF(_xMax, _yMin));
                                break;
                            case EdgeType.Top:
                                extContourList.contourType = ContourType.BridgeContour;
                                break;
                            case EdgeType.Buttom:
                                extContourList.contourType = ContourType.EdgeContour;
                                break;
                            default:
                                throw new Exception("等值线追踪出错");
                        }
                        _buttomContourLists.Add(extContourList);
                        break;
                    case EdgeType.Closed:
                        extContourList.contourType = ContourType.ClosedContour;
                        _closedContourLists.Add(extContourList);
                        break;
                }

            }
        }

        //得到起始点或终止点在边框的左，右，上，下哪个边，
        //由起始，终止点所在的边来决定是那一种等值线类型
        //例如，起始点在左边（EdgeType.Left)，而终止点在上边（EdgeType.Top）
        //这样的情况下的等值线类型就是b类（ContourType.CornerContour）（边角等值线）
        private EdgeType GetEdgeType(PointF edgePoint)
        {
            if (edgePoint.X < Precision && edgePoint.X > -Precision)
                return EdgeType.Left;
            else if (edgePoint.Y < Precision && edgePoint.Y > -Precision)
            {
                return EdgeType.Buttom;
            }
            else if (((edgePoint.X - _xMax) < Precision) && ((edgePoint.X - _xMax) > -Precision))
            {
                return EdgeType.Right;
            }
            else if (((edgePoint.Y - _yMax) < Precision) && ((edgePoint.Y - _yMax) > -Precision))
            {
                return EdgeType.Top;
            }
            else
            {
                return EdgeType.Closed;
            }
        }

        //对每一段中的等值线排序
        private void SortContourList()
        {
            List<ExtContourList> aList = new List<ExtContourList>();       //a,b,c类型等值线
            List<ExtContourList> bList = new List<ExtContourList>();
            List<ExtContourList> cList = new List<ExtContourList>();
            List<ExtContourList> closedList = new List<ExtContourList>();

            //对左边界上的等值线排序
            for (int i = 0; i < _leftContourLists.Count; i++)
            {
                switch (_leftContourLists[i].contourType)
                {
                    case ContourType.EdgeContour:
                        aList.Add(_leftContourLists[i]);
                        break;
                    case ContourType.CornerContour:
                        bList.Add(_leftContourLists[i]);
                        break;
                    case ContourType.BridgeContour:
                        cList.Add(_leftContourLists[i]);
                        break;
                    case ContourType.ClosedContour:
                        //closedList.Add(_leftContourLists[i]);          　//这个是不可能的，如果发生，只可能是出现错误
                        throw new Exception("排序时出错");
                        //break;
                }
            }
            InsertSort(aList, true, false);
            InsertSort(bList, true, false);        //注意blist中的等值线的填充方式要分成两种情况
                                            //一种是终点在上边界，另一种是终点在下边界，是要分开处理的，面这里有排序是统一升序
            InsertSort(cList, true, false);
            _leftContourLists.Clear();

            AddListToList(_leftContourLists, ref aList);
            AddListToList(_leftContourLists, ref bList);
            AddListToList(_leftContourLists, ref cList);

            //对上边界上的等值线排序
            for (int i = 0; i < _topContourLists.Count; i++)
            {
                switch (_topContourLists[i].contourType)
                {
                    case ContourType.EdgeContour:
                        aList.Add(_topContourLists[i]);
                        break;
                    case ContourType.CornerContour:
                        bList.Add(_topContourLists[i]);
                        break;
                    case ContourType.BridgeContour:
                        cList.Add(_topContourLists[i]);
                        break;
                    case ContourType.ClosedContour:
                        //closedList.Add(_leftContourLists[i]);          　//这个是不可能的，如果发生，只可能是出现错误
                        throw new Exception("排序时出错");
                        //break;
                }
            }
            InsertSort(aList, true, true);
            InsertSort(bList, true, true);
            InsertSort(cList, true, true);
            _topContourLists.Clear();
            AddListToList(_topContourLists, ref aList);
            AddListToList(_topContourLists, ref bList);
            AddListToList(_topContourLists, ref cList);

            //对右边界上的等值线排序
            for (int i = 0; i < _rightContourLists.Count; i++)
            {
                switch (_rightContourLists[i].contourType)
                {
                    case ContourType.EdgeContour:
                        aList.Add(_rightContourLists[i]);
                        break;
                    case ContourType.CornerContour:
                        bList.Add(_rightContourLists[i]);
                        break;
                    case ContourType.BridgeContour:
                        cList.Add(_rightContourLists[i]);
                        break;
                    case ContourType.ClosedContour:
                        //closedList.Add(_rightContourLists[i]);          　//这个是不可能的，如果发生，只可能是出现错误
                        throw new Exception("排序时出错");
                    //break;
                }
            }
            InsertSort(aList, false, false);
            InsertSort(bList, false, false);
            InsertSort(cList, false, false);
            _rightContourLists.Clear();
            AddListToList(_rightContourLists, ref aList);
            AddListToList(_rightContourLists, ref bList);
            AddListToList(_rightContourLists, ref cList);

            //对下边界上的等值线排序
            for (int i = 0; i < _buttomContourLists.Count; i++)
            {
                switch (_buttomContourLists[i].contourType)
                {
                    case ContourType.EdgeContour:
                        aList.Add(_buttomContourLists[i]);
                        break;
                    case ContourType.CornerContour:
                        bList.Add(_buttomContourLists[i]);
                        break;
                    case ContourType.BridgeContour:
                        cList.Add(_buttomContourLists[i]);
                        break;
                    case ContourType.ClosedContour:
                        //closedList.Add(_buttomContourLists[i]);          　//这个是不可能的，如果发生，只可能是出现错误
                        throw new Exception("排序时出错");
                    //break;
                }
            }
            InsertSort(aList, false, true);
            InsertSort(bList, false, true);
            InsertSort(cList, false, true);
            _buttomContourLists.Clear();
            AddListToList(_buttomContourLists, ref aList);
            AddListToList(_buttomContourLists, ref bList);
            AddListToList(_buttomContourLists, ref cList);

            //对封闭等值线排序
            InsertSort(_closedContourLists, true, true);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            int contourSum = _leftContourLists.Count + _topContourLists.Count + _rightContourLists.Count        //等值线总条数
                + _buttomContourLists.Count + _closedContourLists.Count;
            int filledNum = 0;                       //已经填充过的等值线的条数

            FillCContour(e.Graphics, contourSum, ref filledNum);        //填充C类等值线
            FillBContour(e.Graphics, contourSum, ref filledNum);        //填充B类等值线
            FillAContour(e.Graphics, contourSum, ref filledNum);        //填充A类等值线
            FillClosedContour(e.Graphics, contourSum, ref filledNum);   //填充封闭等值线
        }

        //填充C类等值线
        private void FillCContour(Graphics g, int contourSum, ref int filledNum)
        {
            List<ExtContourList> cList = new List<ExtContourList>();      //abc三类等值线的装载链表
            
            int color;
            PointF[] points;
            int fillingNum = 0;

            //左右方向--C类
            for (int i = 0; i < _leftContourLists.Count; i++)
            {
                if (_leftContourLists[i].contourType == ContourType.BridgeContour)
                {
                    cList.Add(_leftContourLists[i]);
                    fillingNum++;
                }
            }
            if (cList.Count == 0) //上下方向--C类
            {
                for (int i = 0; i < _topContourLists.Count; i++)
                {
                    if (_topContourLists[i].contourType == ContourType.BridgeContour)
                    {
                        cList.Add(_topContourLists[i]);
                        fillingNum++;
                    }
                }
            }

            for (int i = 0; i <cList.Count; i++)
            {
                color = GetColorArgb((int)(64 * i / contourSum));
                points = new PointF[cList[i].contourList.Count];

                for (int j = 0; j < points.Length; j++)
                {
                    points[j] = cList[i].contourList[j];
                    //points[j].X = cList[i].contourList[j].X;
                    //points[j].Y = cList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }
            filledNum = filledNum + fillingNum;
            cList = null;
        }

        //填充B类等值线
        private void FillBContour(Graphics g, int contourSum, ref int filledNum)
        {
            List<ExtContourList> leftButtomList = new List<ExtContourList>();       //当起始点在左边界，填充B类等值线是必须要分开考虑
            List<ExtContourList> leftTopList = new List<ExtContourList>();          //因为在开始排序的时候是统一升序排的，这个地方是比较特殊的

            PointF[] points;
            int fillingNum = 0;
            int color = 0;

            #region 填充起点在左边界的B类等值线
            for (int i = 0; i < _leftContourLists.Count; i++)
            {
                if (_leftContourLists[i].contourType == ContourType.CornerContour)
                {
                    if (GetEdgeType(_leftContourLists[i].contourList[_leftContourLists[i].contourList.Count - 2]) == EdgeType.Buttom)
                    {
                        leftButtomList.Add(_leftContourLists[i]);
                        fillingNum++;
                    }
                    else if (GetEdgeType(_leftContourLists[i].contourList[_leftContourLists[i].contourList.Count - 2]) == EdgeType.Top)
                    {
                        leftTopList.Add(_leftContourLists[i]);
                        fillingNum++;
                    }
                }
            }

            for (int i = leftButtomList.Count - 1; i >= 0; i--)     //必须由大到小(因为在开始排序的时候是统一升序排的，这个地方是比较特殊的)
            {
                points = new PointF[leftButtomList[i].contourList.Count];
                color = GetColorArgb((int)((64f / contourSum) * (i + filledNum)));

                for (int j = 0; j < points.Length; j++)
                {
                    points[j].X = leftButtomList[i].contourList[j].X;
                    points[j].Y = leftButtomList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }

            for (int i = 0; i < leftTopList.Count; i++)
            {
                points = new PointF[leftTopList[i].contourList.Count];
                color = GetColorArgb((int)((64f / contourSum) * (i + filledNum)));

                for (int j = 0; j < points.Length; j++)
                {
                    points[j].X = leftTopList[i].contourList[j].X;
                    points[j].Y = leftTopList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }
            filledNum += fillingNum;
            fillingNum = 0;                 //已经加过了，就要将计数器置0
            leftTopList = null;
            leftButtomList = null;

            #endregion 填充起点在左边界的B类等值线

            #region 填充起点在上边界的B类等值线
            List<ExtContourList> bList = new List<ExtContourList>();
            for (int i = 0; i < _topContourLists.Count; i++)
            {
                if (_topContourLists[i].contourType == ContourType.CornerContour)
                {
                    bList.Add(_topContourLists[i]);
                    fillingNum++;
                }
            }

            for (int i = 0; i < bList.Count; i++)
            {
                points = new PointF[bList[i].contourList.Count];
                color = GetColorArgb((int)((64f / contourSum) * (i + filledNum)));

                for (int j = 0; j < points.Length; j++)
                {
                    points[j].X = bList[i].contourList[j].X;
                    points[j].Y = bList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }
            filledNum += fillingNum;
            fillingNum = 0;
            bList.Clear();

            #endregion 填充起点在上边界的B类等值线

            #region 填充起点在右边界的B类等值线

            for (int i = 0; i < _rightContourLists.Count; i++)
            {
                if (_rightContourLists[i].contourType == ContourType.CornerContour)
                {
                    bList.Add(_rightContourLists[i]);
                    fillingNum++;
                }
            }

            for (int i = 0; i < bList.Count; i++)
            {
                points = new PointF[bList[i].contourList.Count];
                color = GetColorArgb((int)((64f / contourSum) * (i + filledNum)+20));

                for (int j = 0; j < points.Length; j++)
                {
                    points[j].X = bList[i].contourList[j].X;
                    points[j].Y = bList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }
            filledNum += fillingNum;
            fillingNum = 0;
            bList = null;
            #endregion 填充起点在右边界的B类等值线

            #region  填充起点在下边界的B类等值线（注，这种是不可能有的，有的话，只可能前面产生错误）
            #endregion  填充起点在下边界的B类等值线
        }

        //填充A类等值线
        private void FillAContour(Graphics g, int contourSum, ref int filledNum)
        {
            List<ExtContourList> aList = new List<ExtContourList>();

            int color;
            PointF[] points;
            int fillingNum = 0;

            #region 填充起点在左，上边界的A类等值线（这两种是可以一起处理的）
            for (int i = 0; i < _leftContourLists.Count; i++)
            {
                if (_leftContourLists[i].contourType == ContourType.EdgeContour)
                {
                    aList.Add(_leftContourLists[i]);
                    fillingNum++;
                }
            }

            for (int i = 0; i < _topContourLists.Count; i++)
            {
                if (_topContourLists[i].contourType == ContourType.EdgeContour)
                {
                    aList.Add(_topContourLists[i]);
                    fillingNum++;
                }
            }

            for (int i = 0; i < aList.Count; i++)
            {
                points = new PointF[aList[i].contourList.Count];
                color = GetColorArgb((int)((64f / contourSum) * (i + filledNum)));

                for (int j = 0; j < points.Length; j++)
                {
                    points[j].X = aList[i].contourList[j].X;
                    points[j].Y = aList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }
            filledNum += fillingNum;
            fillingNum = 0;         //重新开始计数
            aList.Clear();
            #endregion 填充起点在左，上边界的A类等值线（这两种是可以一起处理的）

            #region 填充起点在右，下边界的A类等值线（这两种是可以一起处理的）
            for (int i = 0; i < _rightContourLists.Count; i++)
            {
                if (_rightContourLists[i].contourType == ContourType.EdgeContour)
                {
                    aList.Add(_rightContourLists[i]);
                    fillingNum++;
                }
            }

            for (int i = 0; i < _buttomContourLists.Count; i++)
            {
                if (_buttomContourLists[i].contourType == ContourType.EdgeContour)
                {
                    aList.Add(_buttomContourLists[i]);
                    fillingNum++;
                }
            }

            for (int i = 0; i < aList.Count; i++)
            {
                points = new PointF[aList[i].contourList.Count];
                color = GetColorArgb((int)((64f / contourSum) * (i + filledNum)));

                for (int j = 0; j < points.Length; j++)
                {
                    points[j].X = aList[i].contourList[j].X;
                    points[j].Y = aList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }
            filledNum += fillingNum;
            fillingNum = 0;
            aList = null;
            #endregion 填充起点在右，下边界的A类等值线（这两种是可以一起处理的）
        }

        //填充封闭等值线
        private void FillClosedContour(Graphics g, int contourSum, ref int filledNum)
        {
            List<ExtContourList> closedList = new List<ExtContourList>();

            int color;
            PointF[] points;
            int fillingNum = 0;

            for (int i = 0; i < _closedContourLists.Count; i++)
            {
                if (_closedContourLists[i].contourType == ContourType.ClosedContour)
                {
                    closedList.Add(_closedContourLists[i]);
                    fillingNum++;
                }
            }

            for (int i = 0; i < closedList.Count; i++)
            {
                points = new PointF[closedList[i].contourList.Count];
                color = GetColorArgb((int)((64f / contourSum) * (i + filledNum)));

                for (int j = 0; j < points.Length; j++)
                {
                    points[j].X = closedList[i].contourList[j].X;
                    points[j].Y = closedList[i].contourList[j].Y;
                }
                SolidBrush brush = new SolidBrush(Color.FromArgb(color));
                g.FillPolygon(brush, points);
            }
        }

        //得到颜色的ARGB值
        private int GetColorArgb(int n)
        {
            if (n >= 0 && n <= 7)
            {
                return (0x00008f + (n << 4) + Alpha);
            }
            if (n >= 8 && n <= 23)
            {
                return (0x000fff + ((n - 8) << 12) + Alpha);
            }
            if (n >= 24 && n <= 38)
            {
                return (0x00ffff + ((n - 24) << 20) - ((n - 23) << 4) + Alpha);

            }
            if (n >= 39 && n <= 54)
            {
                return (0xffff00 - ((n - 39) << 12) + Alpha);
            }
            if (n >= 55 && n <= 64)
            {
                return (0xff0000 - ((n - 54) << 20) + Alpha);
            }
            return Color.White.ToArgb();
        }

        //快速排序
        //isAscend-----是否降序     true----升序   false---降序  
        //isXSort------是否以X为准排序  true---是   fase---否
        private void InsertSort(List<ExtContourList> lists, bool isAscend, bool isXSort)
        {
            if (lists.Count <= 0)
                return;

            if (isAscend)
            {
                //以X为排序对象，否则以Y为排序对象（升序）
                if (isXSort)
                {
                    ExtContourList curContourList = new ExtContourList();
                    int j = 0;
                    for (int i = 1; i < lists.Count; i++)
                    {
                        curContourList.contourList = lists[i].contourList;
                        curContourList.contourType = lists[i].contourType;

                        j = i;
                        while (j > 0 && lists[j - 1].contourList[0].X > curContourList.contourList[0].X)
                        {
                            lists[j].contourList = lists[j-1].contourList;
                            lists[j].contourType = lists[j-1].contourType;
                            
                            j--;
                        }
                        lists[j].contourList = curContourList.contourList;
                        lists[j].contourType = curContourList.contourType;
                    }
                }
                else
                {
                    ExtContourList curContourList = new ExtContourList();
                    int j = 0;
                    for (int i = 1; i < lists.Count; i++)
                    {
                        curContourList.contourList = lists[i].contourList;
                        curContourList.contourType = lists[i].contourType;

                        j = i;
                        while (j > 0 && lists[j - 1].contourList[0].Y > curContourList.contourList[0].Y)
                        {
                            lists[j].contourList = lists[j - 1].contourList;
                            lists[j].contourType = lists[j - 1].contourType;

                            j--;
                        }
                        lists[j].contourList = curContourList.contourList;
                        lists[j].contourType = curContourList.contourType;
                    }
                }
            }
            else
            {
                //以X为排序对象，否则以Y为排序对象 （降序）
                if (isXSort)
                {
                    ExtContourList curContourList = new ExtContourList();
                    int j = 0;
                    for (int i = 1; i < lists.Count; i++)
                    {
                        curContourList.contourList = lists[i].contourList;
                        curContourList.contourType = lists[i].contourType;

                        j = i;
                        while ((j > 0) && (lists[j - 1].contourList[0].X < curContourList.contourList[0].X))
                        {
                            lists[j].contourList = lists[j - 1].contourList;
                            lists[j].contourType = lists[j - 1].contourType;

                            j--;
                        }
                        lists[j].contourList = curContourList.contourList;
                        lists[j].contourType = curContourList.contourType;
                    }
                }
                else
                {
                    ExtContourList curContourList = new ExtContourList();
                    int j = 0;
                    for (int i = 1; i <lists.Count; i++)
                    {
                        curContourList.contourList = lists[i].contourList;
                        curContourList.contourType = lists[i].contourType;

                        j = i;
                        while ((j >0) && (lists[j-1].contourList[0].Y < curContourList.contourList[0].Y))
                        {
                            lists[j].contourList = lists[j - 1].contourList;
                            lists[j].contourType = lists[j - 1].contourType;

                            j--;
                        }
                        lists[j].contourList = curContourList.contourList;
                        lists[j].contourType = curContourList.contourType;
                    }
                }
            }
        }

        //将copyingList中的元素加入到目的表中
        private void AddListToList(List<ExtContourList> desContourList, ref List<ExtContourList> addingList)
        {
            for (int i = 0; i < addingList.Count; i++)
            {
                desContourList.Add(addingList[i]);
            }
            addingList.Clear();
        }
    }
}
