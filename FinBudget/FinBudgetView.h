
// FinBudgetView.h: CFinBudgetView 类的接口
//

#pragma once
#include "FinBudgetDebtManager.h"
#include "FinBudgetFlowManager.h"
#include "FinBudgetSupport.h"

class CFinBudgetView : public CFormView
{
protected: // 仅从序列化创建
	CFinBudgetView() noexcept;
	DECLARE_DYNCREATE(CFinBudgetView)


public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_FINBUDGET_FORM };
#endif

// 特性
public:
	CFinBudgetDoc* GetDocument() const;

// 操作
public:
	afx_msg void OnBnClickedButtonDebtAdmin();
	afx_msg void OnBnClickedButtonDebtReport();
	afx_msg void OnBnClickedButtonFlowAdmin();
	afx_msg void OnBnClickedButtonFlowReport();
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CFinBudgetView();
	FinBudgetDebtManager FDM;
	FinBudgetFlowManager FFM;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
//	CListCtrl m_mian_list;
//	CListCtrl m_main_list;
	CListCtrl m_MAIN_LIST;
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void On32782();
	afx_msg void OnFileNew();
};

#ifndef _DEBUG  // FinBudgetView.cpp 中的调试版本
inline CFinBudgetDoc* CFinBudgetView::GetDocument() const
   { return reinterpret_cast<CFinBudgetDoc*>(m_pDocument); }
#endif

