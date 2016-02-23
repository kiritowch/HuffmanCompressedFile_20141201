
// 哈夫曼压缩Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "哈夫曼压缩.h"
#include "哈夫曼压缩Dlg.h"
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// C哈夫曼压缩Dlg 对话框



C哈夫曼压缩Dlg::C哈夫曼压缩Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C哈夫曼压缩Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C哈夫曼压缩Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
}

BEGIN_MESSAGE_MAP(C哈夫曼压缩Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C哈夫曼压缩Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C哈夫曼压缩Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C哈夫曼压缩Dlg::OnBnClickedButton3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &C哈夫曼压缩Dlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_BUTTON4, &C哈夫曼压缩Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C哈夫曼压缩Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT1, &C哈夫曼压缩Dlg::OnEnChangeEdit1)
	ON_WM_DROPFILES()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// C哈夫曼压缩Dlg 消息处理程序

BOOL C哈夫曼压缩Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C哈夫曼压缩Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C哈夫曼压缩Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP是你自己的图对应的ID   ，由于我刚刚加入的位图资源 
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		 
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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
		bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP是你自己的图对应的ID   ，由于我刚刚加入的位图资源 
		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap   *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	}
		
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C哈夫曼压缩Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 数据压缩.cpp : 定义应用程序的入口点。
//

struct HuffNode
{
	long long weight;

	int parent, lchild, rchild;
};
struct HuffTree  //最终建成的哈夫曼树
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
		B.buffer = (B.buffer << 1) | 1;//最右面添1
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
	T.buffer = new HuffNode[2 * leafnum - 1];  //所有的哈夫曼节点
	T.leafnum = leafnum;
	for (int i = 0; i < leafnum; i++)//叶子节点
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
					m2 = m1; m1 = j;//m2为次小的，m1为最小的下标 
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
	stack<int> temp;//用来存放每个字节对应的哈夫曼编码 
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
	for (int i = B.count; i < 8; i++)//最后没到8位的情况
		B.buffer = B.buffer << 1;
	fputc(B.buffer, outf);
	fseek(outf, 511L, 0);
	fputc(B.count, outf);//最后一个字节的长度
	return 1;
}

