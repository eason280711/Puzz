# 目錄
- [開發日誌](#開發日誌)
    - [2023/1/25](#2023/1/25)
    - [2023/1/26](#2023/1/26)
    - [2023/1/27](#2023/1/27)
    - [2023/1/28](#2023/1/28)
    - [2023/1/29](#2023/1/29)
- [近期計畫](#近期計畫)

# 開發日誌

這是開發時的日誌，記錄開發過程中遇到困難。過程中遇到的問題與解決方法會記錄在這裡，以便日後查閱。

主要紀錄：

- 過程與問題
- 解決方法
- 參考資料
- 開發心得

---

## 2023/1/25
(設計階段)
因為希望能夠實現一個架構完整、可擴充的程式，因此每一步都要先規劃好，並且計畫先實現一個簡單的版本，再慢慢擴充。

## 2023/1/26

在思考設計架構中，我認為我將來會想實現自定義容器，因此我定義了容器的介面，並且將容器的實現方式抽象出來，這樣在未來我想要實現自定義容器時，只需要實現容器並修改模板，而不需要修改原本的程式碼。因此我在`puzz::Container`中先簡單實現了`puzz::Array`、`puzz::TreeMap`。並且也實現一個簡單的計數智慧指標`puzz::ref_ptr`。

## 2023/1/27

一個簡單的OO的多態問題，我需要在一個vector中存放繼承自同一個基底類別的不同類別的物件，這在未來設計中會有很多的應用，例如規劃Layer的架構時，勢必需要有容器存放繼承自puzz::RuntimeModule的各種不同的功能模組。

在這裡先跳過了以`vector<Base>`作為容器的問題，因為在賦值時就會將物件向上轉型為Base類別了。
 
```cpp
class Base {
public:
    void print() { cout << "Base" << endl;};
};

class Derived : public Base {
public:
    void print() { cout << "Derived" << endl;};
};

int main()
{
    vector<Base*> ls = {new Derived};
    for(auto &a:ls)
        a -> print();
    return 0;
}
```
輸出結果
```
Base
```

在上面的情況中，由於靜態多型的關係，vector中的物件會被視為Base類別，因此在呼叫print()時，會呼叫Base類別的print()，而不是Derived類別的print()。

解決方法可以將Base類別的print()設為虛擬函式，這樣在呼叫時，會根據物件的實際類別來決定要呼叫哪個print()。

```cpp
class Base {
public:
    virtual void print() { cout << "Base" << endl;};
};

class Derived : public Base {
public:
    void print() override { cout << "Derived" << endl;};
};

int main()
{
    vector<Base*> ls = {new Derived};
    for(auto &a:ls)
        a -> print();
    return 0;
}
```
輸出結果
```
Derived
```

題外話，在C++沉思錄中提出了一個代理 (Surrogate) 類的概念，也是用來解決這個問題的，有興趣的可以看看。( C++沉思錄的內容太艱深了(X)，因此沒有採納那個做法 )。

但這個問題並沒有在這裡完全解決。接下來一個問題是，假設我們需要實現一個Clone函式，這個函式會根據物件的實際類別來複製一個新的物件，並且返回該物件的指標。依照上面的程式碼，我們可以這樣寫：

```cpp
class Base {
public:
    virtual void print() { cout << "Base" << endl;};
    virtual Base* Clone() {return new Base(*static_cast<Base*>(this));};
};

class Derived : public Base {
public:
    void print() override { cout << "Derived" << endl;};
    Base* Clone() override {return new Derived(*static_cast<Derived*>(this));}
};

int main()
{
    vector<Base*> ls = {new Derived};
    for(auto &a:ls)
    {
        auto tmp = a -> Clone();
        tmp -> print();
    }
    return 0;
}
```

但是，這樣寫的話，我們就必須在每個繼承自Base的類別中都實現一個Clone函式，這樣的話，如果我們有很多的類別繼承自Base，那麼就必須在每個類別中都實現一個Clone函式，這樣的話，就會造成程式碼的重複。

所以，我們需要一個方法，可以讓我們在繼承自Base的類別中，只需要實現一個Clone函式，就可以複製出該類別的物件，而不需要在每個類別中都實現一個Clone函式。因此，我們可以使用CRTP (Curiously Recurring Template Pattern) 來解決這個問題。關於CRTP的介紹可以參考網路上的資料，這裡就不再贅述。

我們可以這樣寫：

```cpp
template<typename T>
class Base {
public:
    virtual void print() { cout << "Base" << endl;};
    virtual Base* Clone() {return new T(*static_cast<T*>(this));};
};

class Derived : public Base<Derived> {
public:
    void print() override { cout << "Derived" << endl;};
};

int main()
{
    vector<Base<Derived>*> ls = {new Derived};
    for(auto &a:ls)
    {
        auto tmp = a -> Clone();
        tmp -> print();
    }
    return 0;
}
```

但是這種寫法有一個缺點，就是我們必須要將vector的型別設為`vector<Base<Derived>*>`，這會讓我們不能將Derived以外的類別放入vector中，因此我們可以再改寫一下，讓我們可以維持vector的型別設為`vector<Base*>`。

下面這種作法實現了一個`CRTP`的類別，這個類別的作用是繼承自Base，並且將Base的Clone函式覆寫，這樣的話，我們就可以在繼承自Base的類別中，只需要實現一個Clone函式，就可以複製出該類別的物件，而不需要在每個類別中都實現一個Clone函式。而且，我們可以保持vector的型別設為`vector<Base*>`，因為CRTP的類別繼承自Base，所以我們可以將繼承自CRTP的類別放入vector中。

```cpp
class Base {
public:
    virtual void print() { cout << "Base" << endl;};
    virtual Base* Clone() {return new Base(*static_cast<Base*>(this));};
};

template<typename Derived,typename Base>
class CRTP : public Base {
    Base* Clone() override {return new Derived(*static_cast<Derived*>(this));}
};

class Derived : public CRTP<Derived,Base> {
public:
    void print() override { cout << "Derived" << endl;};
};

int main()
{
    vector<Base*> ls = {new Derived};
    for(auto &a:ls)
    {
        auto tmp = a -> Clone();
        tmp -> print();
    }
    return 0;
}
```

## 2023/1/28

修改了Inherit的實現方法，參考自[這裡](https://www.fluentcpp.com/2017/09/12/how-to-return-a-smart-pointer-and-use-covariance/)。主要原因是因為協變返回類型(Covariant Return Type)。可以看看以下範例:

```cpp
struct Base {};
struct Derived : Base {};

struct Parent
{
   virtual Base * foo();
} ;

struct Child : Parent
{
   virtual Derived * foo() override ;
} ;
```

在這個範例中，我們可以看到，Child繼承自Parent，並且覆寫了Parent的foo函式。但我們知道，在C++中覆寫函式時，函式的參數列表必須與被覆寫的函式的參數列表相同，但是，回傳值的型別可以是被覆寫函式回傳值的**子類別**。因此，我們可以看到，Child的foo函式的回傳值是Derived的指標，而Parent的foo函式的回傳值是Base的指標，並且可以成功編譯。這就是協變返回類型(Covariant Return Type)

**但是**，這對於智慧指標來說，就不能這麼做了。因為，如果我們將Parent的foo函式的回傳值改為`std::unique_ptr<Base>`，那麼Child的foo函式的回傳值就必須是`std::unique_ptr<Base>`，而不能是`std::unique_ptr<Derived>`。

```cpp
#include <memory>

struct Base {};
struct Derived : Base {};

struct Parent
{
   virtual std::unique_ptr<Base> foo();
} ;

struct Child : Parent
{
   virtual std::unique_ptr<Derived> foo() override ;
} ;
```

這會造成編譯錯誤。

那解決方法在上面的文章中有提到，而且還寫得挺仔細的，這裡就不再贅述了。這個專案中Inherit的實現方法也是修改自上面的文章的實現。

## 2023/1/29

主要完成狀態機的實現。修改自原本寫過的選課系統的專案，就像原本提到的，因為每一步都要重新思考、琢磨，所以感覺架構上比較乾淨，而且更好理解。

還修改了Inherit無法將建構函式傳遞給子類別的問題。

# 近期計畫

- [x] 完成狀態機的實現
- [ ] 完成Layer的實現
- [ ] 完成功能模塊的實現
- [ ] 實現一個不使用GUI的貪吃蛇小遊戲
- [ ] 完成腳本系統的實現