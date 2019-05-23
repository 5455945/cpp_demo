#include "../message_bus/MessageBus.hpp"

// test01
void TestMsgBus() {
    MessageBus bus;
    // 注册消息
    bus.Attach([](int a) {std::cout << "no reference" << a << std::endl;});
    bus.Attach([](int& a) {std::cout << "lvalue reference" << a << std::endl;});
    bus.Attach([](int&& a) {std::cout << "rvalue reference" << a << std::endl;});
    bus.Attach([](const int& a) {std::cout << "const lvalue reference" << a << std::endl;});
    bus.Attach([](int a) {std::cout << "no reference has return value and key" << a << std::endl;});

    int i = 2;
    // 发送消息
    bus.SendReq<void, int>(2);
    bus.SendReq<int, int>(2, "a");
    bus.SendReq<void, int&>(i);
    bus.SendReq<void, const int&>(2);
    bus.SendReq<void, int&&>(2);

    // 移除消息
    bus.Remove<void, int>();
    bus.Remove<int, int>("a");
    bus.Remove<void, int&>();
    bus.Remove<void, const int&>();
    bus.Remove<void, int&&>();

    // 发送消息
    bus.SendReq<void, int>(2);
    bus.SendReq<int, int>(2, "a");
    bus.SendReq<void, int&>(i);
    bus.SendReq<void, const int&>(2);
    bus.SendReq<void, int&&>(2);
}

// test02
MessageBus g_bus;
const std::string Topic = "Drive";
struct Subject {
    void SendReq(const std::string& topic) {
        g_bus.SendReq<void, int>(50, topic);
    }
};

struct Car {
    Car() {
        g_bus.Attach([this](int speed) {Drive(speed);}, Topic);
    }

    void Drive(int speed) { std::cout << "Car Drive " << speed << std::endl; }
};

struct Bus {
    Bus() { g_bus.Attach([this](int speed) {Drive(speed);}, Topic); }

    void Drive(int speed) { std::cout << "Bus Drive " << speed << std::endl; }
};

struct Truck {
    Truck() { g_bus.Attach([this](int speed) { Drive(speed);}); }

    void Drive(int speed) { std::cout << "Truck Drive " << speed << std::endl; }
};

void TestBus() {
    Subject subject;
    Car car;
    Bus bas;
    Truck truck;
    subject.SendReq(Topic);
    subject.SendReq("");

    g_bus.Remove<void, int>();
    subject.SendReq("");
}

// test03 通过MessageBus将复杂对象关系解耦
MessageBus g_bus03;
const std::string Topic03 = "Drive";
const std::string CallBackTopic = "DriveOk";
struct Subject03 {
    Subject03() {g_bus03.Attach([this]{DriveOk();}, CallBackTopic); }

    void SendReq(const std::string& topic) { g_bus03.SendReq<void, int>(50, topic); }

    void DriveOk() { std::cout << "Drive Ok" << std::endl; }
};

struct Car03 {
    Car03() {g_bus03.Attach([this](int speed) {Drive(speed);}, Topic03); }

    void Drive(int speed) {
        std::cout << "Car Drive " << std::endl;
        g_bus03.SendReq<void>(CallBackTopic);
    }
};

struct Bus03 {
    Bus03() {g_bus03.Attach([this](int speed) {Drive(speed);}); }

    void Drive(int speed) {
        std::cout << "Bus Drive " << speed << std::endl;
        g_bus03.SendReq<void>(CallBackTopic);
    }
};

struct Truck03 {
    Truck03() { g_bus03.Attach([this](int speed){Drive(speed);}); }

    void Drive(int speed) {
        std::cout << "Truck Drive " << speed << std::endl;
        g_bus03.SendReq<void>(CallBackTopic);
    }

};

void TestBus03() {
    Subject03 subject;
    Car03 car;
    Bus03 bas;
    Truck03 truck;
    subject.SendReq(Topic03);
    subject.SendReq("");

    g_bus.Remove<void, int>();
    subject.SendReq("");
}

int main() {
    TestMsgBus();
    TestBus();
    TestBus03();
    return 0;
}