int  C哈夫曼压缩Dlg::decompress(char *argv[])//解压缩
{
	int count;
	FILE *fp;
	errno_t err;
	if ((fopen_s(&fp, argv[2], "rb")) != 0)
	{
		TCHAR str[256] = _T("文件打开错误，请检查后重新执行。");
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
	fgetc(fp);//接收结尾标识0
	count = fgetc(fp);//接收最后一个不满8的长度 
	FILE *outf;
	err = fopen_s(&outf, argv[3], "wb");
	if (err != 0)
	{
		TCHAR str[256] = _T("创建新文件错误，请检查输入后重新执行。");
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
		while (count2 > 1)//count2大于1证明没到末尾
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

int C哈夫曼压缩Dlg::compress(char *argv[])//压缩函数
{
	FILE *fp;
	if (fopen_s(&fp, argv[2], "rb") != 0)
	{
		TCHAR str[256] = _T("文件打开错误，请检查后重新执行。");//vs2013以后输出文字的必要转换
		MessageBox(str);
		return 1;
	}
	FILE *outf;
	errno_t err;
	//对BMP文件进行判断================================================================================
	BITMAPFILEHEADER bfh;		// bmp文件头
	BITMAPINFOHEADER bih;		// bmp头信息
	RGBQUAD rq[256];			// 调色板
	int nAdjust;		// 用于字节对齐
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
		if (bfh.bfOffBits - 1024 < 54)//BMP图像数据的地址
		{
			TCHAR str[256] = _T("系统检测到该文件不是bmp文件或图片位深有误，将进行普通压缩！");
			MessageBox(str);
			//fclose(f);
			goto flag;
		}
		// 8位字节对齐
		nAdjust = bih.biWidth % 4;
		if (nAdjust) nAdjust = 4 - nAdjust;
		data = new BYTE[(bih.biWidth + nAdjust)*bih.biHeight];
		fseek(fp, bfh.bfOffBits - 1024, SEEK_SET);// 定位调色板，并读取调色板
		fread(rq, sizeof(RGBQUAD), 256, fp);
		fread(data, (bih.biWidth + nAdjust)*bih.biHeight, 1, fp);
		fclose(fp);
		nComponent = 1;
		break;
	}
	case 24:
	{
		// 8位字节对齐
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
		TCHAR str[256] = _T("系统检测到该文件不是bmp文件或图片位深有误，将进行普通压缩！");
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
		TCHAR str[256] = _T("创建新图片文件失败！");
		MessageBox(str);
		return 2;
	}
	jpeg_stdio_dest(&jcs, fp);
	jcs.image_width = bih.biWidth; 			
	jcs.image_height = bih.biHeight;
	jcs.input_components = nComponent;			// 1表示灰度图， 3表示彩色位图
	if (nComponent == 1)
		jcs.in_color_space = JCS_GRAYSCALE; 
	else
		jcs.in_color_space = JCS_RGB;

	jpeg_set_defaults(&jcs);
	jpeg_set_quality(&jcs, 60, true);
	jpeg_start_compress(&jcs, TRUE);
	JSAMPROW row_pointer[1];			// 一行位图
	int row_stride;						// 每一行的字节数 
	row_stride = jcs.image_width*nComponent;		
	// 对每一行进行压缩
	while (jcs.next_scanline < jcs.image_height) {
		row_pointer[0] = &data[(jcs.image_height - jcs.next_scanline - 1) * (row_stride + nAdjust)];
		jpeg_write_scanlines(&jcs, row_pointer, 1);
	}

	jpeg_finish_compress(&jcs);

	jpeg_destroy_compress(&jcs);

	fclose(fp);
	delete[] data;
	return 0;

	//普通文件的压缩=========================================================================
flag:
	err = fopen_s(&outf, argv[3], "wb+");
	if (err != 0)
	{
		TCHAR str[256] = _T("创建新文件错误，请检查输入后重新执行。");
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

void C哈夫曼压缩Dlg::OnBnClickedButton1()//压缩
{
	// TODO:  在此添加控件通知处理程序代码
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
		TCHAR str[256] = _T("压缩成功！");
		MessageBox(str);
	}
	//m_Progress.SetPos(0);
}


void C哈夫曼压缩Dlg::OnBnClickedButton2()//解压缩
{
	// TODO:  在此添加控件通知处理程序代码
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
		TCHAR str[256] = _T("解压成功！");
		MessageBox(str);
	}
	//m_Progress.SetPos(0);
}


void C哈夫曼压缩Dlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CHelpDlg Dlg;
	Dlg.DoModal();
}

void C哈夫曼压缩Dlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

void C哈夫曼压缩Dlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, strFilePath);
	}

}


void C哈夫曼压缩Dlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here   
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
	// 构造保存文件对话框   
	CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, strFilePath);
	}

}


void C哈夫曼压缩Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//CString strFilePath = _T("Hello");
	//strFilePath = this->m_lpszTemplateName;
	//MessageBox(strFilePath);
	//SetDlgItemText(IDC_EDIT1, strFilePath);
}



void C哈夫曼压缩Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default  
	WCHAR strFileName[MAX_PATH];
	 
		::DragQueryFileW(hDropInfo, 0, strFileName, MAX_PATH);
		CString str(strFileName);
		SetDlgItemText(IDC_EDIT1, str);
		
	 

	::DragFinish(hDropInfo);

	   CDialog::OnDropFiles(hDropInfo);

}


void C哈夫曼压缩Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	/*if (point.x > 20 && point.y > 82 && point.x < 70 && point.y < 96)     //帮助
	{
		CHelpDlg Dlg;
		Dlg.DoModal();
	}
	if (point.x > 130 && point.y > 138 && point.x < 176 && point.y < 154)     //打开
	{
		// TODO:  在此添加控件通知处理程序代码
		TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
		// 构造打开文件对话框   
		CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
		CString strFilePath;

		// 显示打开文件对话框   
		if (IDOK == fileDlg.DoModal())
		{
			// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT1, strFilePath);
		}
	}
	if (point.x > 131 && point.y > 167 && point.x < 176 && point.y < 184)    //保存
	{
		 
		// 设置过滤器   
		TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
		// 构造保存文件对话框   
		CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		CString strFilePath;

		// 显示保存文件对话框   
		if (IDOK == fileDlg.DoModal())
		{
			// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT2, strFilePath);
		}
	}
	if (point.x > 15 && point.y > 201 && point.x < 64 && point.y < 223)    //压缩
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
			TCHAR str[256] = _T("压缩成功！");
			MessageBox(str);
		}
	}
	if (point.x > 66 && point.y > 201 && point.x < 115 && point.y < 223)   //解压缩

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
			TCHAR str[256] = _T("解压成功！");
			MessageBox(str);
		}
	}*/
	CDialogEx::OnLButtonUp(nFlags, point);
}


