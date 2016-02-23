
// ������ѹ��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������ѹ��.h"
#include "������ѹ��Dlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <queue>
#include <afxpriv.h>
#include "HelpDlg.h"
#include "memory.h"
#include "libjpeg/jpeglib.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C������ѹ��Dlg �Ի���



C������ѹ��Dlg::C������ѹ��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C������ѹ��Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C������ѹ��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(C������ѹ��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C������ѹ��Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C������ѹ��Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C������ѹ��Dlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &C������ѹ��Dlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_BUTTON4, &C������ѹ��Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C������ѹ��Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &C������ѹ��Dlg::OnEnChangeEdit1)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// C������ѹ��Dlg ��Ϣ�������

BOOL C������ѹ��Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C������ѹ��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C������ѹ��Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID   �������Ҹոռ����λͼ��Դ 
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		 
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		//CDialogEx::OnPaint();
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID   �������Ҹոռ����λͼ��Դ 
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	}
		
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C������ѹ��Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ����ѹ��.cpp : ����Ӧ�ó������ڵ㡣
//

struct HuffNode
{
	long long weight;

	int parent, lchild, rchild;
};
struct HuffTree  //���ս��ɵĹ�������
{
	HuffNode *buffer;
	int leafnum;  // buffer=2*leafnum-1
};
struct BitBuffer
{
	int buffer, count;
};

int InitBitBuffer(BitBuffer &B)
{
	B.buffer = B.count = 0;
	return 1;
}

bool AppendBit(BitBuffer &B, int bit)
{
	if (bit == 1)
		B.buffer = (B.buffer << 1) | 1;//��������1
	else
		B.buffer = B.buffer << 1;
	B.count++;
	return B.count >= 8;  
}

int countfre(FILE *fp, long long *&cal)
{
	int ch;
	while ((ch = fgetc(fp)) != EOF)
		cal[ch]++;
	return 1;
}

int CreateHuffTree(HuffTree &T, int leafnum, long long weight[])
{
	T.buffer = new HuffNode[2 * leafnum - 1];  //���еĹ������ڵ�
	T.leafnum = leafnum;
	for (int i = 0; i < leafnum; i++)//Ҷ�ӽڵ�
	{
		T.buffer[i].weight = weight[i];
		T.buffer[i].parent = -1;
		T.buffer[i].lchild = -1;
		T.buffer[i].rchild = -1;
	}
	for (int i = 0; i < leafnum - 1; i++)
	{
		int m1 = -1, m2 = -1;
		for (int j = 0; j < leafnum + i; j++)
		{
			if (T.buffer[j].parent == -1)
			{
				if (m1 == -1 || T.buffer[j].weight < T.buffer[m1].weight)
				{
					m2 = m1; m1 = j;//m2Ϊ��С�ģ�m1Ϊ��С���±� 
				}
				else if (m2 == -1 || T.buffer[j].weight < T.buffer[m2].weight)
					m2 = j;
			}
		}
		T.buffer[m1].parent = i + leafnum;
		T.buffer[m2].parent = i + leafnum;
		T.buffer[i + leafnum].parent = -1;
		if (m1 < m2)
		{
			T.buffer[i + leafnum].lchild = m1;
			T.buffer[i + leafnum].rchild = m2;
		}
		else
		{
			T.buffer[i + leafnum].lchild = m2;
			T.buffer[i + leafnum].rchild = m1;
		}
		T.buffer[i + leafnum].weight = T.buffer[m1].weight + T.buffer[m2].weight;
	}
	return 1;
}

int coding(HuffTree T, FILE *fp, FILE *outf)
{
	for (int i = 0; i < 511; i++)
	{
		int byte = T.buffer[i].parent - 256;
		fputc(byte, outf);
	}
	fputc(0, outf);
	int ch;
	BitBuffer B;
	InitBitBuffer(B);
	stack<int> temp;//�������ÿ���ֽڶ�Ӧ�Ĺ��������� 
	while ((ch = fgetc(fp)) != EOF)
	{
		while (T.buffer[ch].parent != -1)
		{
			if (ch == T.buffer[T.buffer[ch].parent].lchild)
				temp.push(0);
			else if (ch == T.buffer[T.buffer[ch].parent].rchild)
				temp.push(1);
			ch = T.buffer[ch].parent;
		}
		while (!temp.empty())
		{ 
			if (AppendBit(B, temp.top()) == 1)
			{
				fputc(B.buffer, outf);
				InitBitBuffer(B);
			}
			temp.pop();
		}
	}
	for (int i = B.count; i < 8; i++)//���û��8λ�����
		B.buffer = B.buffer << 1;
	fputc(B.buffer, outf);
	fseek(outf, 511L, 0);
	fputc(B.count, outf);//���һ���ֽڵĳ���
	return 1;
}

