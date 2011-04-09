//////////////////////////////////////////////////////////////////////
// NLequation.h
//
// 求解线性方程组的类 CNLequation 的声明接口
//
// 周长发编制, 2002/8
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NLEQUATION_H__72143033_E39F_404E_9A3B_F870E603EEE2__INCLUDED_)
#define AFX_NLEQUATION_H__72143033_E39F_404E_9A3B_F870E603EEE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

// 需要调用复数和矩阵运算
#include "Matrix.h"
#include "Complex.h"

// 类声明
class AFX_EXT_CLASS CNLequation  
{
	//
	// 公有接口函数
	//
public:

	//
	// 构造与析构
	//

	CNLequation();
	virtual ~CNLequation();

	//
	// 虚函数：计算方程左端函数值，必须在引申类中覆盖该类函数
	//

	virtual double Func(double x)
	{
		return 0.0;
	}
	virtual double Func(int n, double x[])
	{
		return 0.0;
	}
	virtual void Func(double x, double y[])
	{
	}
	virtual double Func(double x, double y)
	{
		return 0.0;
	}
	virtual double Func(double x[], double y[])
	{
		return 0.0;
	}
    virtual void FuncMJ(int n, double x[], double p[])
	{
	}

	//
	// 非线性方程求解算法
	//

	// 求非线性方程实根的对分法
	int GetRootBisect(int nNumRoots, double x[], double xStart, double xEnd, double dblStep, double eps = 0.000001);
	// 求非线性方程一个实根的牛顿法
	BOOL GetRootNewton(double* x, int nMaxIt = 60, double eps = 0.000001);
	// 求非线性方程一个实根的埃特金迭代法
	BOOL GetRootAitken(double* x, int nMaxIt = 60, double eps = 0.000001);
	// 求非线性方程一个实根的连分式解法
	BOOL GetRootPq(double* x, double eps = 0.000001);
	// 求实系数代数方程全部根的QR方法
	BOOL GetRootQr(int n, double dblCoef[], double xr[], double xi[], int nMaxIt = 60, double eps = 0.000001);
	// 求实系数代数方程全部根的牛顿下山法
	BOOL GetRootNewtonDownHill(int n, double dblCoef[], double xr[], double xi[]);
	// 求复系数代数方程全部根的牛顿下山法
	BOOL GetRootNewtonDownHill(int n, double ar[], double ai[], double xr[], double xi[]);
	// 求非线性方程一个实根的蒙特卡洛法
	void GetRootMonteCarlo(double* x, double xStart, int nControlB, double eps = 0.000001);
	// 求实函数或复函数方程一个复根的蒙特卡洛法
	void GetRootMonteCarlo(double* x, double* y, double xStart, int nControlB, double eps = 0.000001);

	//
	// 非线性方程组求解算法
	//

	// 求非线性方程组一组实根的梯度法
	BOOL GetRootsetGrad(int n, double x[], int nMaxIt = 500, double eps = 0.000001);
	// 求非线性方程组一组实根的拟牛顿法
	BOOL GetRootsetNewton(int n, double x[], double t, double h, int nMaxIt = 500, double eps = 0.000001);
	// 求非线性方程组最小二乘解的广义逆法
	BOOL GetRootsetGinv(int m, int n, double x[], double eps1 = 0.000001, double eps2 = 0.000001);
	// 求非线性方程组一组实根的蒙特卡洛法
	void GetRootsetMonteCarlo(int n, double x[], double xStart, int nControlB, double eps = 0.000001);

	//
	// 内部函数
	//
private:
	void g60(double* t,double* x,double* y,double* x1,double* y1,double* dx,double* dy,double* p,double* q,int* k,int* it);
	void g90(double xr[],double xi[],double dblCoef[],double* x,double* y,double* p,double* q,double* w,int* k);
	void g65(double* x,double* y,double* x1,double* y1,double* dx,double* dy,double* dd,double* dc,double* c,int* k,int* is,int* it);
	void g60c(double* t,double* x,double* y,double* x1,double* y1,double* dx,double* dy,double* p,double* q,int* k,int* it);
	void g90c(double xr[],double xi[],double ar[],double ai[],double* x,double* y,double* p,double* w,int* k);
	void g65c(double* x,double* y,double* x1,double* y1,double* dx,double* dy,double* dd,double* dc,double* c,int* k,int* is,int* it);
	double rnd(double* r);
};

#endif // !defined(AFX_NLEQUATION_H__72143033_E39F_404E_9A3B_F870E603EEE2__INCLUDED_)
