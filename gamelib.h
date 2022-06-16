/*
 * gamelib.h: 本檔案儲遊戲相關的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *		1. Add ENABLE_AUDIO flag.
 *   2004-03-02 V4.0
 *		1. Add CInteger class.
 *      2. Add CGameState abstract class and adjust CGame to apply
 *         state pattern for switching game states.
 *   2004-03-08 V4.1
 *      1. Add OPEN_AS_FULLSCREEN flag.
 *      2. The Game Engine now becomes a framework.
 *   2005-07-28
 *      1. Add GAME_ASSERT macro to display run time errors gracefully.
 *      2. Remove CDDarw::CheckSystem(). It is useless.
 *   2005-09-08
 *      1. Eliminate CSpecialEffect::Abort. It is useless now.
 *      2. Add SHOW_GAME_CYCLE_TIME flag.
 *      3. Add DEFAULT_BG_COLOR flag;
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add MOUSEMOVE Handler for CGame and CGameState.
 *      2. Add _TRACE preprocessor flag for VC++.net.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Remove constantness of CAnimation::DELAY_COUNT.
 *      3. Enhance CAnimation to support SetDelayCount(), Reset(), and IsFinalBitmap().
 *      4. Remove CAnimation::GetLocation() and CMovingBitmap::GetLocation().
 *      5. Bitmap coordinate can no longer be set by CMovingBitmap::LoadBitmap().
 *         Defauts to (0,0).
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *      2. Fix bug: audio is now correctly recovered after a sleep or suspension of windows.
 *      3. Support ENABLE_GAME_PAUSE.
 *   2008-02-15 V4.4
 *      1. Add setup project for Visual studio 2005.
 *      2. Support bitmap scaling when ShowBitmap(scale) is called.
 *      3. Add namespace game_framework.
 *      4. Make the class CGame a singleton so that MFC can access it easily.
 *      5. Support loading of bitmap from bmp file.
 *      6. Support ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Rewrite CAudio with MCI commands to eliminate dependency with DirectMusic.
*/

/////////////////////////////////////////////////////////////////////////////
// 定義遊戲可設定的環境與條件
/////////////////////////////////////////////////////////////////////////////

#define SIZE_X				 1400		// 設定遊戲畫面的解析度為640x480
#define SIZE_Y				 1005		// 註：若不使用標準的解析度，則不能切換到全螢幕
#define OPEN_AS_FULLSCREEN	 false		// 是否以全螢幕方式開啟遊戲
#define SHOW_LOAD_PROGRESS   true		// 是否顯示loading(OnInit)的進度
#define DEFAULT_BG_COLOR	 RGB(0, 0, 0)	// 遊戲畫面預設的背景顏色(黑色)
#define GAME_CYCLE_TIME		 15		    // 每33ms跑一次Move及Show(每秒30次)
#define SHOW_GAME_CYCLE_TIME false		// 是否在debug mode顯示cycle time
#define ENABLE_GAME_PAUSE	 false		// 是否允許以 Ctrl-Q 暫停遊戲
#define ENABLE_AUDIO		 true		// 啟動音效介面
#define ENABLE_TOOLBAR       false      // 是否關閉 toolbar
#define ENABLE_MENU          false      // 是否關閉 menu
#define ENABLE_STATUSBAR     false      // 是否關閉 statusbar
#define RESOLUTION_X     1920           // 全螢幕用，請設定成目前視窗的解析度 (width)。
#define RESOLUTION_Y     1080           // 全螢幕用，請設定成目前視窗的解析度 (height)。

/////////////////////////////////////////////////////////////////////////////
// 定義CGame及CGameState所使用的三個狀態常數
/////////////////////////////////////////////////////////////////////////////

enum GAME_STATES {
	GAME_STATE_INIT,
	GAME_STATE_RUN,
	GAME_STATE_OVER
};

/////////////////////////////////////////////////////////////////////////////
// Header for STL (Standard Template Library)
/////////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <map>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// 回報程式錯誤用的macro
// 備註：這裡使用macro以便保留檔案名稱及行號，利於debug。
/////////////////////////////////////////////////////////////////////////////

