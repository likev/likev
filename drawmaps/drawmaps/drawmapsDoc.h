// drawmapsDoc.h : CdrawmapsDoc 类的接口
//


#pragma once

#include "county-border.h"
#include "string-trans.h"

#define WM_READOVER WM_USER+2
class CdrawmapsDoc : public CDocument
{
protected: // 仅从序列化创建
	CdrawmapsDoc();
	DECLARE_DYNCREATE(CdrawmapsDoc)

// 属性
public:

	std::string nowfile;
	volatile bool redraw;

	std::vector<county_border> borders;
	void read_border_data(std::string filename);
private:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CdrawmapsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	
};