int  C������ѹ��Dlg::decompress(char *argv[])//��ѹ��
{
	int count;
	FILE *fp;
	errno_t err;
	if ((fopen_s(&fp, argv[2], "rb")) != 0)
	{
		TCHAR str[256] = _T("�ļ��򿪴������������ִ�С�");
		MessageBox(str);
		return 1;
	}
	HuffTree T;
	int ch;
	T.buffer = new HuffNode[511];
	T.leafnum = 256;
	for (int i = 0; i < 511; i++)
	{
		T.buffer[i].parent = -1;
		T.buffer[i].lchild = -1;
		T.buffer[i].rchild = -1;
	}
	for (int i = 0; i < 510; i++)
	{
		ch = fgetc(fp);
		T.buffer[i].parent = ch + 256;
		if (T.buffer[ch + 256].lchild == -1)
			T.buffer[ch + 256].lchild = i;
		else
			T.buffer[ch + 256].rchild = i;
	}
	fgetc(fp);//���ս�β��ʶ0
	count = fgetc(fp);//�������һ������8�ĳ��� 
	FILE *outf;
	err = fopen_s(&outf, argv[3], "wb");
	if (err != 0)
	{
		TCHAR str[256] = _T("�������ļ������������������ִ�С�");
		MessageBox(str);
		return 2;
	}
	m_Progress.SetPos(30);
	int count2 = 0;
	queue<int> temp;
	stack<bool> s;
	int tran = 510;
	while (1)
	{
		if ((ch = fgetc(fp)) != EOF)
		{
			temp.push(ch);
			count2++;
		}
		else
			break;
		while (count2 > 1)//count2����1֤��û��ĩβ
		{
			int num = temp.front();
			temp.pop();
			count2--;
			for (int i = 0; i < 8; i++)
			{ 
				s.push(num % 2);
				num /= 2;
			}
			while (!s.empty())
			{
				if (T.buffer[tran].lchild == -1 && T.buffer[tran].rchild == -1)
				{
					fputc(tran, outf);
					tran = 510;
				}
				else if (s.top() == 0)
				{
					tran = T.buffer[tran].lchild;
					s.pop();
				}
				else if (s.top() == 1)
				{
					tran = T.buffer[tran].rchild;
					s.pop();
				}
			}
		}
	} 
	m_Progress.SetPos(60);
	int num = temp.front();
	temp.pop();
	for (int i = 0; i < 8; i++)
	{
		s.push(num % 2);
		num /= 2;
	}
	if (T.buffer[tran].lchild == -1 && T.buffer[tran].rchild == -1)
	{
		fputc(tran, outf);
		tran = 510;
	}
	for (int i = 0; i < count + 1; i++)
	{
		if (s.top() == 0)
		{
			tran = T.buffer[tran].lchild;
			s.pop();
		}
		else if (s.top() == 1)
		{
			tran = T.buffer[tran].rchild;
			s.pop();
		}
		if (T.buffer[tran].lchild == -1 && T.buffer[tran].rchild == -1)
		{
			fputc(tran, outf);
			tran = 510;
		}
	}
	fclose(outf);
	fclose(fp);
	m_Progress.SetPos(100);
	return 0;
}

