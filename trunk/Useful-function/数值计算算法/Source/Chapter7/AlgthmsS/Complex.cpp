//////////////////////////////////////////////////////////////////////
// Complex.h
//
// ������������ CComplex ��ʵ�ִ���
//
// �ܳ�������, 2002/8
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Complex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// �������캯��
//////////////////////////////////////////////////////////////////////
CComplex::CComplex() 
{
	m_dblX = 0.0;
	m_dblY = 0.0;
}

//////////////////////////////////////////////////////////////////////
// ָ��ֵ���캯��
//
// ������
// 1. double dblX - ָ����ʵ��
// 2. double dblY - ָ�����鲿
//////////////////////////////////////////////////////////////////////
CComplex::CComplex(double dblX, double dblY)
{
	m_dblX = dblX;
	m_dblY = dblY;
}

//////////////////////////////////////////////////////////////////////
// �������캯��
//
// ������
// 1. const CComplex& other - Դ����
//////////////////////////////////////////////////////////////////////
CComplex::CComplex(const CComplex& other)
{
	m_dblX = other.m_dblX;
	m_dblY = other.m_dblY;
}

//////////////////////////////////////////////////////////////////////
// ָ��������ʵ��
//
// ������
// 1. double dblX - ������ʵ��
//////////////////////////////////////////////////////////////////////
void CComplex::SetReal(double dblX)
{
	m_dblX = dblX;
}

//////////////////////////////////////////////////////////////////////
// ָ���������鲿
//
// ������
// 1. double dblX - �������鲿
//////////////////////////////////////////////////////////////////////
void CComplex::SetImag(double dblY)
{
	m_dblY = dblY;
}

//////////////////////////////////////////////////////////////////////
// ȡ������ʵ��
//
// ������  ��
//
// ����ֵ��double �ͣ�������ʵ��
//////////////////////////////////////////////////////////////////////
double CComplex::GetReal()
{
	return m_dblX;
}

//////////////////////////////////////////////////////////////////////
// ȡ�������鲿
//
// ������  ��
//
// ����ֵ��double �ͣ��������鲿
//////////////////////////////////////////////////////////////////////
double CComplex::GetImag()
{
	return m_dblY;
}

//////////////////////////////////////////////////////////////////////
// ������ת��Ϊ"a+bj"��ʽ���ַ���
//
// ������  ��
//
// ����ֵ��CString ����"a+bj"��ʽ���ַ���
//////////////////////////////////////////////////////////////////////
CString CComplex::ToString() const
{
	CString s;
	if (m_dblX != 0.0)
	{
		if (m_dblY > 0)
			s.Format("%f + %fj", m_dblX, m_dblY);
		else if (m_dblY < 0)
			s.Format("%f - %fj", m_dblX, fabs(m_dblY));
		else
			s.Format("%f", m_dblX);
	}
	else
	{
		if (m_dblY > 0)
			s.Format("%fj", m_dblY);
		else if (m_dblY < 0)
			s.Format("-%fj", fabs(m_dblY));
		else
			s.Format("%f", m_dblX);
	}

	return s;
}

//////////////////////////////////////////////////////////////////////
// ��"a,b"��ʽ���ַ���ת��Ϊ��������aΪ������ʵ����bΪ�������鲿
//
// ������
// 1. CString s - "a,b"��ʽ���ַ�����aΪ������ʵ����bΪ�������鲿
// 2. const CString& sDelim - a, b֮��ķָ�����Ĭ��Ϊ�ո�
//
// ����ֵ����
//////////////////////////////////////////////////////////////////////
void CComplex::FromString(CString s, const CString& sDelim /*= " "*/)
{
	int nPos = s.Find(sDelim);
	if (nPos == -1)
	{
		s.TrimLeft();
		s.TrimRight();
		m_dblX = atof(s);
		m_dblY = 0;
	}
	else
	{
		int nLen = s.GetLength();
		CString sLeft = s.Left(nPos);
		CString sRight = s.Right(nLen - nPos - 1);
		sLeft.TrimLeft();
		sRight.TrimRight();
		m_dblX = atof(sLeft);
		m_dblY = atof(sRight);
	}
}

