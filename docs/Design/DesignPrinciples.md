# Design Principles

這是開發過程中我想要遵守的幾個原則。

## Principles

1. 使用統一的基類或介面來定義系統與管理器的共同功能，使用相同的代碼來實現不同的系統與管理器。
    - 使用面向對象設計原則，將系統與管理器的不同功能抽象為物件，並透過繼承和多型實現代碼的重用。例如，可以將管理器分為基本管理器類別和特定管理器類別，基本管理器類別提供公共功能，而特定管理器類別則繼承基本管理器類別並提供特定功能。
    - 使用模塊化設計原則，將系統與管理器的不同功能模組化，並透過接口和依賴性反轉原則實現代碼的模組化。例如，可以將管理器分為資源管理器、圖形管理器、腳本管理器等不同模組，並在不同模組之間建立接口以實現互相訪問。
2. 使用模板或泛型類別來實現系統與管理器，這樣可以使用相同的代碼來支持不同類型的對象。
3. 使用設計模式，如工廠模式、單例模式等，來確保系統與管理器的一致性和可維護性。
    - 使用組合模式，將不同的物件組合在一起，實現系統與管理器的靈活性和擴展性。例如，可以將管理器中的不同物件組合在一起，實現不同管理器之間的互動和整體管理。例如圖形管理器可以組合在應用程式迴圈中，負責處理圖形渲染，而資源管理器則可以組合在圖形管理器中，負責載入和管理圖形資源。
    - 使用策略模式，將不同的策略實現為物件，並將其選擇性地應用到系統與管理器中。例如，可以將圖形渲染策略實現為物件，並在圖形管理器中選擇性地使用，實現不同的圖形渲染效果。
    - 使用觀察者模式，將系統與管理器之間的事件通知實現為物件。例如，可以將應用程式迴圈中的事件通知實現為物件，並在圖形管理器、資源管理器等其他管理器中註冊監聽，實現系統與管理器之間的互動。
    - 使用工廠模式，將系統與管理器的創建實現為物件，並將其選擇性地應用到系統與管理器中。例如，可以將圖形管理器的創建實現為物件，並在應用程式迴圈中選擇性地使用，實現不同類型的圖形管理器。
    - 使用建造者模式，將系統與管理器的配置實現為物件，並將其選擇性地應用到系統與管理器中。例如，可以將圖形管理器的配置實現為物件，並在應用程式迴圈中選擇性地使用，實現不同配置的圖形管理器。
    - 使用模板方法模式，將系統與管理器的基本流程實現為模板方法，並在其中選擇性地使用策略模式，實現不同的邏輯。例如，可以將圖形渲染策略實現為物件，並在圖形管理器中選擇性地使用，實現不同的渲染邏輯。
    - 使用命令模式，將系統與管理器的操作實現為命令物件，並在應用程式迴圈中選擇性地使用，實現不同的操作。
    - 使用觀察者模式，將系統與管理器之間的通知實現為觀察者，並在系統與管理器中選擇性地使用，實現不同的通知機制。
4. 使用清晰的命名空間和類別層次結構來組織代碼，這樣可以更容易地理解系統與管理器之間的關係。
5. 使用符合標準的代碼風格和程式碼架構，如 SOLID 原則 (可參考不同C++的標準)，來確保代碼的可讀性和可維護性。
6. 使用單元測試來確保系統與管理器的正確性和穩定性。
7. 使用版本控制軟體，如 git 來管理代碼，並且利用分支管理機制來保存不同版本的代碼。
8. 使用文件和文檔管理工具，如 Doxygen 來生成代碼文檔，幫助開發人員理解代碼。
9. 使用優化工具，如性能測試和優化工具，來確保系統與管理器的高效性。
10. 保持開放心態，不斷學習新的技術和工具，並且及時將其適用於系統與管理器的開發實踐中。