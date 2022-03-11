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



## Still Unsolve Bug

- 在 `OnBeginState` 時，讀入不合法的（不存在的、不是圖片的）圖片會顯示 

  `A bitmap must be loaded before ShowBitmap() is called !!!`



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



## Application

### 讓一個物件不停的動畫循環

```cpp
CMovingBitmap bitmap;

# -- onBeginState --
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);
bitmap.SetAnimation(5, false);

# -- onShow --

bitmap.showBitmap();
```



### 碰到一個物件之後執行動畫

```cpp
CMovingBitmap bitmap;

# -- onBeginState --

bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);

# -- onMove --
bitmap.SetAnimation(5, false);

# -- onShow --

bitmap.showBitmap();
```



### 同一個物件呈現不同圖片

```cpp
CMovingBitmap bitmap;

# -- onBeginState --

bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);

# -- onMove --
bitmap.SelectShowBitmap(1)

# -- onShow --
bitmap.showBitmap();
```





## 銘謝

謝謝 國立臺北科技大學 陳偉凱教授 開發了這個遊戲框架，並且謝謝 國立臺北科技大學 陳碩漢教授 同意這個框架能夠公開使用。
