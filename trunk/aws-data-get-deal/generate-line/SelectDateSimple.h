#pragma once


// SelectDateSimple �Ի���

class SelectDateSimple : public CDialog
{
	DECLARE_DYNAMIC(SelectDateSimple)

public:
	SelectDateSimple(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectDateSimple();

// �Ի�������
	enum { IDD = IDD_SELECT_DATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ѡ�������
	CTime date;
};
