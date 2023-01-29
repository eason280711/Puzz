# Intro
A library for application development.

# Feature

- Render
    - 應用程式畫面渲染

- Feature module/Plugin
    - 功能模組，可以實現自定義的功能模組，並且添加在應用程式中使用。
        - 網路
        - 資料庫
        - 音效

- Resource Manager
    - I/O
        - 資源管理
        - 資源載入器

- Layer
    - 分層架構，可以將應用程式的功能模組分層。

- script
    - 腳本功能，實現加載腳本，與運行時執行腳本。

- GUI
    - GUI系統，實現GUI的設計與運行。

- State and Event System
    - 狀態機與事件系統，實現狀態機與事件的設計與運行。

# How to use

## As a library
pseudocode
```cpp
#include <puzzlib.h>

class myApplication : public puzz::Application
{
public:
    myApplication(){};
    ~myApplication(){};
    
    class GUI
    {
    public:
        /*實現 GUI、狀態機與事件的設置*/
    };
    
    ...
    /* 定義Class實現應用程式邏輯... */

    virtual void Run()
    {
        while (/*application loop*/)
        {
            /* RuntimeModule && Manager Tick() */
        }
    };

    virtual void Init()
    {
        /* RuntimeModule && Manager startUp() */
    }

    virtual void ShotDown()
    {
        /* RuntimeModule && Manager shutDown() */
    }
};

puzz::ref_ptr<puzz::Application> puzz::CreateApplication()
{
    return new myApplication();
}

```

## Editor (非主要內容)
![](https://i.imgur.com/mVMNkwr.png)