//////////////////////////////////////////////////////////////////////
// LEquations.h
//
// 求解线性方程组的类 CLEquations 的声明接口
//
// 周长发编制, 2002/8
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEQUATIONS_H__89A63160_719C_440D_9DFC_953F79BD4C4D__INCLUDED_)
#define AFX_LEQUATIONS_H__89A63160_719C_440D_9DFC_953F79BD4C4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 需要调用矩阵操作类
#include "Matrix.h"

// 类声明
class CLEquations  
{
	//
	// 公有接口函数
	//
public:

	//
	// 构造与析构
	//

	CLEquations();				// 默认构造函数
	// 指定系数和常数构造函数
	CLEquations(const CMatrix& mtxCoef, const CMatrix& mtxConst);
	virtual ~CLEquations();		// 析构函数
	// 初始化
	BOOL Init(const CMatrix& mtxCoef, const CMatrix& mtxConst);

	//
	// 属性
	//

	CMatrix GetCoefMatrix() const;	// 获取系数矩阵
	CMatrix GetConstMatrix() const;	// 获取常数矩阵
	int	GetNumEquations() const;	// 获取方程个数
	int	GetNumUnknowns() const;		// 获取未知数个数

	//
	// 线性方程组求解算法
	//

	// 全选主元高斯消去法
	BOOL GetRootsetGauss(CMatrix& mtxResult);
	// 全选主元高斯－约当消去法
	BOOL GetRootsetGaussJordan(CMatrix& mtxResult);
	// 复系数方程组的全选主元高斯消去法
	BOOL GetRootsetGauss(const CMatrix& mtxCoefImag, const CMatrix& mtxConstImag, CMatrix& mtxResult, CMatrix& mtxResultImag);
	// 复系数方程组的全选主元高斯－约当消去法
	BOOL GetRootsetGaussJordan(const CMatrix& mtxCoefImag, const CMatrix& mtxConstImag, CMatrix& mtxResult, CMatrix& mtxResultImag);
	// 求解三对角线方程组的追赶法
	BOOL GetRootsetTriDiagonal(CMatrix& mtxResult);
	// 一般带型方程组的求解
	BOOL GetRootsetBand(int nBandWidth, CMatrix& mtxResult);
	// 求解对称方程组的分解法
	BOOL GetRootsetDjn(CMatrix& mtxResult);
	// 求解对称正定方程组的平方根法
	BOOL GetRootsetCholesky(CMatrix& mtxResult);
	// 求解大型稀疏方程组的全选主元高斯－约去消去法
	BOOL GetRootsetGgje(CMatrix& mtxResult);
	// 求解托伯利兹方程组的列文逊方法
	BOOL GetRootsetTlvs(CMatrix& mtxResult);
	// 高斯－赛德尔迭代法
	BOOL GetRootsetGaussSeidel(CMatrix& mtxResult, double eps = 0.000001);
	// 求解对称正定方程组的共轭梯度法
	void GetRootsetGrad(CMatrix& mtxResult, double eps = 0.000001);
	// 求解线性最小二乘问题的豪斯荷尔德变换法
	BOOL GetRootsetMqr(CMatrix& mtxResult, CMatrix& mtxQ, CMatrix& mtxR);
	// 求解线性最小二乘问题的广义逆法
	BOOL GetRootsetGinv(CMatrix& mtxResult, CMatrix& mtxAP, CMatrix& mtxU, CMatrix& mtxV, double eps = 0.000001);
	// 病态方程组的求解
	BOOL GetRootsetMorbid(CMatrix& mtxResult, int nMaxIt = 60, double eps = 0.000001);

	//
	// 保护性数据成员
	//
protected:
	CMatrix	m_mtxCoef;		// 系数矩阵
	CMatrix m_mtxConst;		// 常数矩阵

};

#endif // !defined(AFX_LEQUATIONS_H__89A63160_719C_440D_9DFC_953F79BD4C4D__INCLUDED_)
