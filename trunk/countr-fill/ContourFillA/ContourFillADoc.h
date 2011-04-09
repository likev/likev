// ContourFillADoc.h : CContourFillADoc 类的接口
//


#pragma once

#include "contour_fill.h"

class CContourFillADoc : public CDocument
{
protected: // 仅从序列化创建
	CContourFillADoc();
	DECLARE_DYNCREATE(CContourFillADoc)

// 属性
public:
	contour_fill::contr_set_type lines;
	std::vector<contour_fill::contr_set_type> contr_set_type;

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CContourFillADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


