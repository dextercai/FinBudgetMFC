
// FinBudgetView.cpp: CFinBudgetView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "FinBudget.h"
#endif

#include "FinBudgetDoc.h"
#include "FinBudgetView.h"
#include "FinBudgetDebtDialog.h"
#include "FinBudgetFlowDialog.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFinBudgetView

IMPLEMENT_DYNCREATE(CFinBudgetView, CFormView)

BEGIN_MESSAGE_MAP(CFinBudgetView, CFormView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	// 菜单按钮消息映射
	ON_BN_CLICKED(ID_BUTTON_DEBTADMIN, &CFinBudgetView::OnBnClickedButtonDebtAdmin)
	ON_BN_CLICKED(ID_BUTTON_DEBTREPORT, &CFinBudgetView::OnBnClickedButtonDebtReport)
	ON_BN_CLICKED(ID_BUTTON_FLOWADMIN, &CFinBudgetView::OnBnClickedButtonFlowAdmin)
	ON_BN_CLICKED(ID_BUTTON_FLOWREPORT, &CFinBudgetView::OnBnClickedButtonFlowReport)
	ON_COMMAND(ID_FILE_SAVE, &CFinBudgetView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CFinBudgetView::OnFileOpen)
	ON_COMMAND(ID_32783, &CFinBudgetView::On32782)
	ON_COMMAND(ID_FILE_NEW, &CFinBudgetView::OnFileNew)
END_MESSAGE_MAP()

// CFinBudgetView 构造/析构

CFinBudgetView::CFinBudgetView() noexcept
	: CFormView(IDD_FINBUDGET_FORM)
{
	// TODO: 在此处添加构造代码

}

CFinBudgetView::~CFinBudgetView()
{
}

void CFinBudgetView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_MAIN_LIST, m_mian_list);
	//  DDX_Control(pDX, IDC_MAIN_LIST, m_main_list);
	DDX_Control(pDX, IDC_MAIN_LIST, m_MAIN_LIST);
}

