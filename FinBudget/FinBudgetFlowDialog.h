#pragma once
#include "FinBudgetDebtManager.h"
#include "FinBudgetFlowManager.h"

// FinBudgetFlowDialog 对话框

class FinBudgetFlowDialog : public CDialogEx
{
	DECLARE_DYNAMIC(FinBudgetFlowDialog)
	FinBudgetDebtManager* pFBD = NULL;
	FinBudgetFlowManager* pFBF = NULL;

public:
	FinBudgetFlowDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~FinBudgetFlowDialog();
	void DebtManager(FinBudgetDebtManager* _pFBD);
	void FlowManager(FinBudgetFlowManager* _pFBF);
	void Clear();
	CString getTime();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FLOWADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_FLOW_BUTTON_DELETE;
	CButton m_FLOW_BUTTON_OK;
	CButton m_FLOW_BUTTON_SEARCH;
//	int m_flowDlgId;
	int m_flowDlgType;
	int m_flowDlgId;
	CString m_flowDlgRemark;
	CString m_flowDlgRId;
	CString m_flowDlgTime;
	CString m_flowDlgValue;
	CEdit m_FLOW_ID_EDIT;
	CEdit m_FLOW_REMARK_EDIT;
	CEdit m_FLOW_rID_EDIT;
	CEdit m_FLOW_TIME_EDIT;
	CEdit m_FLOW_VALUE_EDIT;
	afx_msg void OnBnClickedButtonFlowOk();
	CEdit m_FLOW_EDIT_ALERT;
	afx_msg void OnBnClickedButtonFlowSearch();
	afx_msg void OnBnClickedButtonFlowDelete();
	afx_msg void OnEnChangeFlowIdEdit();
	afx_msg void OnBnClickedFlowRadioExpence();
	afx_msg void OnBnClickedFlowRadioGain();
	afx_msg void OnBnClickedFlowRadioInvest();
	afx_msg void OnBnClickedFlowRadioRepay();
};
