#pragma once
#include "FinBudgetDebtManager.h"
#include "FinBudgetFlowManager.h"

// FinBudgetDebtDialog 对话框

class FinBudgetDebtDialog : public CDialogEx
{
	DECLARE_DYNAMIC(FinBudgetDebtDialog)
	FinBudgetDebtManager* pFBD = NULL;
	FinBudgetFlowManager* pFBM = NULL;
public:
	FinBudgetDebtDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FinBudgetDebtDialog();
	void DebtManager(FinBudgetDebtManager* _pFBD);
	void FlowManager(FinBudgetFlowManager* _pFBM);
	void Clear();
	CString getTime();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEBTADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDebtOk();
	afx_msg void OnEnChangeDebtIdEdit();
	afx_msg void OnBnClickedButtonDebtSearch();
private:
	
//	CEdit m_DEBT_ID_EDIT;
	
//	CEdit m_DEBT_VALUE_EDIT;
	
public:
	afx_msg void OnBnClickedButtonDebtDelete();
	
	CEdit m_DEBT_ID_EDIT;
	CEdit m_DEBT_VALUE_EDIT;
	CEdit m_DEBT_RANGE_EDIT;
	CEdit m_DEBT_RATE_EDIT;
	CEdit m_DEBT_REMARK_EDIT;
	CEdit m_DEBT_TIME_EDIT;
	CEdit m_DEBT_EDIT_ALERT;

	CString m_debtDlgRemark;
	CString m_debtDlgRate;
	CString m_debtDlgRange;
	CString m_debtDlgTime;
	CString m_debtDlgValue;

	CButton m_DEBT_BUTTON_SEARCH;
	CButton m_DEBT_BUTTON_DELETE;
	CButton m_DEBT_BUTTON_OK;

	int m_debtDlgId;
	int m_debtDlgCycle;

	
	int m_debtDlgType;
};
