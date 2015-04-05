// FractaleDlg.h : header file
//

#if !defined(AFX_FRACTALEDLG_H__33D86467_7DD2_11D3_A413_A5A5A5A5A5A5__INCLUDED_)
#define AFX_FRACTALEDLG_H__33D86467_7DD2_11D3_A413_A5A5A5A5A5A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFractaleDlg dialog

class CFractaleDlg : public CDialog
{
// Construction
public:
	CFractaleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFractaleDlg)
	enum { IDD = IDD_FRACTALE_DIALOG };
	UINT	m_nIniPts;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFractaleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFractaleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL bGO;
	static UINT Thread( LPVOID pParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTALEDLG_H__33D86467_7DD2_11D3_A413_A5A5A5A5A5A5__INCLUDED_)
