// usbDetectDlg.h : ͷ�ļ�
//

#pragma once


// CusbDetectDlg �Ի���
class CusbDetectDlg : public CDialog
{
// ����
public:
	CusbDetectDlg(CWnd* pParent = NULL);
	// ��׼���캯��
	void FindUsbDevice();
// �Ի�������
	enum { IDD = IDD_USBDETECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