void C哈夫曼压缩Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (point.x > 36 && point.y > 143 && point.x < 74 && point.y < 162)     //帮助
	{
		CHelpDlg Dlg;
		Dlg.DoModal();
	}
	if (point.x > 229 && point.y > 243 && point.x < 308 && point.y < 272)     //打开
	{
		// TODO:  在此添加控件通知处理程序代码
		TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
		// 构造打开文件对话框   
		CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
		CString strFilePath;

		// 显示打开文件对话框   
		if (IDOK == fileDlg.DoModal())
		{
			// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT1, strFilePath);
		}
	}
	if (point.x > 229 && point.y > 293 && point.x < 309 && point.y < 322)    //保存
	{

		// 设置过滤器   
		TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
		// 构造保存文件对话框   
		CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		CString strFilePath;

		// 显示保存文件对话框   
		if (IDOK == fileDlg.DoModal())
		{
			// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT2, strFilePath);
		}
	}
	if (point.x > 26 && point.y > 352 && point.x < 113 && point.y < 392)    //压缩
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
			TCHAR str[256] = _T("压缩成功！");
			MessageBox(str);
		}
	}
	if (point.x > 122 && point.y > 355 && point.x < 195 && point.y < 390)   //解压缩

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
			TCHAR str[256] = _T("解压成功！");
			MessageBox(str);
		}
	}
	if (point.x > 376 && point.y > 0 && point.x < 396 && point.y < 39)   //关闭窗口
	{
		EndDialog(IDCANCEL);
	}
	if (point.x > 0 && point.y >96 && point.x < 20 && point.y < 136)   //拖动窗口
	{
		// 调用父类处理函数完成基本操作
		CDialog::OnLButtonDown(nFlags, point);


		// 发送WM_NCLBUTTONDOWN消息
		// 使Windows认为鼠标在标题条上
		PostMessage(WM_NCLBUTTONDOWN,
			HTCAPTION,
			MAKELPARAM(point.x, point.y));  //或SendMessage(WM_SYSCOMMAND,0xF012,0);   //0xF012 = SC_MOVE | HTCAPTION

	}



	/*if (point.x > 20 && point.y > 82 && point.x < 70 && point.y < 96)     //帮助
	{
		CHelpDlg Dlg;
		Dlg.DoModal();
	}
	if (point.x > 130 && point.y > 138 && point.x < 176 && point.y < 154)     //打开
	{
		// TODO:  在此添加控件通知处理程序代码
		TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
		// 构造打开文件对话框   
		CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
		CString strFilePath;

		// 显示打开文件对话框   
		if (IDOK == fileDlg.DoModal())
		{
			// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT1, strFilePath);
		}
	}
	if (point.x > 131 && point.y > 167 && point.x < 176 && point.y < 184)    //保存
	{

		// 设置过滤器   
		TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Bmp文件(*.bmp)|*.bmp|Jepg文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
		// 构造保存文件对话框   
		CFileDialog fileDlg(FALSE, _T("haf"), _T("*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
		CString strFilePath;

		// 显示保存文件对话框   
		if (IDOK == fileDlg.DoModal())
		{
			// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
			strFilePath = fileDlg.GetPathName();
			SetDlgItemText(IDC_EDIT2, strFilePath);
		}
	}
	if (point.x > 15 && point.y > 201 && point.x < 64 && point.y < 223)    //压缩
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
			TCHAR str[256] = _T("压缩成功！");
			MessageBox(str);
		}
	}
	if (point.x > 66 && point.y > 201 && point.x < 115 && point.y < 223)   //解压缩

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
			TCHAR str[256] = _T("解压成功！");
			MessageBox(str);
		}
	}
 */
	CDialogEx::OnLButtonDown(nFlags, point);
}