//////////////////////////////////////////////////////////////////////
// ���������==���Ƚ����������Ƿ����
//
// ������
// 1. const CComplex& cpxX - ���ڱȽϵĸ���
//
// ����ֵ��BOOL�ͣ������ΪTRUE������ΪFALSE
//////////////////////////////////////////////////////////////////////
BOOL CComplex::operator==(const CComplex& cpxX) const
{
	return (m_dblX == cpxX.m_dblX && m_dblY == cpxX.m_dblY); 
}

//////////////////////////////////////////////////////////////////////
// ���������!=���Ƚ����������Ƿ񲻵�
//
// ������
// 1. const CComplex& cpxX - ���ڱȽϵĸ���
//
// ����ֵ��BOOL�ͣ��������ΪTRUE�����ΪFALSE
//////////////////////////////////////////////////////////////////////
BOOL CComplex::operator!=(const CComplex& cpxX) const
{
	return (m_dblX != cpxX.m_dblX || m_dblY != cpxX.m_dblY); 
}

//////////////////////////////////////////////////////////////////////
// ���������=����������ֵ
//
// ������
// 1. const CComplex& cpxX - ���ڸ�������ֵ��Դ����
//
// ����ֵ��CComplex�͵����ã������õĸ�����cpxX���
//////////////////////////////////////////////////////////////////////
CComplex& CComplex::operator=(const CComplex& cpxX)
{
	m_dblX = cpxX.m_dblX;
	m_dblY = cpxX.m_dblY;

	return *this;
}

//////////////////////////////////////////////////////////////////////
// ���������+��ʵ�ָ����ļӷ�
//
// ������
// 1. const CComplex& cpxX - ��ָ��������ӵĸ���
//
// ����ֵ��CComplex�ͣ�ָ��������cpxX���֮��
//////////////////////////////////////////////////////////////////////
CComplex CComplex::operator+(const CComplex& cpxX) const
{
	double x = m_dblX + cpxX.m_dblX;
	double y = m_dblY + cpxX.m_dblY;

	return CComplex(x, y);
}

//////////////////////////////////////////////////////////////////////
// ���������-��ʵ�ָ����ļ���
//
// ������
// 1. const CComplex& cpxX - ��ָ����������ĸ���
//
// ����ֵ��CComplex�ͣ�ָ��������ȥcpxX֮��
//////////////////////////////////////////////////////////////////////
CComplex CComplex::operator-(const CComplex& cpxX) const
{
	double x = m_dblX - cpxX.m_dblX;
	double y = m_dblY - cpxX.m_dblY;

	return CComplex(x, y);
}

//////////////////////////////////////////////////////////////////////
// ���������*��ʵ�ָ����ĳ˷�
//
// ������
// 1. const CComplex& cpxX - ��ָ��������˵ĸ���
//
// ����ֵ��CComplex�ͣ�ָ��������cpxX���֮��
//////////////////////////////////////////////////////////////////////
CComplex CComplex::operator*(const CComplex& cpxX) const
{
    double x = m_dblX * cpxX.m_dblX - m_dblY * cpxX.m_dblY;
    double y = m_dblX * cpxX.m_dblY + m_dblY * cpxX.m_dblX;

	return CComplex(x, y);
}

//////////////////////////////////////////////////////////////////////
// ���������/��ʵ�ָ����ĳ���
//
// ������
// 1. const CComplex& cpxX - ��ָ����������ĸ���
//
// ����ֵ��CComplex�ͣ�ָ����������cpxX֮��
//////////////////////////////////////////////////////////////////////
CComplex CComplex::operator/(const CComplex& cpxX) const
{
    double e, f, x, y;
    
    if (fabs(cpxX.m_dblX) >= fabs(cpxX.m_dblY))
	{
        e = cpxX.m_dblY / cpxX.m_dblX;
        f = cpxX.m_dblX + e * cpxX.m_dblY;
        
        x = (m_dblX + m_dblY * e) / f;
        y = (m_dblY - m_dblX * e) / f;
	}
    else
    {
		e = cpxX.m_dblX / cpxX.m_dblY;
        f = cpxX.m_dblY + e * cpxX.m_dblX;
        
        x = (m_dblX * e + m_dblY) / f;
        y = (m_dblY * e - m_dblX) / f;
    }

	return CComplex(x, y);
}

