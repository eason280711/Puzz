# HighLevelDesignDecisions

**Project Name**:首選 Puzz，指框架模組化管理(設想)的設計。

**Language**:C++20 (暫定)

**Build tool**:根據最廣泛的選擇，使用CMake。

**Source code control**:git hosted on github

**Windowing**:以本地原生的Windowing集成在核心中，也能使用第三方函式庫取代。

**Namespace**:puzz 用於 Puzz庫中所有類別的功能。

**Memory**:(暫無)

**Unification**:(暫無)

**Design Patterns**:(暫無)

**Core Components**:
 - 框架核心是一個應用程式迴圈，負責處理事件、狀態、渲染等等功能。
 - 將包含一個基本渲染管理器來處理圖形(暫定)。
 - 一個動態加載插件的系統，實現可擴展性。

**Extensibility**:
 - 使用者可以創建系統與管理器來擴展框架，添加至迴圈中進行更新或是渲染。
 - 框架以模塊化設計，方便使用者新增或是擴展

**IO** : 常用的資源管理、載入器。