#define GAME_ASSERT(boolexp,str)											\
		if (!(boolexp)) {													\
			int id;															\
			char s[300]="";													\
			sprintf(s,"Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"		\
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);									\
			id = AfxMessageBox(s, MB_RETRYCANCEL);							\
																			\
			if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();												\
		}

namespace game_framework {


	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供時間、錯誤等控制
	// 一般的遊戲並不需直接操作這個物件，因此可以不管這個class的使用方法
	/////////////////////////////////////////////////////////////////////////////

	class CSpecialEffect {
	public:
		static void  SetCurrentTime();					// 儲存目前的時間至ctime
		static DWORD GetEllipseTime();					// 讀取目前的時間 - ctime
		static int   GetCurrentTimeCount();				// 讀取儲存ctime的次數
		static void  Delay(DWORD ms);					// 延遲 x ms
		static void  DelayFromSetCurrentTime(DWORD ms);	// 自ctime起算，延遲 x ms
	private:
		static DWORD ctime;
		static int	 ctimeCount;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class會建立DirectDraw物件，以提供其他class使用
	// 一般的遊戲並不需直接操作這個物件，因此可以不管這個class的使用方法
	/////////////////////////////////////////////////////////////////////////////

	class CDDraw {
		friend class CMovingBitmap;
	public:
		~CDDraw();
		static void  BltBackColor(DWORD);		// 將Back plain全部著上指定的顏色
		static void  BltBackToPrimary();		// 將Back plain貼至Primary plain
		static CDC*  GetBackCDC();				// 取得Back Plain的DC (device context)
		static void  GetClientRect(CRect &r);	// 取得設定的解析度
		static void  Init(int, int);			// Initialize direct draw
		static void  ReleaseBackCDC();			// 放掉Back Plain的DC (device context)
		static bool  SetFullScreen(bool);		// 設定為全螢幕模式/視窗模式
		static bool  IsFullScreen();			// 回答是否為全螢幕模式/視窗模式
	private:
		CDDraw();								// private constructor
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
		static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
		static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
		static void	 CheckDDFail(char *s);
		static bool  CreateSurface();
		static bool  CreateSurfaceFullScreen();
		static bool  CreateSurfaceWindowed();
		static void  LoadBitmap(int i, int IDB_BITMAP);
		static void  LoadBitmap(int i, char *filename);
		static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
		static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
		static int   RegisterBitmap(char *filename, COLORREF ColorKey);
		static void  ReleaseSurface();
		static void  RestoreSurface();
		static void  SetColorKey(unsigned SurfaceID, COLORREF color);
		static HDC					hdc;
		static CDC					cdc;
		static CView				*pCView;
		static LPDIRECTDRAW2		lpDD;
		static LPDIRECTDRAWCLIPPER	lpClipperPrimary;
		static LPDIRECTDRAWCLIPPER	lpClipperBack;
		static LPDIRECTDRAWSURFACE	lpDDSPrimary;
		static LPDIRECTDRAWSURFACE	lpDDSBack;
		static vector<LPDIRECTDRAWSURFACE>	lpDDS;
		static HRESULT				ddrval;
		static vector<int>			BitmapID;
		static vector<string>		BitmapName;
		static vector<CRect>		BitmapRect;
		static vector<COLORREF>		BitmapColorKey;
		static bool					fullscreen;
		static CDDraw				ddraw;
		static int					size_x, size_y;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供動態(可以移動)的圖形
	// 每個Public Interface的用法都要懂，Implementation可以不懂
	/////////////////////////////////////////////////////////////////////////////