int C������ѹ��Dlg::compress(char *argv[])//ѹ������
{
	FILE *fp;
	if (fopen_s(&fp, argv[2], "rb") != 0)
	{
		TCHAR str[256] = _T("�ļ��򿪴������������ִ�С�");//vs2013�Ժ�������ֵı�Ҫת��
		MessageBox(str);
		return 1;
	}
	FILE *outf;
	errno_t err;
	//��BMP�ļ������ж�================================================================================
	BITMAPFILEHEADER bfh;		// bmp�ļ�ͷ
	BITMAPINFOHEADER bih;		// bmpͷ��Ϣ
	RGBQUAD rq[256];			// ��ɫ��
	int nAdjust;		// �����ֽڶ���
	char *strSourceFileName = argv[2];
	char *strDestFileName = argv[3];

	BYTE *data = NULL;
	int nComponent = 0;
	fread(&bfh, sizeof(bfh), 1, fp);
	fread(&bih, sizeof(bih), 1, fp);
	switch (bih.biBitCount)
	{
	case 8: 
	{
		if (bfh.bfOffBits - 1024 < 54)//BMPͼ�����ݵĵ�ַ
		{
			TCHAR str[256] = _T("ϵͳ��⵽���ļ�����bmp�ļ���ͼƬλ�����󣬽�������ͨѹ����");
			MessageBox(str);
			//fclose(f);
			goto flag;
		}
		// 8λ�ֽڶ���
		nAdjust = bih.biWidth % 4;
		if (nAdjust) nAdjust = 4 - nAdjust;
		data = new BYTE[(bih.biWidth + nAdjust)*bih.biHeight];
		fseek(fp, bfh.bfOffBits - 1024, SEEK_SET);// ��λ��ɫ�壬����ȡ��ɫ��
		fread(rq, sizeof(RGBQUAD), 256, fp);
		fread(data, (bih.biWidth + nAdjust)*bih.biHeight, 1, fp);
		fclose(fp);
		nComponent = 1;
		break;
	}
	case 24:
	{
		// 8λ�ֽڶ���
		nAdjust = bih.biWidth * 3 % 4;
		if (nAdjust) nAdjust = 4 - nAdjust;
		data = new BYTE[(bih.biWidth * 3 + nAdjust)*bih.biHeight];
		fseek(fp, bfh.bfOffBits, SEEK_SET);
		fread(data, (bih.biWidth * 3 + nAdjust)*bih.biHeight, 1, fp);
		fclose(fp);
		for (int j = 0; j < bih.biHeight; j++){
			for (int i = 0; i < bih.biWidth; i++)
			{
				BYTE red = data[j*(bih.biWidth * 3 + nAdjust) + i * 3];
				data[j*(bih.biWidth * 3 + nAdjust) + i * 3] = data[j*(bih.biWidth * 3 + nAdjust) + i * 3 + 2];
				data[j*(bih.biWidth * 3 + nAdjust) + i * 3 + 2] = red;
			}
		}
		nComponent = 3;
		break;
	}
	default:
	{
		TCHAR str[256] = _T("ϵͳ��⵽���ļ�����bmp�ļ���ͼƬλ�����󣬽�������ͨѹ����");
		MessageBox(str);
		//fclose(f);
		goto flag;
	}
	}

	struct jpeg_compress_struct jcs;
	struct jpeg_error_mgr jem;
	jcs.err = jpeg_std_error(&jem);

	jpeg_create_compress(&jcs);
	err = fopen_s(&fp, strDestFileName, "wb");
	if (err != 0)
	{
		delete[] data;
		TCHAR str[256] = _T("������ͼƬ�ļ�ʧ�ܣ�");
		MessageBox(str);
		return 2;
	}
	jpeg_stdio_dest(&jcs, fp);
	jcs.image_width = bih.biWidth; 			
	jcs.image_height = bih.biHeight;
	jcs.input_components = nComponent;			// 1��ʾ�Ҷ�ͼ�� 3��ʾ��ɫλͼ
	if (nComponent == 1)
		jcs.in_color_space = JCS_GRAYSCALE; 
	else
		jcs.in_color_space = JCS_RGB;

	jpeg_set_defaults(&jcs);
	jpeg_set_quality(&jcs, 60, true);
	jpeg_start_compress(&jcs, TRUE);
	JSAMPROW row_pointer[1];			// һ��λͼ
	int row_stride;						// ÿһ�е��ֽ��� 
	row_stride = jcs.image_width*nComponent;		
	// ��ÿһ�н���ѹ��
	while (jcs.next_scanline < jcs.image_height) {
		row_pointer[0] = &data[(jcs.image_height - jcs.next_scanline - 1) * (row_stride + nAdjust)];
		jpeg_write_scanlines(&jcs, row_pointer, 1);
	}

	jpeg_finish_compress(&jcs);

	jpeg_destroy_compress(&jcs);

	fclose(fp);
	delete[] data;
	return 0;

	//��ͨ�ļ���ѹ��=========================================================================
flag:
	err = fopen_s(&outf, argv[3], "wb+");
	if (err != 0)
	{
		TCHAR str[256] = _T("�������ļ������������������ִ�С�");
		MessageBox(str);
		return 2;
	}
	long long *cal = new long long[256];
	for (int i = 0; i < 256; i++)
		cal[i] = 0;
	countfre(fp, cal);
	fclose(fp);
	m_Progress.SetPos(30);
	HuffTree T;
	CreateHuffTree(T, 256, cal);
	delete[]cal;
	fopen_s(&fp, argv[2], "rb");
	m_Progress.SetPos(60);
	coding(T, fp, outf);
	fclose(fp);
	fclose(outf);
	m_Progress.SetPos(100);
	return 0;
}
char *argv[4] = { new char[10], new char[10], new char[10], new char[10] };

