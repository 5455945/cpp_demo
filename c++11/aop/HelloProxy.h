#pragma once
#include <string>
#include <iostream>

class IHello {
public:

    IHello() {
    }

    virtual ~IHello() {
    }

    virtual void Output(const std::string& str) {
        
    }
};

class Hello : public IHello {
public:
    void Output(const std::string& str) override {
        std::cout << str << std::endl;
    }
};

class HelloProxy : public IHello {
public:
    HelloProxy(IHello* p) : m_ptr(p) {
    }

    ~HelloProxy() {
        delete m_ptr;
        m_ptr = nullptr;
    }

    void Output(const std::string& str) final {
		std::cout << "Before real Output"<< std::endl;
        m_ptr->Output(str);
		std::cout << "After real Output" << std::endl;
    }
    
private:
    IHello* m_ptr;
};

//#include <memory>
//void TestProxy() {
//    std::shared_ptr<IHello> hello = std::make_shared<HelloProxy>(new Hello());
//    hello->Output("It is a test");
//}
