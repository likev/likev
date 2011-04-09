//////////////////////////////////////////////////////////////////////
// NLequation.h
//
// ������Է�������� CNLequation �������ӿ�
//
// �ܳ�������, 2002/8
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NLEQUATION_H__72143033_E39F_404E_9A3B_F870E603EEE2__INCLUDED_)
#define AFX_NLEQUATION_H__72143033_E39F_404E_9A3B_F870E603EEE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>

// ��Ҫ���ø����;�������
#include "Matrix.h"
#include "Complex.h"

// ������
class AFX_EXT_CLASS CNLequation  
{
	//
	// ���нӿں���
	//
public:

	//
	// ����������
	//

	CNLequation();
	virtual ~CNLequation();

	//
	// �麯�������㷽����˺���ֵ���������������и��Ǹ��ຯ��
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
	// �����Է�������㷨
	//

	// ������Է���ʵ���ĶԷַ�
	int GetRootBisect(int nNumRoots, double x[], double xStart, double xEnd, double dblStep, double eps = 0.000001);
	// ������Է���һ��ʵ����ţ�ٷ�
	BOOL GetRootNewton(double* x, int nMaxIt = 60, double eps = 0.000001);
	// ������Է���һ��ʵ���İ��ؽ������
	BOOL GetRootAitken(double* x, int nMaxIt = 60, double eps = 0.000001);
	// ������Է���һ��ʵ��������ʽ�ⷨ
	BOOL GetRootPq(double* x, double eps = 0.000001);
	// ��ʵϵ����������ȫ������QR����
	BOOL GetRootQr(int n, double dblCoef[], double xr[], double xi[], int nMaxIt = 60, double eps = 0.000001);
	// ��ʵϵ����������ȫ������ţ����ɽ��
	BOOL GetRootNewtonDownHill(int n, double dblCoef[], double xr[], double xi[]);
	// ��ϵ����������ȫ������ţ����ɽ��
	BOOL GetRootNewtonDownHill(int n, double ar[], double ai[], double xr[], double xi[]);
	// ������Է���һ��ʵ�������ؿ��巨
	void GetRootMonteCarlo(double* x, double xStart, int nControlB, double eps = 0.000001);
	// ��ʵ�����򸴺�������һ�����������ؿ��巨
	void GetRootMonteCarlo(double* x, double* y, double xStart, int nControlB, double eps = 0.000001);

	//
	// �����Է���������㷨
	//

	// ������Է�����һ��ʵ�����ݶȷ�
	BOOL GetRootsetGrad(int n, double x[], int nMaxIt = 500, double eps = 0.000001);
	// ������Է�����һ��ʵ������ţ�ٷ�
	BOOL GetRootsetNewton(int n, double x[], double t, double h, int nMaxIt = 500, double eps = 0.000001);
	// ������Է�������С���˽�Ĺ����淨
	BOOL GetRootsetGinv(int m, int n, double x[], double eps1 = 0.000001, double eps2 = 0.000001);
	// ������Է�����һ��ʵ�������ؿ��巨
	void GetRootsetMonteCarlo(int n, double x[], double xStart, int nControlB, double eps = 0.000001);

	//
	// �ڲ�����
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
