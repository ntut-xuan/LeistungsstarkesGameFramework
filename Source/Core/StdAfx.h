// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
/*
 *   2010-02-23 V4.5
 *      1. Add #define _WIN32_WINNT 0x0500 to work with VS2008
 *   2016-02-26 V4.9
 *      1. Remove #define _WIN32_WINNT and Preprocessor Definitions (WINVER=0x500)
 *      2. Include SDKDDKVER.h, the file automatic setting WINVER and _WIN32_WINNT in latest version
*/

#include <sdkddkver.h>

#if !defined(AFX_STDAFX_H__243A7A47_6962_11D3_9B4D_BAD1A91E5344__INCLUDED_)
#define AFX_STDAFX_H__243A7A47_6962_11D3_9B4D_BAD1A91E5344__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__243A7A47_6962_11D3_9B4D_BAD1A91E5344__INCLUDED_)