void C������ѹ��Dlg::OnBnClickedButton1()//ѹ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	const int nMaxValue = 100;
	m_Progress.SetRange32(0, nMaxValue);
	m_Progress.SetPos(0);
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	USES_CONVERSION;
	argv[2] = T2A(str);
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	argv[3] = T2A(str);
	//argv[3] = (char*)(LPCTSTR)str;
	int flag = compress(argv);
	if (flag == 0)
	{
		TCHAR str[256] = _T("ѹ���ɹ���");
		MessageBox(str);
	}
	//m_Progress.SetPos(0);
}


void C������ѹ��Dlg::OnBnClickedButton2()//��ѹ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_Progress.SetPos(0);
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	USES_CONVERSION;
	argv[2] = T2A(str);
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	argv[3] = T2A(str);
	int flag = decompress(argv);
	if (flag == 0)
	{
		TCHAR str[256] = _T("��ѹ�ɹ���");
		MessageBox(str);
	}
	//m_Progress.SetPos(0);
}


void C������ѹ��Dlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CHelpDlg Dlg;
	Dlg.DoModal();
}

void C������ѹ��Dlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void C������ѹ��Dlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, strFilePath);
	}

}


void C������ѹ��Dlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here   
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
	// ���챣���ļ��Ի���   
	CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// ��ʾ�����ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, strFilePath);
	}

}


void C������ѹ��Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CString strFilePath = _T("Hello");
	//strFilePath = this->m_lpszTemplateName;
	//MessageBox(strFilePath);
	//SetDlgItemText(IDC_EDIT1, strFilePath);
}



void C������ѹ��Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default  
	WCHAR strFileName[MAX_PATH];
	 
		::DragQueryFileW(hDropInfo, 0, strFileName, MAX_PATH);
		CString str(strFileName);
		SetDlgItemText(IDC_EDIT1, str);
		
	 

	::DragFinish(hDropInfo);

	   CDialog::OnDropFiles(hDropInfo);

}


void C������ѹ��Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*if (point.x > 20 && point.y > 82 && point.x < 70 && point.y < 96)     //����
	{
		CHelpDlg Dlg;
		Dlg.DoModal();
	}
	if (point.x > 130 && point.y > 138 && point.x < 176 && point.y < 154)     //��
	{
		// TODO:  �ڴ���ӿؼ�֪ͨ����������
		TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
		// ������ļ��Ի���   
		CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
		CString strFilePath;

		// ��ʾ���ļ��Ի���   
		if (IDOK == fileDlg.DoModal())
		{
			// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT1, strFilePath);
		}
	}
	if (point.x > 131 && point.y > 167 && point.x < 176 && point.y < 184)    //����
	{
		 
		// ���ù�����   
		TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
		// ���챣���ļ��Ի���   
		CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		CString strFilePath;

		// ��ʾ�����ļ��Ի���   
		if (IDOK == fileDlg.DoModal())
		{
			// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT2, strFilePath);
		}
	}
	if (point.x > 15 && point.y > 201 && point.x < 64 && point.y < 223)    //ѹ��
	{
		const int nMaxValue = 100;
		m_Progress.SetRange32(0, nMaxValue);
		m_Progress.SetPos(0);
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		USES_CONVERSION;
		argv[2] = T2A(str);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		argv[3] = T2A(str);
		//argv[3] = (char*)(LPCTSTR)str;
		int flag = compress(argv);
		if (flag == 0)
		{
			TCHAR str[256] = _T("ѹ���ɹ���");
			MessageBox(str);
		}
	}
	if (point.x > 66 && point.y > 201 && point.x < 115 && point.y < 223)   //��ѹ��

	{
		m_Progress.SetPos(0);
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		USES_CONVERSION;
		argv[2] = T2A(str);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		argv[3] = T2A(str);
		int flag = decompress(argv);
		if (flag == 0)
		{
			TCHAR str[256] = _T("��ѹ�ɹ���");
			MessageBox(str);
		}
	}*/
	CDialogEx::OnLButtonUp(nFlags, point);
}


