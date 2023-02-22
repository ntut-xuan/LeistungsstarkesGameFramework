/////////////////////////////////////////////////////////////////////////////
// 定義遊戲可設定的環境與條件
/////////////////////////////////////////////////////////////////////////////

#define GAME_TITLE           "Game"
#define SIZE_X				 1400		// 設定遊戲畫面的解析度為640x480
#define SIZE_Y				 900		// 註：若不使用標準的解析度，則不能切換到全螢幕
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