void CFinBudgetView::OnBnClickedButtonDebtAdmin()
{
	FinBudgetDebtDialog *pDlg = new FinBudgetDebtDialog;
	pDlg->Create(IDD_DEBTADMIN, this);
	pDlg->DebtManager(&FDM);
	pDlg->FlowManager(&FFM);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->Clear();
}
void CFinBudgetView::OnBnClickedButtonFlowReport()
{
	GetDlgItem(IDC_MAIN_LIST)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MAIN_EDIT)->ShowWindow(SW_HIDE);
	m_MAIN_LIST.DeleteAllItems();
	while (m_MAIN_LIST.DeleteColumn(0));
	m_MAIN_LIST.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 35, 90);
	m_MAIN_LIST.InsertColumn(1, _T("收支类型"), LVCFMT_LEFT, 75, 90);
	m_MAIN_LIST.InsertColumn(2, _T("数额"), LVCFMT_LEFT, 80, 90);
	m_MAIN_LIST.InsertColumn(3, _T("关联ID"), LVCFMT_LEFT, 75, 90);
	m_MAIN_LIST.InsertColumn(4, _T("备注"), LVCFMT_LEFT, 100, 90);
	m_MAIN_LIST.InsertColumn(5, _T("时间"), LVCFMT_LEFT, 100, 90);
	std::map<int, FinBudgetFlow*>::iterator it;
	it = this->FFM.FlowMap.begin();
	int _iflag = 0;
	while (it != this->FFM.FlowMap.end())
	{
		m_MAIN_LIST.InsertItem(_iflag, _toCString(it->first));
		switch (it->second->getType())
		{
		case Invest:
			m_MAIN_LIST.SetItemText(_iflag, 1, _T("投资"));
			break;
		case Repay:
			m_MAIN_LIST.SetItemText(_iflag, 1, _T("还款"));
			break;
		case Expance:
			m_MAIN_LIST.SetItemText(_iflag, 1, _T("普通支出"));
			break;
		case Gain:
			m_MAIN_LIST.SetItemText(_iflag, 1, _T("普通收入"));
			break;
		default:
			break;
		}
		m_MAIN_LIST.SetItemText(_iflag, 2, _toCString(it->second->getValue()));
		if (it->second->getRId() != -1) {
			m_MAIN_LIST.SetItemText(_iflag, 3, _toCString(it->second->getValue()));
		}
		m_MAIN_LIST.SetItemText(_iflag, 4, it->second->getRemark());
		m_MAIN_LIST.SetItemText(_iflag, 5, DateTimeToString(it->second->getTime()));
		_iflag++;
		it++;
	}

}
void CFinBudgetView::OnBnClickedButtonDebtReport()
{
	GetDlgItem(IDC_MAIN_LIST)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MAIN_EDIT)->ShowWindow(SW_HIDE);

	m_MAIN_LIST.DeleteAllItems();
	while (m_MAIN_LIST.DeleteColumn(0));
	m_MAIN_LIST.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 35, 90);
	m_MAIN_LIST.InsertColumn(1, _T("债权类型"), LVCFMT_LEFT, 75, 90);
	m_MAIN_LIST.InsertColumn(2, _T("数额"), LVCFMT_LEFT, 80, 90);
	m_MAIN_LIST.InsertColumn(3, _T("已还款/取出"), LVCFMT_LEFT, 150, 90);
	m_MAIN_LIST.InsertColumn(4, _T("本息和"), LVCFMT_LEFT, 150, 90);
	m_MAIN_LIST.InsertColumn(5, _T("最后期限"), LVCFMT_LEFT, 150, 90);
	m_MAIN_LIST.InsertColumn(6, _T("备注"), LVCFMT_LEFT, 150, 90);
	m_MAIN_LIST.InsertColumn(6, _T("结清状态"), LVCFMT_LEFT, 35, 90);
	m_MAIN_LIST.InsertColumn(6, _T("时间"), LVCFMT_LEFT, 150, 90);
	std::map<int, FinBudgetDebt*>::iterator itD;
	itD = this->FDM.DebtMap.begin();
	int _iflag = 0;
	while (itD != this->FDM.DebtMap.end())
	{
		m_MAIN_LIST.InsertItem(_iflag, _toCString(itD->first));
		switch (itD->second->getType())
		{
		case Finance:
			m_MAIN_LIST.SetItemText(_iflag, 1, _T("投资"));
			break;
		case Debt:
			m_MAIN_LIST.SetItemText(_iflag, 1, _T("贷款"));
			break;
		default:
			break;
		}
		m_MAIN_LIST.SetItemText(_iflag, 2, _toCString(itD->second->getValue()));
		std::map<int, FinBudgetFlow*>::iterator itF;
		itF = this->FFM.FlowMap.begin();
		double _tmp0 = 0;
		while (itF != this->FFM.FlowMap.end()) {
			if (itF->second->getRId() == itD->first && ((itF->second->getType() == Invest && itD->second->getType() == Finance) || (itF->second->getType() == Repay && itD->second->getType() == Debt))) {
				_tmp0 += itF->second->getValue();
			}
			itF++;
		}
		m_MAIN_LIST.SetItemText(_iflag, 3, _toCString(_tmp0));

		double _tmp1 = 0;
		switch (itD->second->getType())
		{
		case Finance:
			_tmp1 = itD->second->getValue() * (1.0 + itD->second->getRate() * itD->second->getRange());
			m_MAIN_LIST.SetItemText(_iflag, 4, CString("单利和：") + _toCString(_tmp1));
			break;
		case Debt:
			_tmp1 = itD->second->getValue() * pow((1.0 + itD->second->getRate()), int(itD->second->getRange()));
			m_MAIN_LIST.SetItemText(_iflag, 4, CString("复利和：") + _toCString(_tmp1));
			break;
		default:
			break;
		}
		switch (itD->second->getCycle()) {
		case Daily:
			m_MAIN_LIST.SetItemText(_iflag, 5, DateTimeToString(itD->second->getTime() + (itD->second->getRange() * 60 * 60 * 24)));
			break;
		case Monthly:
			m_MAIN_LIST.SetItemText(_iflag, 5, DateTimeToString(itD->second->getTime() + (itD->second->getRange() * 60 * 60 * 24 * 30)));
			break;
		case Annually:
			m_MAIN_LIST.SetItemText(_iflag, 5, DateTimeToString(itD->second->getTime() + (itD->second->getRange() * 60 * 60 * 24 * 30 * 12)));
			break;
		default:
			break;
		}
		m_MAIN_LIST.SetItemText(_iflag, 6, itD->second->getRemark());
		if (_tmp0 >= _tmp1) {
			m_MAIN_LIST.SetItemText(_iflag, 7, _T("✔"));
		}
	
		m_MAIN_LIST.SetItemText(_iflag, 8, DateTimeToString(itD->second->getTime()));
		_iflag++;
		itD++;
	}


}

void CFinBudgetView::OnBnClickedButtonFlowAdmin()
{
	FinBudgetFlowDialog* pDlg = new FinBudgetFlowDialog;
	pDlg->Create(IDD_FLOWADMIN, this);
	pDlg->DebtManager(&FDM);
	pDlg->FlowManager(&FFM);
	pDlg->ShowWindow(SW_SHOW);
	pDlg->Clear();
}



BOOL CFinBudgetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CFinBudgetView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CFinBudgetView 打印

BOOL CFinBudgetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFinBudgetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFinBudgetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CFinBudgetView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 在此处添加自定义打印代码
}


