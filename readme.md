# Leistungsstarkes Game Framework

LGF (Leistungsstarkes Game Framework) 是一款基於陳偉凱老師的 Game Framework 加上些許功能的 Powerful Game Framework。

專案不保證長期維護，有任何問題或者任何其他想要的 feature，請丟 issue，祝使用愉快 :D



## Installation

1. 將此專案 clone 下來
2. 替換原有的 Game Framework / 直接使用這個 Game Framework.

（基本上是相容於舊框架的，因為是基於舊框架新增更多的 feature 以及修正 bug）



## Feature

### 2022-03-06

- 修正了 `CInteger` 的 Bug，現在可以正常呈現。
- **半修正**了 `CMovingBitmap.showBitmap(double factor)` 的 Bug，當 `factor` 等於 `0` 時視為隱藏圖片。
- 可以隱藏 `CMovingBitmap` 的圖片。
- 可以讀入多個 `CMovingBitmap` 的圖片，並且選擇欲呈現的圖片。
- 可以讀入多個 `CMovingBitmap` 的圖片，並且利用 `SetAnimation(int delay, bool once)` 來製作動畫。
- 廢棄 `CAnimation` 的作法。

### 2022-03-11

- 讓 `CInteger` 可以自由顯示是否要顯示前導零。



### 2022-06-17

- 【New Feature】修正了全螢幕時的黑邊問題，並且會將遊戲視窗絕對置中。
- 【New Feature】將動畫每幀的延遲加上精準時間。
- 【New Feature】支援以 `vector<string>` 讀取每幀的畫面。
- 【New Feature】新增了 `CTextDraw` 類別，**畫上文字時請使用這個類別的函式，全螢幕的字位移才會正確**
- 【Bug】修正了 CMovngBitmap 在執行動畫時會出現的小 bug。



### 2023-02-22

- 創立了純淨版（Purified）的 Leistungsstarkes Game Framework 專案，可直接建置方案並執行。
- 修改了檔案架構，從原先將所有的 `.cpp` 放入 `Source` 資料夾，改為在 `Source` 建立一個資料夾架構來存放 `.cpp` 檔案。
- 修改了檔案架構，將 `/RES` 重新命名為 `Resources` 來釐清名稱。
- 創立 `GAME_TITLE` 的定義（`#define`），使框架使用者能夠變更遊戲標題。
- 將 `mygame.cpp` 分割成三個不同的檔案，分別實作 `GameStateInit`、`GameStateRun` 與 `GameStateOver` 的類別。
- 重構了部分的 code 使得重複的 code 出現的次數減少。
- 抽離遊戲設定參數至 `config.cpp`，讓使用者不須也不應更改 `/Library` 與 `/Core` 的程式碼。



## Documents

### void CMovingBitmap::LoadBitmap(char* , COLORREF)

讀取一張圖片。

```c++
CMovingBitmap bitmap;
bitmap.LoadBitmap("RES/bitmap.bmp", RGB(255, 255, 255));
bitmap.SetLeftRight(0, 0);

# -- on show --

bitmap.ShowBitmap();
```



### void  CMovingBitmap::LoadBitmap(vector<char*>, COLORREF = CLR_INVALID);

讀取多張圖片，索引值從 `0` 開始。

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"}, RGB(255, 255, 255));
bitmap.SetLeftRight(0, 0);

# -- on show --

bitmap.ShowBitmap(); // 預設呈現第一張 (index = 0)。
```



### void CMovingBitmap::UnshowBitmap()

隱藏當前的 `CMovingBitmap`。

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.setLeftRight(0, 0);

# -- on show --
bitmap.showBitmap(); // 預設呈現第一張 (index = 0)。

/* Do something... */

bitmap.UnShowBitmap(); // 隱藏圖片。
```



### void  CMovingBitmap::SelectShowBitmap(int select)

選擇要呈現的 `CMovingBitmap`。

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetLeftRight(0, 0);
bitmap.SelectShowBitmap(1); // 設定呈現第二張圖片