	class CMovingBitmap {
	public:
		CMovingBitmap();
		int   Height();						// 取得圖形的高度
		int   Left();						// 取得圖形的左上角的 x 座標
		void  SetAnimation(int delay, bool _once);
		void  LoadBitmap(int, COLORREF = CLR_INVALID);		// 載入圖，指定圖的編號(resource)及透明色
		void  LoadBitmap(char*, COLORREF = CLR_INVALID);	// 載入圖，指定圖的檔名及透明色
		void  LoadBitmap(vector<char*>, COLORREF = CLR_INVALID);	// 載入圖，指定圖的檔名及透明色
		void  LoadBitmapByString(vector<string>, COLORREF = CLR_INVALID);	// 載入圖，指定圖的檔名及透明色
		void  UnshowBitmap();
		void  SetTopLeft(int, int);			// 將圖的左上角座標移至 (x,y)
		void  ShowBitmap();					// 將圖貼到螢幕
		void  ShowBitmap(double factor);	// 將圖貼到螢幕 factor < 1時縮小，>1時放大。注意：需要VGA卡硬體的支援，否則會很慢
		void  SelectShowBitmap(int select);
		int   GetSelectShowBitmap();
		void  ToggleAnimation();
		int   Top();						// 取得圖形的左上角的 y 座標
		int   Width();						// 取得圖形的寬度
		bool  IsAnimationDone();
		int   GetMovingBitmapFrame();
	protected:
		int selector = 0;
		int delayCount = 10;
		int animationCount = -1;
		clock_t last_time = clock();
		bool isAnimation = false;
		bool isAnimationDone = true;
		bool once = false;
		vector<unsigned> SurfaceID;
		bool     isBitmapLoaded = false;	// whether a bitmap has been loaded
		CRect    location;			// location of the bitmap
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以移動的動畫
	// 每個Public Interface的用法都要懂，Implementation可以不懂
	/////////////////////////////////////////////////////////////////////////////

	class CAnimation {
	public:
		CAnimation(int = 10);				// Constructor (預設動畫播放頻率每1/3秒換一張圖)
		void  AddBitmap(int, COLORREF = CLR_INVALID);
		// 增加一張圖形至動畫(圖的編號及透明色)
		void  AddBitmap(char *, COLORREF = CLR_INVALID);
		// 增加一張圖形至動畫(圖的編號及透明色)
		int   GetCurrentBitmapNumber();	// 取得正在撥放的bitmap是第幾個bitmap
		int   Height();					// 取得動畫的高度
		bool  IsFinalBitmap();			// 回傳正在撥放的bitmap是否為最後一個bitmap
		int   Left();					// 取得動畫的左上角的 x 座標
		void  OnMove();					// 依頻率更換bitmap
		void  OnShow();					// 將動畫貼到螢幕
		void  Reset();					// 重設播放順序回到第一張圖形
		void  SetDelayCount(int);		// 設定動畫播放速度的常數(越大越慢)
		void  SetTopLeft(int, int);		// 將動畫的左上角座標移至 (x,y)
		int   Top();					// 取得動畫的左上角的 y 座標
		int   Width();					// 取得動畫的寬度
	private:
		list<CMovingBitmap>				bmp;			// list of CMovingBitmap
		list<CMovingBitmap>::iterator	bmp_iter;		// list iterator
		int								bmp_counter;	// 儲存bmp_iter為第n個bmp
		int								delay_counter;	// 延緩動畫播放速度的計數器
		int								delay_count;	// 動畫播放速度的常數
		int								x, y;			// 動畫的座標
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供顯示整數圖形的能力
	// 每個Public Interface的用法都要懂，Implementation可以不懂
	/////////////////////////////////////////////////////////////////////////////

	class CInteger {
	public:
		CInteger(int = 5);			// default 5 digits
		void Add(int n);			// 增加整數值
		int  GetInteger();			// 回傳整數值
		void LoadBitmap();			// 載入0..9及負號之圖形
		void SetInteger(int);		// 設定整數值
		void SetTopLeft(int, int);	// 將動畫的左上角座標移至 (x,y)
		void ShowBitmap(bool);			// 將動畫貼到螢幕
		void ShowBitmap();			// 將動畫貼到螢幕
	private:
		int NUMDIGITS;			// 共顯示NUMDIGITS個位數
		CMovingBitmap digit[11]; // 儲存0..9及負號之圖形(bitmap)
		int x, y;						// 顯示的座標
		int n;							// 整數值
		bool isBmpLoaded;				// 是否已經載入圖形
	};