void C������ѹ��Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (point.x > 36 && point.y > 143 && point.x < 74 && point.y < 162)     //����
	{
		CHelpDlg Dlg;
		Dlg.DoModal();
	}
	if (point.x > 229 && point.y > 243 && point.x < 308 && point.y < 272)     //��
	{
		// TODO:  �ڴ���ӿؼ�֪ͨ����������
		TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
		// ������ļ��Ի���   
		CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
		CString strFilePath;

		// ��ʾ���ļ��Ի���   
		if (IDOK == fileDlg.DoModal())
		{
			// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT1, strFilePath);
		}
	}
	if (point.x > 229 && point.y > 293 && point.x < 309 && point.y < 322)    //����
	{

		// ���ù�����   
		TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
		// ���챣���ļ��Ի���   
		CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		CString strFilePath;

		// ��ʾ�����ļ��Ի���   
		if (IDOK == fileDlg.DoModal())
		{
			// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT2, strFilePath);
		}
	}
	if (point.x > 26 && point.y > 352 && point.x < 113 && point.y < 392)    //ѹ��
	{
		const int nMaxValue = 100;
		m_Progress.SetRange32(0, nMaxValue);
		m_Progress.SetPos(0);
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		USES_CONVERSION;
		argv[2] = T2A(str);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		argv[3] = T2A(str);
		//argv[3] = (char*)(LPCTSTR)str;
		int flag = compress(argv);
		if (flag == 0)
		{
			TCHAR str[256] = _T("ѹ���ɹ���");
			MessageBox(str);
		}
	}
	if (point.x > 122 && point.y > 355 && point.x < 195 && point.y < 390)   //��ѹ��

	{
		m_Progress.SetPos(0);
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		USES_CONVERSION;
		argv[2] = T2A(str);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		argv[3] = T2A(str);
		int flag = decompress(argv);
		if (flag == 0)
		{
			TCHAR str[256] = _T("��ѹ�ɹ���");
			MessageBox(str);
		}
	}
	if (point.x > 376 && point.y > 0 && point.x < 396 && point.y < 39)   //�رմ���
	{
		EndDialog(IDCANCEL);
	}
	if (point.x > 0 && point.y >96 && point.x < 20 && point.y < 136)   //�϶�����
	{
		// ���ø��ദ������ɻ�������
		CDialog::OnLButtonDown(nFlags, point);


		// ����WM_NCLBUTTONDOWN��Ϣ
		// ʹWindows��Ϊ����ڱ�������
		PostMessage(WM_NCLBUTTONDOWN,
			HTCAPTION,
			MAKELPARAM(point.x, point.y));  //��SendMessage(WM_SYSCOMMAND,0xF012,0);   //0xF012 = SC_MOVE | HTCAPTION

	}



	/*if (point.x > 20 && point.y > 82 && point.x < 70 && point.y < 96)     //����
	{
		CHelpDlg Dlg;
		Dlg.DoModal();
	}
	if (point.x > 130 && point.y > 138 && point.x < 176 && point.y < 154)     //��
	{
		// TODO:  �ڴ���ӿؼ�֪ͨ����������
		TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
		// ������ļ��Ի���   
		CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
		CString strFilePath;

		// ��ʾ���ļ��Ի���   
		if (IDOK == fileDlg.DoModal())
		{
			// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT1, strFilePath);
		}
	}
	if (point.x > 131 && point.y > 167 && point.x < 176 && point.y < 184)    //����
	{

		// ���ù�����   
		TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|Bmp�ļ�(*.bmp)|*.bmp|Jepg�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
		// ���챣���ļ��Ի���   
		CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		CString strFilePath;

		// ��ʾ�����ļ��Ի���   
		if (IDOK == fileDlg.DoModal())
		{
			// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT2, strFilePath);
		}
	}
	if (point.x > 15 && point.y > 201 && point.x < 64 && point.y < 223)    //ѹ��
	{
		const int nMaxValue = 100;
		m_Progress.SetRange32(0, nMaxValue);
		m_Progress.SetPos(0);
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		USES_CONVERSION;
		argv[2] = T2A(str);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		argv[3] = T2A(str);
		//argv[3] = (char*)(LPCTSTR)str;
		int flag = compress(argv);
		if (flag == 0)
		{
			TCHAR str[256] = _T("ѹ���ɹ���");
			MessageBox(str);
		}
	}
	if (point.x > 66 && point.y > 201 && point.x < 115 && point.y < 223)   //��ѹ��

	{
		m_Progress.SetPos(0);
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowText(str);
		USES_CONVERSION;
		argv[2] = T2A(str);
		GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		argv[3] = T2A(str);
		int flag = decompress(argv);
		if (flag == 0)
		{
			TCHAR str[256] = _T("��ѹ�ɹ���");
			MessageBox(str);
		}
	}
 */
	CDialogEx::OnLButtonDown(nFlags, point);
}
