//////////////////////////////////////////////////////////////////////
// Interpolate.h
//
// 插值类 CInterpolate 的声明接口
//
// 周长发编制, 2002/8
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERPOLATE_H__0AF22CA4_A4AA_486B_9D68_E074FABDAF85__INCLUDED_)
#define AFX_INTERPOLATE_H__0AF22CA4_A4AA_486B_9D68_E074FABDAF85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

class CInterpolate  
{
public:
	//
	// 构造与析构
	//

	CInterpolate();
	virtual ~CInterpolate();

	//
	// 将字符串转换成结点值
	//

	static int GetNodesFromString(CString s, int n, double dblNodes[], const CString& sDelim = " ");

	//
	// 插值算法函数
	//

	// 一元全区间不等距插值
	static double GetValueLagrange(int n, double x[], double y[], double t);
	// 一元全区间等距插值
	static double GetValueLagrange(int n, double x0, double xStep, double y[], double t);
	// 一元三点不等距插值
	static double GetValueLagrange3(int n, double x[], double y[], double t);
	// 一元三点等距插值
	static double GetValueLagrange3(int n, double x0, double xStep, double y[], double t);
	// 连分式不等距插值
	static double GetValuePqs(int n, double x[], double y[], double t);
	// 连分式等距插值
	static double GetValuePqs(int n, double x0, double xStep, double y[], double t);
	// 埃尔米特不等距插值
	static double GetValueHermite(int n, double x[], double y[], double dy[], double t);
	// 埃尔米特等距插值
	static double GetValueHermite(int n, double x0, double xStep, double y[], double dy[], double t);
	// 埃特金不等距逐步插值
	static double GetValueAitken(int n, double x[], double y[], double t, double eps = 0.000001);
	// 埃特金等距逐步插值
	static double GetValueAitken(int n, double x0, double xStep, double y[], double t, double eps = 0.000001);
	// 光滑不等距插值
	static double GetValueAkima(int n, double x[], double y[], double t, double s[], int k = -1);
	// 光滑等距插值
	static double GetValueAkima(int n, double x0, double xStep, double y[], double t, double s[], int k = -1);
	// 第一种边界条件的三次样条函数插值、微商与积分
	static double GetValueSpline1(int n, double x[], double y[], double dy[], double ddy[], 
								  int m, double t[], double z[], double dz[], double ddz[]);
	// 第二种边界条件的三次样条函数插值、微商与积分
	static double GetValueSpline2(int n, double x[], double y[], double dy[], double ddy[], 
								  int m, double t[], double z[], double dz[], double ddz[]);
	// 第三种边界条件的三次样条函数插值、微商与积分
	static double GetValueSpline3(int n, double x[], double y[], double dy[], double ddy[], 
								  int m, double t[], double z[], double dz[], double ddz[]);
	// 二元三点插值
	static double GetValueTqip(int n, double x[], int m, double y[], double z[], double u, double v);
	// 二元全区间插值
	static double GetValueLagrange2(int n, double x[], int m, double y[], double z[], double u, double v);
};

#endif // !defined(AFX_INTERPOLATE_H__0AF22CA4_A4AA_486B_9D68_E074FABDAF85__INCLUDED_)
