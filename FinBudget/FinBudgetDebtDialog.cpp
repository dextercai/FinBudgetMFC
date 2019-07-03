// FinBudgetDebtDialog.cpp: 实现文件
//

#include "pch.h"
#include "FinBudget.h"
#include "FinBudgetDebtDialog.h"
#include "afxdialogex.h"


// FinBudgetDebtDialog 对话框

IMPLEMENT_DYNAMIC(FinBudgetDebtDialog, CDialogEx)

FinBudgetDebtDialog::FinBudgetDebtDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEBTADMIN, pParent)
	, m_debtDlgId(0)
	, m_debtDlgValue(_T(""))
	, m_debtDlgTime(_T(""))
	, m_debtDlgRange(_T(""))
	, m_debtDlgRemark(_T(""))
	, m_debtDlgRate(_T(""))
	, m_debtDlgCycle(0)
	, m_debtDlgType(0)
{

}

FinBudgetDebtDialog::~FinBudgetDebtDialog()
{
}

void FinBudgetDebtDialog::DebtManager(FinBudgetDebtManager* _pFBD)
{
	this->pFBD = _pFBD;

}

void FinBudgetDebtDialog::FlowManager(FinBudgetFlowManager* _pFBM)
{
	this->pFBM = _pFBM;
}

void FinBudgetDebtDialog::Clear()
{
	GetDlgItem(IDC_DEBT_REMARK_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEBT_TIME_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEBT_RANGE_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEBT_RATE_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEBT_VALUE_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_DEBT_ID_EDIT)->SetWindowText(_T(""));
	GetDlgItem(ID_BUTTON_DEBT_DELETE)->EnableWindow(FALSE);
}

CString FinBudgetDebtDialog::getTime()
{
	CString _tmpStr;
	GetDlgItem(IDC_DEBT_TIME_EDIT)->GetWindowText(_tmpStr);
	if (_tmpStr == CString("")) {
		time_t timep;
		time(&timep);
		return DateTimeToString(timep);
	}
	else {
		return _tmpStr;
	}
}

void FinBudgetDebtDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DEBT_ID_EDIT, m_debtDlgId);
	DDV_MinMaxInt(pDX, m_debtDlgId, 0, INT_MAX);
	DDX_Control(pDX, IDC_DEBT_VALUE_EDIT, m_DEBT_VALUE_EDIT);
	DDX_Text(pDX, IDC_DEBT_VALUE_EDIT, m_debtDlgValue);
	DDX_Text(pDX, IDC_DEBT_TIME_EDIT, m_debtDlgTime);
	DDX_Control(pDX, IDC_DEBT_TIME_EDIT, m_DEBT_TIME_EDIT);
	DDX_Control(pDX, IDC_DEBT_ID_EDIT, m_DEBT_ID_EDIT);
	DDX_Control(pDX, IDC_DEBT_RANGE_EDIT, m_DEBT_RANGE_EDIT);
	DDX_Text(pDX, IDC_DEBT_RANGE_EDIT, m_debtDlgRange);
	DDX_Control(pDX, IDC_DEBT_REMARK_EDIT, m_DEBT_REMARK_EDIT);
	DDX_Text(pDX, IDC_DEBT_REMARK_EDIT, m_debtDlgRemark);
	DDX_Text(pDX, IDC_DEBT_RATE_EDIT, m_debtDlgRate);
	DDX_Control(pDX, IDC_DEBT_RATE_EDIT, m_DEBT_RATE_EDIT);
	DDX_Radio(pDX, IDC_DEBT_RADIO_DAY, m_debtDlgCycle);
	DDX_Control(pDX, ID_BUTTON_DEBT_SEARCH, m_DEBT_BUTTON_SEARCH);
	DDX_Control(pDX, ID_BUTTON_DEBT_DELETE, m_DEBT_BUTTON_DELETE);
	DDX_Control(pDX, ID_BUTTON_DEBT_OK, m_DEBT_BUTTON_OK);
	DDX_Control(pDX, IDC_EDIT2, m_DEBT_EDIT_ALERT);
	DDX_Radio(pDX, IDC_DEBT_RADIO_Invest, m_debtDlgType);
}


BEGIN_MESSAGE_MAP(FinBudgetDebtDialog, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON_DEBT_OK, &FinBudgetDebtDialog::OnBnClickedButtonDebtOk)
	ON_EN_CHANGE(IDC_DEBT_ID_EDIT, &FinBudgetDebtDialog::OnEnChangeDebtIdEdit)
	ON_BN_CLICKED(ID_BUTTON_DEBT_SEARCH, &FinBudgetDebtDialog::OnBnClickedButtonDebtSearch)
	ON_BN_CLICKED(ID_BUTTON_DEBT_DELETE, &FinBudgetDebtDialog::OnBnClickedButtonDebtDelete)
END_MESSAGE_MAP()


// FinBudgetDebtDialog 消息处理程序


