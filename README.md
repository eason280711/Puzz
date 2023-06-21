# Puzz

![](./docs/Image/Logo.png)

--------------------------------------------------------------------------------

這是一個用來練習與實作軟體開發概念的Side Project。將設計成框架的形式，將練習將各種設計模式和物件導向的概念應用在架構與系統中。更多訊息可以看[Quick Guide](#Quick-Guide)，整理了一些開發過程的資料。

題外話，這個專案的名字是Puzz，原先是指將功能模組化管理(規劃時的想法)的設計。但後來腦袋冒出一句話"It's a C++ Puzz"，Puzzle也有謎題的意思，C++開發對我來說就像解各種謎題，總覺得這名稱真有意境，LUL。

# 進度

根據你的環境，可以使用Visual Studio或是其他IDE來開啟、建置專案。目前我只嘗試過在Windows上使用Visual Studio 2022或是Ninja來建置專案。

建置生成其中有一個檔案 `application.exe` 是應用程式的本體。可以由 `puzzlib/src/Core/Application.cpp` [檔案](https://github.com/eason280711/Puzz/blob/main/puzzlib/src/Core/Application.cpp)中的 `main` 函式來看到應用程式的原始碼。

目前的架構是以 `component` 建構 `layer`，我稱其為 `puzzles` 。`application` 則是由 `layer` 堆疊而成。可以參考 `puzzlib/src/Puzzles` 的內容。現在在 `Application.cpp` 初步實現了 `Logging`、`KeyBoard`、`Dispatchers` 的 `puzzles`，在 `Application.cpp` 展示的範例即為，當按下鍵盤時，會將按下的 `KeyBoard` 資訊輸出到 `Console` 中。這過程是經由 `Dispatchers` 傳遞事件給 `Logging`，一個跨 `layer` 的事件傳遞範例。

像是這樣
![](./docs/Image/example.png)

目前需要 pdcurses、spdlog 的 dependency 。

# Table of Contents

* [Quick Guide](#Quick-Guide)
* [Getting Started](#Getting-Started)

# Quick Guide
整理了repository中的可以參考的連結，方便閱讀。
- Build & Run
    - 快速開始 : [Quick Start](#Getting-Started)
- Code
    - 原始碼 : [Puzz/puzzlib/](https://github.com/eason280711/Puzz/tree/main/puzzlib)
    - 應用程式 : [Puzz/application/](https://github.com/eason280711/Puzz/blob/main/application)
- 參考資料
    - 開發日誌 : [Development Log](./docs/Log/DevelopmentLog.md)
    - 設計概念 : [Design](https://github.com/eason280711/Puzz/tree/main/docs/Design)
    - 外部參考資源 : [Resources](./docs/Resources/Resources.md)

# Getting Started
雖然還沒完成，但如果真的需要的話，可以使用CMake來建置專案。

```bash
# clone repository
git clone https://github.com/eason280711/Puzz.git

# make build directory
cd Puzz
mkdir build
cd build

# generate project
cmake ..
```
