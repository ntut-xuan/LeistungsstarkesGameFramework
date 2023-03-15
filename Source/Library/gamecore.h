#pragma once

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
		static void  LoadBitmapFromExistHBITMAP(int i, HBITMAP bitmap);
		static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
		static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
		static int   RegisterBitmap(char *filename, COLORREF ColorKey);
		static int   RegisterBitmapWithHBITMAP(HBITMAP hbitmap);
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
}