//////////////////////////////////////////////////////////////////////
// ���㸴����ģ
//
// ��������
//
// ����ֵ��double�ͣ�ָ��������ģ
//////////////////////////////////////////////////////////////////////
double CComplex::Abs() const
{
    // ��ȡʵ�����鲿�ľ���ֵ
    double x = fabs(m_dblX);
    double y = fabs(m_dblY);

    if (m_dblX == 0)
		return y;
    if (m_dblY == 0)
		return x;
    
    
    // ����ģ
    if (x > y)
        return (x * sqrt(1 + (y / x) * (y / x)));
    
    return (y * sqrt(1 + (x / y) * (x / y)));
}

//////////////////////////////////////////////////////////////////////
// ���㸴���ĸ�
//
// ������
// 1. int n - ������ĸ���
// 2. CComplex cpxR[] - CComplex�����飬����Ϊn�����ظ��������и�
//
// ����ֵ����
//////////////////////////////////////////////////////////////////////
void CComplex::Root(int n, CComplex cpxR[]) const
{
	if (n<1) 
		return;
    
	double q = atan2(m_dblY, m_dblX);
    double r = sqrt(m_dblX*m_dblX + m_dblY*m_dblY);
    if (r != 0)
    { 
		r = (1.0/n)*log(r);
		r = exp(r);
	}

    for (int k=0; k<=n-1; k++)
    { 
		double t = (2.0*k*3.1415926+q)/n;
        cpxR[k].m_dblX = r*cos(t); 
		cpxR[k].m_dblY = r*sin(t);
    }
}

//////////////////////////////////////////////////////////////////////
// ���㸴����ʵ��ָ��
//
// ������
// 1. double dblW - ����ʵ��ָ�����ݴ�
//
// ����ֵ��CComplex�ͣ�������ʵ��ָ��ֵ
//////////////////////////////////////////////////////////////////////
CComplex CComplex::Pow(double dblW) const
{
	// ����
	const double PI = 3.14159265358979;

	// �ֲ�����
	double r, t;
    
    // ����ֵ����
    if ((m_dblX == 0) && (m_dblY == 0))
		return CComplex(0, 0);
    
    // �����㹫ʽ�е����Ǻ�������
    if (m_dblX == 0)
	{
        if (m_dblY > 0)
            t = 1.5707963268;
        else
            t = -1.5707963268;
	}
    else
	{
        if (m_dblX > 0)
            t = atan2(m_dblY, m_dblX);
        else
        {
			if (m_dblY >= 0)
                t = atan2(m_dblY, m_dblX) + PI;
            else
                t = atan2(m_dblY, m_dblX) - PI;
		}
    }
    
    // ģ����
    r = exp(dblW * log(sqrt(m_dblX * m_dblX + m_dblY * m_dblY)));
    
    // ������ʵ��ָ��
    return CComplex(r * cos(dblW * t), r * sin(dblW * t));
}

//////////////////////////////////////////////////////////////////////
// ���㸴���ĸ���ָ��
//
// ������
// 1. CComplex cpxW - ������ָ�����ݴ�
// 2. int n - ���Ʋ�����Ĭ��ֵΪ0����n=0ʱ����õĽ��Ϊ����ָ������ֵ��
//
// ����ֵ��CComplex�ͣ������ĸ���ָ��ֵ
//////////////////////////////////////////////////////////////////////
CComplex CComplex::Pow(CComplex cpxW, int n /*= 0*/) const
{
	// ����
	const double PI = 3.14159265358979;
	// �ֲ�����
    double r, s, u, v;
    
    // ����ֵ����
    if (m_dblX == 0)
	{
        if (m_dblY == 0)
			return CComplex(0, 0);
            
        s = 1.5707963268 * (fabs(m_dblY) / m_dblY + 4 * n);
	}
    else
	{
        s = 2 * PI * n + atan2(m_dblY, m_dblX);
        
        if (m_dblX < 0)
		{
            if (m_dblY > 0)
                s = s + PI;
            else
                s = s - PI;
        }
    }
    
    // �������㹫ʽ
    r = 0.5 * log(m_dblX * m_dblX + m_dblY * m_dblY);
    v = cpxW.m_dblX * r + cpxW.m_dblY * s;
    u = exp(cpxW.m_dblX * r - cpxW.m_dblY * s);

    return CComplex(u * cos(v), u * sin(v));
}

