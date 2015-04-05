// FractaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Fractale.h"
#include "FractaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFractaleDlg dialog

CFractaleDlg::CFractaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFractaleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFractaleDlg)
	m_nIniPts = 10;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFractaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFractaleDlg)
	DDX_Text(pDX, IDC_NBRINIPTS_EDIT, m_nIniPts);
	DDV_MinMaxUInt(pDX, m_nIniPts, 1, 1000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFractaleDlg, CDialog)
	//{{AFX_MSG_MAP(CFractaleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFractaleDlg message handlers

BOOL CFractaleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	bGO = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFractaleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFractaleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFractaleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFractaleDlg::OnButton1() 
{
	UpdateData(TRUE);
	// GO / STOP
	if (bGO)
	{
		bGO = FALSE;
		SetDlgItemText(IDC_BUTTON1, _T("GO"));
	}
	else
	{
		bGO = TRUE;
		SetDlgItemText(IDC_BUTTON1, _T("STOP"));
		// Thread
		AfxBeginThread(Thread, this);
	}
}

UINT CFractaleDlg::Thread(LPVOID pParam)
{
	CFractaleDlg	*pDlg = (CFractaleDlg*) pParam;
	CClientDC		dcClient(pDlg->GetDlgItem(IDC_PIC));
	static int		yMin;
	CRect			rect;
	register int	w, h, x, y;
	register UINT	i;
	CDC				memdc;
	CBitmap			bitmap,
					*pOriBmp;

	// Créé un DC
	pDlg->GetDlgItem(IDC_PIC)->GetClientRect(&rect);			// Donne la taille de la zone
	w = rect.Width();
	h = rect.Height();
	memdc.CreateCompatibleDC(&dcClient);
	bitmap.CreateCompatibleBitmap(&dcClient, w, h);
	pOriBmp = memdc.SelectObject(&bitmap);						// Sélectionne la bitmap dans le DC mém.
	
	// Fond gris (efface)
	memdc.FillSolidRect(0,0, w,h, RGB(192,192,192));

	// Affiche des pts aléatoires en bas
	for (i=0; i<pDlg->m_nIniPts; i++)
		memdc.SetPixel(rand()*w/RAND_MAX, h - 5, RGB(0,0,0));
	yMin = h - 6;

	while (pDlg->bGO)
	{
		// Calcule la fractale
		for (i=0; i<50; i++)
		{
			x = rand()*w/RAND_MAX;
			for (y=yMin; y<=h; y++)
				if (memdc.GetPixel(x,y) == RGB(0,0,0) ||
					memdc.GetPixel(x-1,y) == RGB(0,0,0) ||
					memdc.GetPixel(x+1,y) == RGB(0,0,0))
				{
					memdc.SetPixel(x,y-1, RGB(0,0,0));
					if (y-2<yMin)
						yMin = y-2;
					break;
				}
		}

		// DC Client = DC mémoire
		dcClient.BitBlt(0,0, w,h, &memdc, 0,0, SRCCOPY);
	}

	// Suppression des DCs & Bitmaps
	memdc.SelectObject(pOriBmp);
	bitmap.DeleteObject();
	memdc.DeleteDC();

	return 0;
}