// CFinBudgetView 诊断

#ifdef _DEBUG
void CFinBudgetView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFinBudgetView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFinBudgetDoc* CFinBudgetView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFinBudgetDoc)));
	return (CFinBudgetDoc*)m_pDocument;
}
#endif //_DEBUG



void CFinBudgetView::OnFileSave()
{
	if (this->FDM.getSize() > 0 || this->FFM.getSize() > 0) {
		BOOL isOpen = FALSE;		//是否打开(否则为保存)
		CString defaultDir = L"C:\\FinBudget";	//默认打开的文件路径
		CString fileName = L"Table.fbmfc";			//默认打开的文件名
		CString filter = L"FinBudget财务统计文件 (*.fbmfc)|*.fbmfc||";	//文件过虑的类型
		CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
		openFileDlg.GetOFN().lpstrInitialDir = L"C:\\FinBudget\\Table.fbmfc";
		INT_PTR result = openFileDlg.DoModal();
		CString filePath = defaultDir + "\\" + fileName;
		if (result == IDOK) {
			filePath = openFileDlg.GetPathName();
			std::ofstream OpenFile(filePath,std::ios::trunc);
			if (OpenFile.fail()) {
				MessageBox(TEXT("文件打开错误 可能被占用"), TEXT("无法保存"), MB_OK);
			}
			else {
				std::map<int, FinBudgetFlow*>::iterator itF;
				itF = this->FFM.FlowMap.begin();
				
				while (itF != this->FFM.FlowMap.end()) {
					OpenFile << "F," << itF->first << ","
						<< itF->second->getValue() << ","
						<< itF->second->getType() << ","
						<< itF->second->getTime() << ","
						<< itF->second->getRId() << ","
						<< CStringToCharArray(itF->second->getRemark()) << ",\r\n";
					itF++;
				}
				std::map<int, FinBudgetDebt*>::iterator itD;
				itD = this->FDM.DebtMap.begin();
				while (itD != this->FDM.DebtMap.end()) {
					OpenFile << "D," << itD->first << ","
						<< itD->second->getValue() << ","
						<< itD->second->getType() << ","
						<< itD->second->getCycle() << ","
						<< itD->second->getRange() << ","
						<< itD->second->getRate() << ","
						<< itD->second->getTime() << ","
						<< CStringToCharArray(itD->second->getRemark()) << ",\r\n";
					itD++;
				}
			}
		}
	}
	else {
		MessageBox(TEXT("当前未打开或未添加任何财务统计数据"), TEXT("无法保存"), MB_OK);
	}
	
}


void CFinBudgetView::OnFileOpen()
{
	if (this->FDM.getSize() != 0 || this->FFM.getSize() != 0) {
		MessageBox(TEXT("当前工作区已经包含财务统计数据,继续将覆盖。"), TEXT("提示"), MB_OK);
	}
	BOOL isOpen = TRUE;		//是否打开(否则为保存)
	CString defaultDir = L"C:\\FinBudget";	//默认打开的文件路径
	CString fileName = L"Table.fbmfc";			//默认打开的文件名
	CString filter = L"FinBudget财务统计文件 (*.fbmfc)|*.fbmfc||";	//文件过虑的类型
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"C:\\FinBudget\\Table.fbmfc";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if (result == IDOK) {
			filePath = openFileDlg.GetPathName();
			std::ifstream OpenFile(filePath);
			if (OpenFile.fail()) {
				MessageBox(TEXT("文件打开错误"), TEXT("无法打开"), MB_OK);
			}
			else {
				std::string line;
				std::vector<std::string> splitLine;
				CString _tmpCStr;
				while (std::getline(OpenFile, line)) {
					SplitString(line, splitLine, ",");
					afxDump << splitLine.size() << line.c_str() << "\r\n";
					if (splitLine.size() >= 9 ) {
						if (splitLine.at(0) == "D") {
							FinBudgetDebt* pFBD = new FinBudgetDebt();
							pFBD->setValue(atof(splitLine.at(2).c_str()));
							pFBD->setTime(atoi(splitLine.at(7).c_str()));
							_tmpCStr = splitLine.at(8).c_str();
							pFBD->setRemark(_tmpCStr);
							pFBD->setRange(atof(splitLine.at(5).c_str()));
							pFBD->setRate(atof(splitLine.at(6).c_str()));
							pFBD->setCycle((Cycle)atoi(splitLine.at(4).c_str()));
							pFBD->setType((DebtType)atoi(splitLine.at(3).c_str()));
							this->FDM.DebtMap.insert(std::map<int, FinBudgetDebt*>::value_type(atoi(splitLine.at(1).c_str()), pFBD));
						}
					}
					else if (splitLine.size() >= 7) {
						if (splitLine.at(0) == "F") {
							FinBudgetFlow* pFBD = new FinBudgetFlow();
							pFBD->setValue(atof(splitLine.at(2).c_str()));
							pFBD->setTime(atoi(splitLine.at(4).c_str()));
							_tmpCStr = splitLine.at(6).c_str();
							pFBD->setRemark(_tmpCStr);
							pFBD->setRId(atoi(splitLine.at(5).c_str()));
							pFBD->setType((FlowType)atoi(splitLine.at(3).c_str()));;
							this->FFM.FlowMap.insert(std::map<int, FinBudgetFlow*>::value_type(atoi(splitLine.at(1).c_str()), pFBD));
						}
					}
					splitLine.clear();
					continue;
				}

			}
		}
	}


