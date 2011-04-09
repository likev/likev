//////////////////////////////////////////////////////////////////////
// LEquations.h
//
// ������Է�������� CLEquations �������ӿ�
//
// �ܳ�������, 2002/8
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEQUATIONS_H__89A63160_719C_440D_9DFC_953F79BD4C4D__INCLUDED_)
#define AFX_LEQUATIONS_H__89A63160_719C_440D_9DFC_953F79BD4C4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ��Ҫ���þ��������
#include "Matrix.h"

// ������
class CLEquations  
{
public:
	// ����������
	CLEquations();
	CLEquations(const CMatrix& mtxCoef, const CMatrix& mtxConst);
	virtual ~CLEquations();
	// ��ʼ��
	BOOL Init(const CMatrix& mtxCoef, const CMatrix& mtxConst);
	// ��ȡ��������
	CMatrix GetCoefMatrix() const
	{
		return m_mtxCoef;
	}
	CMatrix GetConstMatrix() const
	{
		return m_mtxConst;
	}
	int	GetNumEquations() const
	{
		return GetCoefMatrix().GetNumRows();
	}
	int	GetNumUnknowns() const
	{
		return GetCoefMatrix().GetNumColumns();
	}

	// ���Է���������㷨

	// ȫѡ��Ԫ��˹��ȥ��
	BOOL GetRootsetGauss(CMatrix& mtxResult);
	// ȫѡ��Ԫ��˹��Լ����ȥ��
	BOOL GetRootsetGaussJordan(CMatrix& mtxResult);
	// ��ϵ���������ȫѡ��Ԫ��˹��ȥ��
	BOOL GetRootsetGauss(CMatrix mtxCoefImag, CMatrix mtxConstImag, CMatrix& mtxResult, CMatrix& mtxResultImag);
	// ��ϵ���������ȫѡ��Ԫ��˹��Լ����ȥ��
	BOOL GetRootsetGaussJordan(CMatrix mtxCoefImag, CMatrix mtxConstImag, CMatrix& mtxResult, CMatrix& mtxResultImag);
	// ������Խ��߷������׷�Ϸ�
	BOOL GetRootsetTriDiagonal(CMatrix& mtxResult);
	// һ����ͷ���������
	BOOL GetRootsetBand(int nBandWidth, CMatrix& mtxResult);
	// ���ԳƷ�����ķֽⷨ
	BOOL GetRootsetDjn(CMatrix& mtxResult);
	// ���Գ������������ƽ������
	BOOL GetRootsetCholesky(CMatrix& mtxResult);
	// ������ϡ�跽�����ȫѡ��Ԫ��˹��Լȥ��ȥ��
	BOOL GetRootsetGgje(CMatrix& mtxResult);
	// ����в����ȷ����������ѷ����
	BOOL GetRootsetTlvs(CMatrix& mtxResult);
	// ��˹�����¶�������
	BOOL GetRootsetGaussSeidel(CMatrix& mtxResult, double eps = 0.000001);
	// ���Գ�����������Ĺ����ݶȷ�
	void GetRootsetGrad(CMatrix& mtxResult, double eps = 0.000001);
	// ���������С��������ĺ�˹�ɶ��±任��
	BOOL GetRootsetMqr(CMatrix& mtxResult, CMatrix& mtxQ, CMatrix& mtxR);
	// ���������С��������Ĺ����淨
	BOOL GetRootsetGinv(CMatrix& mtxResult, CMatrix& mtxAP, CMatrix& mtxU, CMatrix& mtxV, double eps = 0.000001);
	// ��̬����������
	BOOL GetRootsetMorbid(CMatrix& mtxResult, int nMaxIt = 60, double eps = 0.000001);

	// ���������ݳ�Ա
protected:
	CMatrix	m_mtxCoef;		// ϵ������
	CMatrix m_mtxConst;		// ��������

};

#endif // !defined(AFX_LEQUATIONS_H__89A63160_719C_440D_9DFC_953F79BD4C4D__INCLUDED_)
