# Puzz

![](./Image/Logo.png)


[English](../README.md)

--------------------------------------------------------------------------------

這是一個用來練習與實作軟體開發概念的Side Project。將設計成軟體框架的形式(或是遊戲引擎)，將練習將各種設計模式和物件導向的概念應用在架構與系統中。更多訊息可以看[Quick Guide](#Quick-Guide)，整理了一些開發過程的資料。

題外話，這個專案的名字是Puzz，原先是指學習過程中看到將功能模組化管理的設計感覺就像是拼圖。開發過程中後來腦袋冒出一句話"It's a C++ Puzz"，Puzzle也有謎題的意思，C++開發對我來說就像解各種謎題，總覺得這名稱真有意境，LUL。

# Progress

- [X] 系統核心架構
- [X] 完成功能模塊
- [x] 渲染支持
- [X] 2D 物理引擎
- [X] Runtime Script 系統
- [X] GUI
- [ ] 實現一個小遊戲
- [ ] 跨平台
- [ ] 測試
- [ ] Debug Tool
- [ ] 文檔
- [ ] 範例

目前實現了一個簡易的 Editor，僅目前有主要的應用程式渲染畫面與一個的文字編輯器。這是與 Box2D 物理引擎互動的範例。
![](https://imgur.com/VnImKIE.gif)

Runtime DLL Reload
![](https://imgur.com/q5vk5OH.gif)

Debug ConSole
![](https://imgur.com/MniullZ.gif)

# Future Work

- Neural Network Models Loading Puzzle
- Network Puzzle
...

# Table of Contents

* [Architecture](#Architecture)
* [Quick Guide](#Quick-Guide)
* [Getting Started](#Getting-Started)
    * [Dependency](#Dependency)
    * [Build Step](#Build-Step)

# Architecture

我簡單的使用底下這張圖來介紹架構與運行原理。(或許改天我會正式的用 UML 重新繪製一次)

![](./Image/Puzz.drawio.svg)

Puzz 會被編譯成一個動態函式庫 (DLL)，其中 EntryPoint 包含了 main function，因此你僅需要 include puzzlib 的 header 即可完成應用程式的建立。你可以建立一個 Class 並繼承自 `puzz::Application` ，這將可以讓你進行應用程式的創立與流程的控制。就像 [application/src/Application.cpp](https://github.com/eason280711/Puzz/blob/main/application/src/Application.cpp) 示範的一樣。

而在 [puzzlib/src/Core/Application](https://github.com/eason280711/Puzz/blob/main/puzzlib/src/Core/Application.cpp) 中，你可以看見預設的 `puzz::Application` 與其實現。

在 Init function 裡，可以使用 PushLayer 將實現的 "Puzzle" push 進入 Application 的 Layer Array。"Puzzle" 是以 Component 建構成的 Layer 的最小單位。在 [puzzlib/src/Puzzles](https://github.com/eason280711/Puzz/tree/main/puzzlib/src/Puzzles) 裡有我為框架初步實現的幾個 Puzzle。Puzzle 的實現應該是要盡量不與其他 Puzzle 耦合的，因此除了用於處理 Event 的 Dispatcher 以外，移除任何 Puzzle 都不應該影響到程式的運行，除非是建立在某個功能上的加強。

這是一個範例。當你僅使用 `Logging`、`KeyBoard`、`Dispatchers` 這幾個 Puzzles 時呈現的畫面，將可以看到由 `KeyBoard` 所偵測的按鍵事件，並由 `Logging` 輸出到 Console 中。

![](./Image/example.png)

而當你新增 `Console` 這個 Puzzle 時，將可以看到一個簡易的 `Console` ， 其將 `Logging` 重新導向到 `Console` 的畫面中。這個過程是低耦合的，你可以在任何時候新增或移除 `Console` 這個 Puzzle，而不會影響到其他的 Puzzle。

![](./Image/terminal.png)

而 Run Functioin 裡則是先處理 Event Queue 裡的事件再依序進行 Puzzles 的 Tick 更新，Dispathcer 作為處理事件的 Puzzle，提供了兩種方式 dispatch Event，一種是使用 `Dispatcher::dispatchEvent()` 這將即時的傳送 Event 到有 Register 該 Dispatcher 的 Listener 並在當下直接 Handle Event。第二種是。在全局都能使用 `Dispatcher::enqeueEvent()` 來將 Event enqeue，並就像是上面 Run Function 所描述的，將在每輪更新之前處理 Event Queue 裡的事件。

至於最上面的架構圖的 Plugin 部分，Plugin 是加載 DLL 來實現的。設計為使用者能夠撰寫 Class 繼承 Puzzle 的 component ， DllManager 會讀取特定 DLL 並獲取定義的 component 並在更新時同時的調用 Tick function。DllManager 也是一個 component，因此可以 push 進任何 Layer。

在 Runtime 時 Dispatch Reload Event 將會重新編譯該檔案，在編譯完成後重新加載該 DLL。這將用於 Runtime 時更新 Puzzle Layer，達到不需要重新啟動程式即可修改 UI、Render 等等的功能。

# Quick Guide
整理了 repository 中的可以參考的連結，方便閱讀。
- Build & Run
    - 快速開始 : [Quick Start](#Getting-Started)
- Code
    - 原始碼 : [Puzz/puzzlib/](https://github.com/eason280711/Puzz/tree/main/puzzlib)
    - 應用程式 : [Puzz/application/](https://github.com/eason280711/Puzz/blob/main/application)
- 參考資料
    - 開發日誌 : [Development Log](./Log/DevelopmentLog.md)
    - 設計概念 : [Design](https://github.com/eason280711/Puzz/tree/main/Design)
    - 外部參考資源 : [Resources](./Resources/Resources.md)

# Getting Started
目前我只嘗試過在Windows上使用  Visual Studio 2022 來 Build Project。實際上在部分與系統相關的功能上的 Source Code 使用了 Windows API ，將來會進一步對那些功能進行抽象並新增跨平台支持。而在 Windows 上雖然可以使用其他的工具來 build，例如 Ninja。但在插件系統中我使用 MSBuild 指令來進行 DLL 的編譯，因此 Visual Studio 的環境目前還是必須的。
## Dependency
目前需要的 dependency 如下， 基本上我都使用 [vcpkg](https://github.com/Microsoft/vcpkg) 管理套件，其他項目例如 Spdlog 或是 imgui 的第三方擴展可以在 vendor 裡的 submodules 找到。

- Main
    - [Magnum](https://github.com/mosra/magnum)
    - [Corrade](https://github.com/mosra/corrade)
    - [Box2D](https://github.com/erincatto/box2d)
    - [Glfw3](https://github.com/glfw/glfw)
    - [Imgui](https://github.com/ocornut/imgui)
    - [Ftxui](https://github.com/ArthurSonzogni/FTXUI)
    - [Spdlog](https://github.com/gabime/spdlog)
- Imgui Extension
    - [ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)
    - [ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog)

## Build Step

雖然還沒完成，但如果真的需要的話，可以使用CMake來生成專案的建構檔。
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
