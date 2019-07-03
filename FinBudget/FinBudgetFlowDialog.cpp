// FinBudgetFlowDialog.cpp: 实现文件
//

#include "pch.h"
#include "FinBudget.h"
#include "FinBudgetFlowDialog.h"
#include "afxdialogex.h"


// FinBudgetFlowDialog 对话框

IMPLEMENT_DYNAMIC(FinBudgetFlowDialog, CDialogEx)

FinBudgetFlowDialog::FinBudgetFlowDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FLOWADMIN, pParent)
	, m_flowDlgId(0)
	, m_flowDlgType(0)
	, m_flowDlgRemark(_T(""))
	, m_flowDlgRId(_T(""))
	, m_flowDlgTime(_T(""))
	, m_flowDlgValue(_T(""))
{

}

FinBudgetFlowDialog::~FinBudgetFlowDialog()
{
}

void FinBudgetFlowDialog::DebtManager(FinBudgetDebtManager* _pFBD)
{
	this->pFBD = _pFBD;
}

void FinBudgetFlowDialog::FlowManager(FinBudgetFlowManager* _pFBF)
{
	this->pFBF = _pFBF;
}

void FinBudgetFlowDialog::Clear()
{
	GetDlgItem(IDC_FLOW_rID_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_FLOW_REMARK_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_FLOW_VALUE_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_FLOW_TIME_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_FLOW_ID_EDIT)->SetWindowText(_T(""));
	GetDlgItem(ID_BUTTON_FLOW_DELETE)->EnableWindow(FALSE);
}


CString FinBudgetFlowDialog::getTime()
{
	CString _tmpStr;
	GetDlgItem(IDC_FLOW_TIME_EDIT)->GetWindowText(_tmpStr);
	if (_tmpStr == CString("")) {
		time_t timep;
		time(&timep);
		return DateTimeToString(timep);
	}
	else {
		return _tmpStr;
	}
}

void FinBudgetFlowDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_BUTTON_FLOW_DELETE, m_FLOW_BUTTON_DELETE);
	DDX_Control(pDX, ID_BUTTON_FLOW_OK, m_FLOW_BUTTON_OK);
	DDX_Control(pDX, ID_BUTTON_FLOW_SEARCH, m_FLOW_BUTTON_SEARCH);
	DDX_Radio(pDX, IDC_FLOW_RADIO_INVEST, m_flowDlgType);
	DDX_Text(pDX, IDC_FLOW_ID_EDIT, m_flowDlgId);
	DDX_Text(pDX, IDC_FLOW_REMARK_EDIT, m_flowDlgRemark);
	DDX_Text(pDX, IDC_FLOW_rID_EDIT, m_flowDlgRId);
	DDX_Text(pDX, IDC_FLOW_TIME_EDIT, m_flowDlgTime);
	DDX_Text(pDX, IDC_FLOW_VALUE_EDIT, m_flowDlgValue);
	DDX_Control(pDX, IDC_FLOW_ID_EDIT, m_FLOW_ID_EDIT);
	DDX_Control(pDX, IDC_FLOW_REMARK_EDIT, m_FLOW_REMARK_EDIT);
	DDX_Control(pDX, IDC_FLOW_rID_EDIT, m_FLOW_rID_EDIT);
	DDX_Control(pDX, IDC_FLOW_TIME_EDIT, m_FLOW_TIME_EDIT);
	DDX_Control(pDX, IDC_FLOW_VALUE_EDIT, m_FLOW_VALUE_EDIT);
	DDX_Control(pDX, IDC_EDIT2, m_FLOW_EDIT_ALERT);
}


BEGIN_MESSAGE_MAP(FinBudgetFlowDialog, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON_FLOW_OK, &FinBudgetFlowDialog::OnBnClickedButtonFlowOk)
	ON_BN_CLICKED(ID_BUTTON_FLOW_SEARCH, &FinBudgetFlowDialog::OnBnClickedButtonFlowSearch)
	ON_BN_CLICKED(ID_BUTTON_FLOW_DELETE, &FinBudgetFlowDialog::OnBnClickedButtonFlowDelete)
	ON_EN_CHANGE(IDC_FLOW_ID_EDIT, &FinBudgetFlowDialog::OnEnChangeFlowIdEdit)
	ON_BN_CLICKED(IDC_FLOW_RADIO_EXPENCE, &FinBudgetFlowDialog::OnBnClickedFlowRadioExpence)
	ON_BN_CLICKED(IDC_FLOW_RADIO_GAIN, &FinBudgetFlowDialog::OnBnClickedFlowRadioGain)
	ON_BN_CLICKED(IDC_FLOW_RADIO_INVEST, &FinBudgetFlowDialog::OnBnClickedFlowRadioInvest)
	ON_BN_CLICKED(IDC_FLOW_RADIO_REPAY, &FinBudgetFlowDialog::OnBnClickedFlowRadioRepay)
END_MESSAGE_MAP()


// FinBudgetFlowDialog 消息处理程序