void FinBudgetDebtDialog::OnBnClickedButtonDebtOk()
{
	UpdateData(TRUE);
	try {
		CString t_str;
		FinBudgetDebt* t_pFBD = this->pFBD->R(m_debtDlgId);
		t_pFBD->setCycle((Cycle)m_debtDlgCycle);
		t_pFBD->setRange(_toDouble(m_debtDlgRange));
		t_pFBD->setValue(_toDouble(m_debtDlgValue));
		t_pFBD->setRemark(m_debtDlgRemark);
		t_pFBD->setTime(StringToDateTime(CStringToCharArray(getTime())));
		t_pFBD->setRate(_toDouble(m_debtDlgRate));
		//t_pFBD->setType((DebtType)m_debtDlgType);
		m_DEBT_EDIT_ALERT.SetWindowText(_T("修改成功"));
	}
	catch (int) {
		int _index = this->pFBD->C(_toDouble(m_debtDlgValue),
			_toDouble(m_debtDlgRange),
			_toDouble(m_debtDlgRate),
			StringToDateTime(CStringToCharArray(getTime())),
			m_debtDlgRemark,
			(Cycle)m_debtDlgCycle,
			(DebtType)m_debtDlgType);
		if (m_debtDlgType == Finance) {
			this->pFBM->R(this->pFBM->C(_toDouble(m_debtDlgValue),
				StringToDateTime(CStringToCharArray(getTime())),
				m_debtDlgRemark + CString("投资支出"),
				Expance))->setRId(_index);
		}
		else if(m_debtDlgType == Debt){
			this->pFBM->R(this->pFBM->C(_toDouble(m_debtDlgRange),
				StringToDateTime(CStringToCharArray(getTime())),
				m_debtDlgRemark + CString("贷款获得"),
				Gain))->setRId(_index);
		}
		m_DEBT_EDIT_ALERT.SetWindowText(_T("添加成功"));
	}
	UpdateData(FALSE);
}


void FinBudgetDebtDialog::OnEnChangeDebtIdEdit()
{
	UpdateData(TRUE);
	CString ID_Str;
	m_DEBT_ID_EDIT.GetWindowText(ID_Str);
	if (ID_Str.SpanIncluding(_T("0123456789")) == ID_Str && ID_Str != "") {
		m_DEBT_BUTTON_SEARCH.EnableWindow(TRUE);
		OnBnClickedButtonDebtSearch();
		m_DEBT_BUTTON_OK.EnableWindow(TRUE);
		m_DEBT_BUTTON_DELETE.EnableWindow(TRUE);
	}
	else {
		m_debtDlgValue = "";
		m_debtDlgRate = "";
		m_debtDlgRange = "";
		m_debtDlgRemark = "";
		m_debtDlgTime = "";
		m_debtDlgCycle = NULL;
		m_debtDlgType = NULL;
		m_DEBT_BUTTON_SEARCH.EnableWindow(FALSE);
		m_DEBT_BUTTON_OK.EnableWindow(FALSE);
		m_DEBT_BUTTON_DELETE.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}


void FinBudgetDebtDialog::OnBnClickedButtonDebtSearch()
{
	UpdateData(TRUE);
	try {
		FinBudgetDebt* t_pFBD = this->pFBD->R(m_debtDlgId);
		m_debtDlgValue = _toCString(t_pFBD->getValue());
		m_debtDlgRate = _toCString(t_pFBD->getRate());
		m_debtDlgRange = _toCString(t_pFBD->getRange());
		m_debtDlgRemark = t_pFBD->getRemark();
		m_debtDlgTime = DateTimeToString(t_pFBD->getTime());
		m_debtDlgCycle = t_pFBD->getCycle();
		m_debtDlgType = t_pFBD->getType();
		m_DEBT_BUTTON_OK.SetWindowText(_T("修改"));
		m_DEBT_EDIT_ALERT.SetWindowText(_T("搜索成功"));
	}
	catch (int) {
		m_debtDlgValue = "";
		m_debtDlgRate = "";
		m_debtDlgRange = "";
		m_debtDlgRemark = "";
		m_debtDlgTime = "";
		m_debtDlgCycle = NULL;
		m_debtDlgType = NULL;
		m_DEBT_BUTTON_OK.SetWindowText(_T("添加"));
		m_DEBT_EDIT_ALERT.SetWindowText(_T(""));
		//MessageBox(TEXT("所查ID不存在"), TEXT("异常"), MB_OK);
	}
	UpdateData(FALSE);
	
}


void FinBudgetDebtDialog::OnBnClickedButtonDebtDelete()
{
	UpdateData(TRUE);
	try {
		this->pFBD->D(m_debtDlgId);
		std::map<int, FinBudgetFlow*>::iterator it;
		it = this->pFBM->FlowMap.begin();

		while (it != this->pFBM->FlowMap.end())
		{
			if (it->second->getRId() == m_debtDlgId) {
				this->pFBM->FlowMap.erase(it++);
			}
			else {
				it++;
			}
		}
		m_debtDlgValue = "";
		m_debtDlgRate = "";
		m_debtDlgRange = "";
		m_debtDlgRemark = "";
		m_debtDlgTime = "";
		m_debtDlgCycle = NULL;
		m_debtDlgType = NULL;
	}
	catch (int) {
		MessageBox(TEXT("ID不存在"), TEXT("异常"), MB_OK);
	}
	UpdateData(FALSE);
}