	/////////////////////////////////////////////////////////////////////////////
	// 宣告尚未定義的class
	/////////////////////////////////////////////////////////////////////////////

	class CGame;
	class CGameStateInit;
	class CGameStateRun;
	class CGameStateOver;

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的各種狀態之Base class(是一個abstract class)
	// 每個Public Interface的用法都要懂，Implementation可以不懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameState {
	public:
		CGameState(CGame *g);
		void OnDraw();			// Template Method
		void OnCycle();			// Template Method
		//
		// virtual functions, 由繼承者提供implementation
		//
		virtual ~CGameState() {}								// virtual destructor
		virtual void OnBeginState() {}							// 設定每次進入這個狀態時所需的初值
		virtual void OnInit() {}								// 狀態的初值及圖形設定
		virtual void OnKeyDown(UINT, UINT, UINT) {}				// 處理鍵盤Down的動作
		virtual void OnKeyUp(UINT, UINT, UINT) {}				// 處理鍵盤Up的動作
		virtual void OnLButtonDown(UINT nFlags, CPoint point) {}// 處理滑鼠的動作
		virtual void OnLButtonUp(UINT nFlags, CPoint point) {}	// 處理滑鼠的動作
		virtual void OnMouseMove(UINT nFlags, CPoint point) {}  // 處理滑鼠的動作 
		virtual void OnRButtonDown(UINT nFlags, CPoint point) {}// 處理滑鼠的動作
		virtual void OnRButtonUp(UINT nFlags, CPoint point) {}	// 處理滑鼠的動作
	protected:
		void GotoGameState(int state);							// 跳躍至指定的state
		void ShowInitProgress(int percent, string message);						// 顯示初始化的進度
		//
		// virtual functions, 由繼承者提供implementation
		//
		virtual void OnMove() {}								// 移動這個狀態的遊戲元素
		virtual void OnShow() = 0;								// 顯示這個狀態的遊戲畫面
		CGame *game;
		CMovingBitmap loadingBitmap;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class是遊戲的核心，控制遊戲的進行
	// 一般的遊戲並不需直接操作這個物件，因此可以不管這個class的使用方法
	/////////////////////////////////////////////////////////////////////////////

	class CGame {
	public:
		CGame();										// Constructor
		~CGame();										// Destructor
		bool IsRunning();								// 讀取遊戲是否正在進行中
		void OnDraw();									// 對應CGameView的OnDraw()
		void OnFilePause();								// 遊戲暫停
		void OnInit();									// 遊戲繪圖及音效的初始化
		void OnInitStates();							// 遊戲各狀態的初值及圖形設定
		bool OnIdle();									// 遊戲的主迴圈
		void OnKeyDown(UINT, UINT, UINT);				// 處理鍵盤Down的動作
		void OnKeyUp(UINT, UINT, UINT);					// 處理鍵盤Up的動作
		void OnKillFocus();								// 遊戲被迫暫停
		void OnLButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);    // 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnResume();								// 處理自「待命」還原的動作
		void OnSetFocus();								// 處理Focus
		void OnSuspend();								// 處理「待命」的動作
		void SetGameState(int);
		static CGame *Instance();
	private:
		bool			running;			// 遊戲是否正在進行中(未被Pause)
		bool            suspended;			// 遊戲是否被suspended
		const int		NUM_GAME_STATES;	// 遊戲的狀態數(3個狀態)
		CGameState		*gameState;			// pointer指向目前的遊戲狀態
		CGameState		*gameStateTable[3];	// 遊戲狀態物件的pointer
		static CGame	instance;			// 遊戲唯一的instance
	};

	class CTextDraw {
	public:
		void static Print(CDC *pDC, int x, int y, string str);
		void static ChangeFontLog(CDC* pDC, CFont* &fp, int size, string fontName, int weight = 500);
	};

}