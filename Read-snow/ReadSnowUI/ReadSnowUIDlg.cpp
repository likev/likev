// ReadSnowUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadSnowUI.h"
#include "ReadSnowUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReadSnowUIDlg �Ի���




CReadSnowUIDlg::CReadSnowUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadSnowUIDlg::IDD, pParent)
	, beginHour(_T("20ʱ"))
	, endHour(_T("20ʱ"))
	, selectRagion(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	endDay = CTime::GetCurrentTime();
	beginDay = endDay - CTimeSpan(1,0,0,0);

	InitDataFromFile();
}

void CReadSnowUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, beginHour);
	DDX_CBString(pDX, IDC_COMBO2, endHour);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, beginDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, endDay);
	DDX_Radio(pDX, IDC_RADIO1, selectRagion);
}

BEGIN_MESSAGE_MAP(CReadSnowUIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Query, &CReadSnowUIDlg::OnBnClickedButtonQuery)
END_MESSAGE_MAP()


// CReadSnowUIDlg ��Ϣ�������

BOOL CReadSnowUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CReadSnowUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CReadSnowUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReadSnowUIDlg::OnBnClickedButtonQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

	beginDay += CTimeSpan(0,getSelectHour(beginHour)-beginDay.GetHour(),0,0);
	endDay += CTimeSpan(0,getSelectHour(endHour)-endDay.GetHour(),0,0);

	if(endDay > CTime::GetCurrentTime()) endDay = CTime::GetCurrentTime();

	if(beginDay >= endDay)
	{
		this->MessageBox("ʱ�䷶Χ����������ѡ��ʱ�䣡","����",MB_OK|MB_ICONINFORMATION );
		return;
	}

	WriteDataToFile();
}

// ������д���ļ�
bool CReadSnowUIDlg::WriteDataToFile(void)
{
	std::string timestr = beginDay.Format("%Y��%#m��%#d��%Hʱ -- ")+endDay.Format("%#d��%Hʱ");
	log_to_file("ftplog.txt","��ѯʱ��Σ�"+timestr);
	
	DealSnowData dsd(beginDay, endDay );

	if(0 == selectRagion) 
	{
		log_to_file("ftplog.txt","��ѯ��������");

		dsd.SetStations(luoyangStationID);

		std::vector<CTime> timeList = dsd.GetTimeList();
		std::vector< std::vector<SnowInfo> > allStationsRecord = dsd.GetAllStationsRecord();
		std::vector<SnowInfo> accumulatedResult = dsd.GetAccumulateSnow();

		std::ofstream fout("result.txt");

		fout<<"\n            �����и�վ "<<timestr<<" ��ѩͳ��  \n"
			  "--------------------------------------------------------------------------\n\n\n"
			  "��ʱ����ϸ��ѩ��� ѩ��(cm)/��ѩ��(mm)��\n"
			  "---------------------------------------------\n";
		
		fout<<"վ��";

		for(int index=0;index<timeList.size();index++)
		{
			fout<<std::setw(10)<<timeList[index].Format("%#d/%Hʱ");
		}
		fout<<"  ���ѩ��/�ۼƽ�ѩ��\n\n";
		
		for(int index=0;index<allStationsRecord.size();index++)
		{
			fout<<luoyangStationName[index];
			
			for(int col=0; col<allStationsRecord[index].size(); col++)
			{
				fout<<std::setw(10)<<allStationsRecord[index][col].GetSnowStr();
			}
			fout<<std::setw(10)<<accumulatedResult[index].GetSnowStr()<<std::endl;
		}

		fout<<"\n\n\n";
		fout<<"��վ�� ���ѩ��(cm)/�ۼƽ�ѩ��(mm)��\n"
			"---------------------------------------------\n";
		
		for(int index=0;index<accumulatedResult.size();index++)
		{
			fout<<"    "<<luoyangStationName[index]<<": "<<accumulatedResult[index].GetSnowStr();
		}
		
		fout.close();
	}

	else 
	{
		log_to_file("ftplog.txt","��ѯ���ϵ���");
		MessageBox("����ܴ���ɣ�","��ʾ",MB_OK|MB_ICONINFORMATION );

		return false;
	}

	ShellExecute(NULL, "open", "result.txt", NULL, NULL, SW_SHOWNORMAL);

	return true;
}

void CReadSnowUIDlg::InitDataFromFile()
{
	std::ifstream fin;

	fin.open("luoyang-stations.txt");

	if(!fin.is_open())
	{
		log_to_file("ftplog.txt","���ļ�luoyang-stations.txtʧ��");
		return;
	}

	std::string str;
	
	while(fin>>str)
	{
		luoyangStationID.push_back(str);
		fin>>str;
		luoyangStationName.push_back(str);
	}
	fin.close();

	fin.clear();
	fin.open("henan-stations.txt");
	if(!fin.is_open())
	{
		log_to_file("ftplog.txt","���ļ�henan-stations.txtʧ��");
		return;
	}
	
	while(fin>>str)
	{
		henanStationID.push_back(str);
		fin>>str;
		henanStationName.push_back(str);
	}
	fin.close();
}

int CReadSnowUIDlg::getSelectHour(CString hourString)const
{
	if("06ʱ" == hourString) return 6;
	else if("07ʱ" == hourString) return 7;
	else if("08ʱ" == hourString) return 8;
	else if("11ʱ" == hourString) return 11;
	else if("14ʱ" == hourString) return 14;
	else if("17ʱ" == hourString) return 17;
	else if("20ʱ" == hourString) return 20;
	else return 20;
}