void CFinBudgetView::On32782()
{
	GetDlgItem(IDC_MAIN_LIST)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MAIN_EDIT)->ShowWindow(SW_SHOW);
	double _tmpInv, _tmpRepay,_tmpExp, _tmpGain ;
	_tmpExp = _tmpGain = _tmpInv = _tmpRepay = 0.0;
	CString Result = CString("");
	std::map<int, FinBudgetFlow*>::iterator itF;
	itF = this->FFM.FlowMap.begin();
	while (itF != this->FFM.FlowMap.end()) {
		switch (itF->second->getType())
		{
		case Invest:
			_tmpInv += itF->second->getValue();
			break;
		case Expance:
			_tmpExp += itF->second->getValue();
			break;
		case Gain:
			_tmpGain += itF->second->getValue();
			break;
		case Repay:
			_tmpRepay += itF->second->getValue();
			break;
		default:
			break;
		}
		itF++;
	}
	
	double _tmpDebt, _tmpFina, _tmpDebtAll, _tmpFinaAll;
	_tmpDebt = _tmpFina = _tmpDebtAll = _tmpFinaAll = 0.0;
	std::map<int, FinBudgetDebt*>::iterator itD;
	itD = this->FDM.DebtMap.begin();
	while (itD != this->FDM.DebtMap.end()) {
		switch (itD->second->getType())
		{
		case Debt:
			_tmpDebt += itD->second->getValue();
			_tmpDebtAll = itD->second->getValue()* pow((1.0 + itD->second->getRate()), int(itD->second->getRange()));
			break;
		case Finance:
			_tmpFina += itD->second->getValue();
			_tmpFinaAll = itD->second->getValue()* (1.0 + itD->second->getRate() * itD->second->getRange());
			break;
		default:
			break;
		}
		itD++;
	}
	Result += (CString("支出：") + _toCString(_tmpExp - _tmpFina) + CString("\r\n"));
	Result += (CString("投资取出：") + _toCString(_tmpInv) + CString("\r\n"));
	Result += (CString("收入：") + _toCString(_tmpGain - _tmpDebt) + CString("\r\n"));
	Result += (CString("还款支出：") + _toCString(_tmpRepay) + CString("\r\n"));
	Result += CString("\r\n");

	Result += (CString("贷款：") + _toCString(_tmpDebt) + CString("\r\n"));
	Result += (CString("贷款本利和（复利）：") + _toCString(_tmpDebtAll) + CString("\r\n"));
	Result += (CString("投资：") + _toCString(_tmpFina) + CString("\r\n"));
	Result += (CString("投资本利和（单利）：") + _toCString(_tmpFinaAll) + CString("\r\n"));
	Result += CString("\r\n");
	Result += (CString("贷款剩余额：") + _toCString(_tmpDebtAll - _tmpRepay) + CString("\r\n"));
	Result += (CString("投资剩余额：") + _toCString(_tmpFinaAll - _tmpInv) + CString("\r\n"));

	Result += CString("\r\n");
	Result += (CString("总支出：") + _toCString(_tmpRepay + _tmpExp) + CString("\r\n"));
	Result += (CString("总收入：") + _toCString(_tmpGain + _tmpInv) + CString("\r\n"));
	Result += (CString("总值：") + _toCString(_tmpGain + _tmpInv - _tmpRepay - _tmpExp) + CString("\r\n"));

	GetDlgItem(IDC_MAIN_EDIT)->SetWindowText(Result);
}


void CFinBudgetView::OnFileNew()
{
	if (this->FDM.getSize() != 0 || this->FFM.getSize() != 0) {
		MessageBox(TEXT("当前工作区已经包含财务统计数据,请先保存。"), TEXT("提示"), MB_OK);
		OnFileSave();
	}
	this->FDM.DebtMap.clear();
	this->FFM.FlowMap.clear();
	MessageBox(TEXT("新建成功"), TEXT("提示"), MB_OK);
	// TODO: 在此添加命令处理程序代码
}
