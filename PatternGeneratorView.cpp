
// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// PatternGeneratorView.cpp : implementation of the CPatternGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatternGenerator.h"
#endif

#include "PatternGeneratorDoc.h"
#include "PatternGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPatternGeneratorView

IMPLEMENT_DYNCREATE(CPatternGeneratorView, CView)

BEGIN_MESSAGE_MAP(CPatternGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPatternGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CPatternGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_SUSPEND, &CPatternGeneratorView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_RESUME, &CPatternGeneratorView::OnResume)
END_MESSAGE_MAP()

// CPatternGeneratorView construction/destruction

CPatternGeneratorView::CPatternGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;

	 x = 400;
	 y = 200;

  x1 = 300 + 150 * cos(2);
  y1 = 200 + 150 * sin(2);

  //Saturn initial position (radius 200)

  x2 = 300 + 200 * cos(4);
  y2 = 200 + 200 * sin(4);
  	 
}


CPatternGeneratorView::~CPatternGeneratorView()
{
}

BOOL CPatternGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPatternGeneratorView drawing

void CPatternGeneratorView::OnDraw(CDC* pDC)
{
	CPatternGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	CPen* pOldPen = NULL;


	

	// planet1 orbit(Black, radius 100)
	CPen PenBlack1(PS_SOLID, 1, RGB(0, 0, 0));
	pOldPen = pDC->SelectObject(&PenBlack1);
	pDC->Ellipse(200, 100, 400, 300);
	pDC->SelectObject(pOldPen);
	
	// planet2 orbit(Black, radius 150)
	CPen PenBlack2(PS_SOLID, 1, RGB(0, 0, 0));
    pOldPen = pDC->SelectObject(&PenBlack2);
    pDC->Ellipse(150, 50, 450, 350);
	pDC->SelectObject(pOldPen);

	// saturn circular orbit yellow
	CPen yellowPen(PS_SOLID, 2, RGB(255, 255, 0));
    pOldPen = pDC->SelectObject(&yellowPen);
	pDC->Ellipse(100, 0, 500, 400); 
	pDC->SelectObject(pOldPen);

	//restore original brush
	pDC->SelectObject(pOldBrush);


	CBrush brushRed(RGB(255, 0, 0));
	CBrush* pO1dBrush = pDC->SelectObject(&brushRed);
	pDC->Ellipse(330, 230, 270, 170);  //sun
	pDC->SelectObject(pO1dBrush);

	CBrush brushBlack1(RGB(203, 250, 14));
	CBrush* pO2dBrush = pDC->SelectObject(&brushBlack1); //planet1 size
	pDC->Ellipse(x + 10, y + 10, x - 10, y - 10);

	CBrush brushBlack2(RGB(11, 252, 17));
	CBrush* pO3dBrush = pDC->SelectObject(&brushBlack2); //planet2
	pDC->Ellipse(x1 + 20, y1 + 20, x1 - 20, y1 - 20);
	pDC->SelectObject(pO3dBrush);
	
	//Saturn(Blue)
	CBrush brushSaturn(RGB(0, 0, 255));
	CBrush* pOldBrush4 = pDC->SelectObject(&brushSaturn);
	pDC->Ellipse(x2 - 20, y2 - 20, x2 + 20, y2 + 20);
	pDC->SelectObject(pOldBrush4);

	//TODO: add draw code or native data here
}

// CPatternGeneratorView printing


void CPatternGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPatternGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPatternGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPatternGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPatternGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPatternGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPatternGeneratorView diagnostics

#ifdef _DEBUG
void CPatternGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CPatternGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CPatternGeneratorDoc* CPatternGeneratorView::GetDocument() const //non-debug verson is inline
{
return (CPatternGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatternGeneratorView message handlers

void CPatternGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread =AfxBeginThread(CPatternGeneratorView::StartThread,this);
}

void CPatternGeneratorView::OnButtonSuspend()
{
	m_pCurrentThread->SuspendThread();
}
void CPatternGeneratorView::OnResume()
{
	m_pCurrentThread->ResumeThread();
}

UINT CPatternGeneratorView::StartThread(LPVOID Param)
{
	CPatternGeneratorView* pView = (CPatternGeneratorView*)Param;
	CPoint MyPoint(0, 0);
	int j = 0;
	while (1)
	{
		j = j + 4;

		// planet 1

		pView->x = 300 + 100 * cos(j * 0.05); //l
		pView->y = 200 + 100 * sin(j * 0.05); //b

		// planet2 


		pView->x1 = 300 + 150 * cos(j * 0.05 + 3);
		pView->y1 = 200 + 150 * sin(j * 0.05 + 3);

		// Saturn ( circular motion, radius 200)
		pView->x2 = 300 + 200 * cos(j * 0.05 + 5);
		pView->y2 = 200 + 200 * sin(j * 0.05 + 5);


		pView->Invalidate();
		Sleep(80);
	}
	return 0;
}
