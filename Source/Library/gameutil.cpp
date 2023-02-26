//#define	 INITGUID
#include "stdafx.h"
#include "../Core/game.h"
#include "../Core/MainFrm.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "audio.h"
#include "gameutil.h"
#include "gamecore.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// CMovingBitmap: Moving Bitmap class
	// 這個 class 提供可以移動的圖形
	// 要懂得怎麼呼叫(運用)其各種能力，但是可以不懂下列的程式是什麼意思
	/////////////////////////////////////////////////////////////////////////////

	//! CMovingBitmap 建構子
	/*! 
		用於創立一個尚未讀取圖片的物件。
	*/
	CMovingBitmap::CMovingBitmap()
	{
		isBitmapLoaded = false;
	}

	//! 取得 CMovingBitmap 物件的圖片高度。
	/*!
		需要先載入圖片。
		\return 圖片高度，以像素為單位。
	*/
	int CMovingBitmap::GetHeight()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Height() is called !!!");
		return location.bottom - location.top;
	}

	int CMovingBitmap::GetLeft()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Left() is called !!!");
		return location.left;
	}

	void CMovingBitmap::LoadBitmap(int IDB_BITMAP, COLORREF color)
	{
		CBitmap bitmap;
		BOOL rval = bitmap.LoadBitmap(IDB_BITMAP);
		GAME_ASSERT(rval, "Load bitmap failed !!! Please check bitmap ID (IDB_XXX).");
		BITMAP bitmapSize;
		bitmap.GetBitmap(&bitmapSize);
		
		InitializeRectByBITMAP(bitmapSize);

		surfaceID.push_back(CDDraw::RegisterBitmap(IDB_BITMAP, color));
		filterColor = color;
		isBitmapLoaded = true;
	}

	void CMovingBitmap::LoadBitmap(char *filename, COLORREF color)
	{
		HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		if (hbitmap == NULL) {
			char error_msg[300];
			sprintf(error_msg, "Loading bitmap	from file \"%s\" failed !!!", filename);
			GAME_ASSERT(false, error_msg);
		}

		CBitmap *bmp = CBitmap::FromHandle(hbitmap); // memory will be deleted automatically
		BITMAP bitmapSize;
		bmp->GetBitmap(&bitmapSize);

		InitializeRectByBITMAP(bitmapSize);

		surfaceID.push_back(CDDraw::RegisterBitmap(filename, color));
		imageFileName = string(filename);
		filterColor = color;
		isBitmapLoaded = true;

		bmp->DeleteObject();
	}

	void CMovingBitmap::LoadBitmap(vector<char*> filename, COLORREF color)
	{
		for (int i = 0; i < (int)filename.size(); i++) {
			LoadBitmap(filename[i], color);
		}
	}

	void CMovingBitmap::LoadBitmapByString(vector<string> filename, COLORREF color)
	{

		for (int i = 0; i < (int)filename.size(); i++) {
			LoadBitmap((char*)filename[i].c_str(), color);
		}
	}

	void CMovingBitmap::LoadEmptyBitmap(int height, int width) {
		HBITMAP hbitmap = CreateBitmap(width, height, 1, 32, NULL);
		CBitmap *bmp = CBitmap::FromHandle(hbitmap); // memory will be deleted automatically

		/* Fill white color to bitmap */
		HDC hdc = CreateCompatibleDC(NULL);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, hbitmap);
		PatBlt(hdc, 0, 0, width, height, WHITENESS);
		SelectObject(hdc, hOldBitmap);
		DeleteDC(hdc);

		BITMAP bitmapSize;
		bmp->GetBitmap(&bitmapSize);

		InitializeRectByBITMAP(bitmapSize);

		surfaceID.push_back(CDDraw::RegisterBitmapWithHBITMAP(hbitmap));
		isBitmapLoaded = true;

		bmp->DeleteObject();
	}

	void CMovingBitmap::UnshowBitmap()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before SetTopLeft() is called !!!");
		isAnimation = false;
		this->ShowBitmap(0);
	}

	void CMovingBitmap::SetTopLeft(int x, int y)
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before SetTopLeft() is called !!!");
		int dx = location.left - x;
		int dy = location.top - y;
		location.left = x;
		location.top = y;
		location.right -= dx;
		location.bottom -= dy;
	}

	void CMovingBitmap::SetAnimation(int delay, bool once) {
		if(!once) isAnimation = true;
		isOnce = once;
		delayCount = delay;
	}

	void CMovingBitmap::ShowBitmap()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before ShowBitmap() is called !!!");
		CDDraw::BltBitmapToBack(surfaceID[frameIndex], location.left, location.top);
		ShowBitmapBySetting();
	}

	void CMovingBitmap::ShowBitmap(double factor)
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before ShowBitmap() is called !!!");
		CDDraw::BltBitmapToBack(surfaceID[frameIndex], location.left, location.top, factor);
		ShowBitmapBySetting();
	}

	void CMovingBitmap::SetFrameIndexOfBitmap(int frameIndex) {
		GAME_ASSERT(frameIndex < (int) surfaceID.size(), "選擇圖片時索引出界");
		this->frameIndex = frameIndex;
	}

	int CMovingBitmap::GetFrameIndexOfBitmap() {
		return frameIndex;
	}

	int CMovingBitmap::GetTop()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Top() is called !!!");
		return location.top;
	}

	int CMovingBitmap::GetWidth()
	{
		GAME_ASSERT(isBitmapLoaded, "A bitmap must be loaded before Width() is called !!!");
		return location.right - location.left;
	}

	void CMovingBitmap::ToggleAnimation() {
		frameIndex = 0;
		isAnimation = true;
		isAnimationDone = false;
	}

	bool CMovingBitmap::IsAnimation() {
		return isAnimation;
	}

	bool CMovingBitmap::IsAnimationDone() {
		return isAnimationDone;
	}

	bool CMovingBitmap::IsOnceAnimation() {
		return isOnce;
	}

	bool CMovingBitmap::IsBitmapLoaded() {
		return isBitmapLoaded;
	}

	int CMovingBitmap::GetFrameSizeOfBitmap() {
		return (int) surfaceID.size();
	}

	void CMovingBitmap::InitializeRectByBITMAP(BITMAP bitmapSize) {
		const unsigned NX = 0;
		const unsigned NY = 0;

		location.left = NX;
		location.top = NY;
		location.right = NX + bitmapSize.bmWidth;
		location.bottom = NY + bitmapSize.bmHeight;
	}

	void CMovingBitmap::ShowBitmapBySetting() {
		if (isAnimation == true && clock() - last_time >= delayCount) {
			frameIndex += 1;
			last_time = clock();
			if (frameIndex == surfaceID.size() && animationCount > 0) {
				animationCount -= 1;
			}
			if (frameIndex == surfaceID.size() && (isOnce || animationCount == 0)) {
				isAnimation = false;
				isAnimationDone = true;
				frameIndex = surfaceID.size() - 1;
				return;
			}
			frameIndex = frameIndex % surfaceID.size();
		}
	}

	string CMovingBitmap::GetImageFileName() {
		return imageFileName;
	}

	COLORREF CMovingBitmap::GetFilterColor() {
		return filterColor;
	}

	bool CMovingBitmap::IsOverlap(CMovingBitmap bmp1, CMovingBitmap bmp2) {
		CRect rect;
		BOOL isOverlap = rect.IntersectRect(bmp1.location, bmp2.location);
		return isOverlap;
	}

	/////////////////////////////////////////////////////////////////////////////
	// CTextDraw: The class provide the ability to draw the text.
	// 這個 class 提供文字的呈現
	// 要懂得怎麼呼叫(運用)其各種能力，但是可以不懂下列的程式是什麼意思
	/////////////////////////////////////////////////////////////////////////////

	void CTextDraw::Print(CDC *pDC, int x, int y, string str) {
		x = CDDraw::IsFullScreen() ? x + (RESOLUTION_X - SIZE_X) / 2 : x;
		y = CDDraw::IsFullScreen() ? y + (RESOLUTION_Y - SIZE_Y) / 2 : y;
		pDC->TextOut(x, y, str.c_str());
	}

	void CTextDraw::ChangeFontLog(CDC *pDC, int size, string fontName, COLORREF fontColor, int weight) {
		CFont* fp;

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(fontColor);
		LOGFONT lf;
		CFont f;
		memset(&lf, 0, sizeof(lf));
		lf.lfHeight = -MulDiv(size, GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSY), 96);
		lf.lfWeight = weight;
		strcpy(lf.lfFaceName, fontName.c_str());
		f.CreateFontIndirect(&lf);
		fp = pDC->SelectObject(&f);
	}

}         