void FinBudgetFlowDialog::OnBnClickedButtonFlowOk()
{
	UpdateData(TRUE);
	try {
		FinBudgetFlow* t_pFBF = this->pFBF->R(m_flowDlgId);
		t_pFBF->setRemark(m_flowDlgRemark);
		t_pFBF->setValue(_toDouble(m_flowDlgValue));
		t_pFBF->setTime(StringToDateTime(CStringToCharArray(getTime())));
		m_FLOW_EDIT_ALERT.SetWindowText(_T("修改成功"));
	}
	catch (int) {
		if (m_flowDlgType == Invest || m_flowDlgType == Repay) {
			if (m_flowDlgRId != "") {
				try {
					DebtType _dType = this->pFBD->R(atoi(CStringToCharArray(m_flowDlgRId)))->getType();
					if ((m_flowDlgType == Invest && _dType == Finance) || (m_flowDlgType == Repay && _dType == Debt)) {
						//操作
						int nId = this->pFBF->C(_toDouble(m_flowDlgValue),
							StringToDateTime(CStringToCharArray(getTime())),
							m_flowDlgRemark,
							(FlowType)m_flowDlgType);
						this->pFBF->R(nId)->setRId(atoi(CStringToCharArray(m_flowDlgRId)));
					}
					else {
						m_FLOW_EDIT_ALERT.SetWindowText(_T("操作失败"));
						MessageBox(TEXT("关联ID对等类型错误"), TEXT("异常"), MB_OK);
					}
				}
				catch (int) {
					MessageBox(TEXT("关联ID不存在"), TEXT("异常"), MB_OK);
					m_FLOW_EDIT_ALERT.SetWindowText(_T("操作失败"));
				}
				
			}
			else {
				MessageBox(TEXT("必须设定关联ID"), TEXT("异常"), MB_OK);
				m_FLOW_EDIT_ALERT.SetWindowText(_T("操作失败"));
			}
			
		}
		else if (m_flowDlgType == Expance || m_flowDlgType == Gain) {
			int nId = this->pFBF->C(_toDouble(m_flowDlgValue),
				StringToDateTime(CStringToCharArray(getTime())),
				m_flowDlgRemark,
				(FlowType)m_flowDlgType);
			this->pFBF->R(nId)->setRId(-1);
			m_FLOW_EDIT_ALERT.SetWindowText(_T("添加成功"));
		}
	}
	UpdateData(FALSE);
}


void FinBudgetFlowDialog::OnBnClickedButtonFlowSearch()
{
	UpdateData(TRUE);
	try {
		FinBudgetFlow* t_pFBF = this->pFBF->R(m_flowDlgId);
		m_flowDlgValue = _toCString(t_pFBF->getValue());
		m_flowDlgTime = DateTimeToString(t_pFBF->getTime());
		m_flowDlgType = t_pFBF->getType();
		m_flowDlgRemark = t_pFBF->getRemark();
		if (t_pFBF->getRId() == -1) {
			m_flowDlgRId = "";
		}
		else {
			m_flowDlgRId = _toCString(t_pFBF->getRId());
		}
		m_FLOW_BUTTON_OK.SetWindowText(_T("修改"));
		m_FLOW_EDIT_ALERT.SetWindowText(_T("搜索成功"));
	}
	catch (int) {
		m_flowDlgValue = "";
		m_flowDlgTime = "";
		m_flowDlgType = NULL;
		m_flowDlgRemark = "";
		m_FLOW_BUTTON_OK.SetWindowText(_T("添加"));
		m_FLOW_EDIT_ALERT.SetWindowText(_T(""));
		//MessageBox(TEXT("所查ID不存在"), TEXT("异常"), MB_OK);
	}
	UpdateData(FALSE);
}


void FinBudgetFlowDialog::OnBnClickedButtonFlowDelete()
{
	UpdateData(TRUE);
	try {
		this->pFBF->D(m_flowDlgId);
		m_flowDlgValue = "";
		m_flowDlgTime = "";
		m_flowDlgType = NULL;
		m_flowDlgRemark = "";
	}
	catch (int) {
		MessageBox(TEXT("ID不存在"), TEXT("异常"), MB_OK);
	}
	UpdateData(FALSE);
}


void FinBudgetFlowDialog::OnEnChangeFlowIdEdit()
{
	UpdateData(TRUE);
	CString ID_Str;
	m_FLOW_ID_EDIT.GetWindowText(ID_Str);
	if (ID_Str.SpanIncluding(_T("0123456789")) == ID_Str && ID_Str != "") {
		m_FLOW_BUTTON_SEARCH.EnableWindow(TRUE);
		OnBnClickedButtonFlowSearch();
		m_FLOW_BUTTON_OK.EnableWindow(TRUE);
		m_FLOW_BUTTON_DELETE.EnableWindow(TRUE);
	}
	else {
		m_flowDlgValue = "";
		m_flowDlgTime = "";
		m_flowDlgType = NULL;
		m_flowDlgRemark = "";
		m_FLOW_BUTTON_SEARCH.EnableWindow(FALSE);
		m_FLOW_BUTTON_OK.EnableWindow(FALSE);
		m_FLOW_BUTTON_DELETE.EnableWindow(FALSE);
	}
}


void FinBudgetFlowDialog::OnBnClickedFlowRadioExpence()
{
	m_FLOW_rID_EDIT.SetReadOnly(TRUE);
	m_FLOW_rID_EDIT.SetWindowText(_T(""));
}


void FinBudgetFlowDialog::OnBnClickedFlowRadioGain()
{
	m_FLOW_rID_EDIT.SetReadOnly(TRUE);
	m_FLOW_rID_EDIT.SetWindowText(_T(""));
}


void FinBudgetFlowDialog::OnBnClickedFlowRadioInvest()
{
	m_FLOW_rID_EDIT.SetReadOnly(FALSE);
	m_FLOW_rID_EDIT.SetWindowText(_T(""));
}


void FinBudgetFlowDialog::OnBnClickedFlowRadioRepay()
{
	m_FLOW_rID_EDIT.SetReadOnly(FALSE);
	m_FLOW_rID_EDIT.SetWindowText(_T(""));
}