# -- on show --

bitmap.showBitmap(); // 呈現第二張圖片
```



### void CMovingBitmap::SetAnimation(int delay, bool once)

設定當前的 `CMovingBitmap` 為一個動畫。

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetLeftRight(0, 0);
bitmap.SelectShowBitmap(1); // 設定呈現第二張圖片
bitmap.SetAnimation(5, false); // 無限循環呈現

# -- on show --

bitmap.showBitmap(); // 呈現第二張圖片
```



### void CInteger::ShowBitmap(bool leadingZero)

顯示 `CInteger` 是否出現前導零。

```cpp
CInteger health = CInteger(4); //設定最大長度為 4，預設為 5。
health.SetInteger(1000);
health.SetTopLeft(312, 373);

# -- on show --
health.showBitmap(false); // 不顯示前導零
```



### void CMovingBitmap::LoadBitmapByString(vector\<string> filename, COLORREF color)

利用 `vector<string>` 讀取多張圖片，索引值從 `0` 開始。

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.setLeftRight(0, 0);

# -- on show --
bitmap.showBitmap(); // 預設呈現第一張 (index = 0)。

/* Do something... */

bitmap.UnShowBitmap(); // 隱藏圖片。
```



### int CMovingBitmap::GetSelectShowBitmap()

獲得目前呈現的圖片索引值。



### bool CMovingBitmap::IsAnimationDone()

確認動畫是否正在執行，僅限於動畫正在執行 `ToggleAnimation()`。



### void  CMovingBitmap::ToggleAnimation()

運行動畫一次，並且使得 `IsAnimationDone()` 可用。



### int CMovingBitmap::GetMovingBitmapFrame()

確認這個 `CMovingBitmap` 物件有多少幀動畫。



### void CTextDraw::ChangeFontLog(CDC *pDC, int size, string fontName, int weight)

更改文字的樣式、文字與粗體。

```cpp
CDC *pDC = CDDraw::GetBackCDC();
CFont *fp;

pDC->SetBkMode(TRANSPARENT);
pDC->SetTextColor(RGB(255, 255, 255));

/* 變更字體，weight = 800 為粗體，500 為一般 */
CTextDraw::ChangeFontLog(pDC, fp, 40, "Noto Sans TC", 800);
CTextDraw::Print(pDC, 50, 50, "Hello World!");
```



### void CTextDraw::Print(CDC *pDC, int x, int y, string str)

將文字呈現在指定的座標上。

```cpp
CDC *pDC = CDDraw::GetBackCDC();
CFont *fp;

pDC->SetBkMode(TRANSPARENT);
pDC->SetTextColor(RGB(255, 255, 255));

/* 變更字體 */
CTextDraw::ChangeFontLog(pDC, fp, 40, "Noto Sans TC");
CTextDraw::Print(pDC, 50, 50, "Hello World!");
```







## Example

### 讓一個物件不停的動畫循環

```cpp
CMovingBitmap bitmap;

# -- onInit --
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);
bitmap.SetAnimation(5, false);

# -- onShow --

bitmap.showBitmap();
```



### 碰到一個物件之後執行動畫

```cpp
CMovingBitmap bitmap;

# -- onInit --

bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);
bitmap.SetAnimation(200, false);

# -- onEvent --
bitmap.ToggleAnimation(1);

# -- onShow --

if(bitmap.IsAnimationDone()){
    if (hidden_code[current_stage][i][j] == 0) {
		bitmap.showBitmap();
    }
}else{
    bitmap.showBitmap();
}
```



### 同一個物件呈現不同圖片

```cpp
CMovingBitmap bitmap;

# -- onInit --

bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);

# -- onMove --
bitmap.SelectShowBitmap(1)

# -- onShow --
bitmap.showBitmap();
```





## 銘謝

謝謝 國立臺北科技大學 陳偉凱教授 開發了這個遊戲框架

並且謝謝 國立臺北科技大學 陳碩漢教授 同意這個框架能夠公開使用。