//////////////////////////////////////////////////////////////////////
// ���㸴������Ȼ����
//
// ��������
//
// ����ֵ��CComplex�ͣ���������Ȼ����ֵ
//////////////////////////////////////////////////////////////////////
CComplex CComplex::Log() const
{
	double p = log(sqrt(m_dblX*m_dblX + m_dblY*m_dblY));
    return CComplex(p, atan2(m_dblY, m_dblX));
}

//////////////////////////////////////////////////////////////////////
// ���㸴��������
//
// ��������
//
// ����ֵ��CComplex�ͣ�����������ֵ
//////////////////////////////////////////////////////////////////////
CComplex CComplex::Sin() const
{
    int i;
    double x, y, y1, br, b1, b2, c[6];
    
    // �б�ѩ��ʽ�ĳ���ϵ��
    c[0] = 1.13031820798497;
    c[1] = 0.04433684984866;
    c[2] = 0.00054292631191;
    c[3] = 0.00000319843646;
    c[4] = 0.00000001103607;
    c[5] = 0.00000000002498;
    
    y1 = exp(m_dblY);
    x = 0.5 * (y1 + 1 / y1);
    if (fabs(m_dblY) >= 1)
        y = 0.5 * (y1 - 1 / y1);
    else
    {
		b1 = 0;
        b2 = 0;
        y1 = 2 * (2 * m_dblY * m_dblY - 1);
        for (i = 5; i >=0; --i)
		{
            br = y1 * b1 - b2 - c[i];
            if (i != 0)
			{
                b2 = b1;
                b1 = br;
            }
        }
        
        y = m_dblY * (br - b1);
    }
    
    // ��ϼ�����
    x = x * sin(m_dblX);
    y = y * cos(m_dblX);

	return CComplex(x, y);
}

//////////////////////////////////////////////////////////////////////
// ���㸴��������
//
// ��������
//
// ����ֵ��CComplex�ͣ�����������ֵ
//////////////////////////////////////////////////////////////////////
CComplex CComplex::Cos() const
{
    int i;
    double x, y, y1, br, b1, b2, c[6];
    
    // �б�ѩ��ʽ�ĳ���ϵ��
    c[0] = 1.13031820798497;
    c[1] = 0.04433684984866;
    c[2] = 0.00054292631191;
    c[3] = 0.00000319843646;
    c[4] = 0.00000001103607;
    c[5] = 0.00000000002498;
    
    y1 = exp(m_dblY);
    x = 0.5 * (y1 + 1 / y1);
    if (fabs(m_dblY) >= 1)
        y = 0.5 * (y1 - 1 / y1);
    else
    {
		b1 = 0;
        b2 = 0;
        y1 = 2 * (2 * m_dblY * m_dblY - 1);
        for (i=5 ; i>=0; --i)
		{
            br = y1 * b1 - b2 - c[i];
            if (i != 0)
            {
				b2 = b1;
                b1 = br;
            }
        }
        
        y = m_dblY * (br - b1);
    }
    
    // ��ϼ�����
    x = x * cos(m_dblX);
	y = -y * sin(m_dblX);

	return CComplex(x, y);
}

//////////////////////////////////////////////////////////////////////
// ���㸴��������
//
// ��������
//
// ����ֵ��CComplex�ͣ�����������ֵ
//////////////////////////////////////////////////////////////////////
CComplex CComplex::Tan() const
{
	return Sin()/Cos();
}

