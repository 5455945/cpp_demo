#include "../task_cpp/TaskCpp.h"
#include <numeric>

void test_variant01() {
    typedef Variant<int, double, string, int> cv;
    // 根据index获取类型
    cout << typeid(cv::IndexType<1>).name() << endl;
    
    // 根据类型获取索引
    cv v = 10;
    int i = v.GetIndexOf<string>();
    
    // 通过一组lambda访问vairant
    v.Visit([&](double i) {cout << i << endl; }, [&](short i) {cout << i << endl; }, [](int i) {cout << i << endl; },
        [](string i) {cout << i << endl; }
    );
    
    bool emp1 = v.Empty();
    cout << v.Type().name() << endl;
}

void TestTask() {
    Task<void()> task([] {cout << 1 << endl; });
    task.Wait();
    
    Task<void()> task1 = [] {cout << 1 << endl; };
    task1.Wait();
    
    Task<int()> task2 = [] {cout << 1 << endl; return 1; };
    cout << task2.Get() << endl;
    
    Task<int(int)> task3 = [](int i) {cout << i << endl; return i; };
    cout << task3.Get(3) << endl;
}

void PrintThread() {
    cout << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

void TestWhenAll() {
    vector<Task<int()>> v = {
        Task<int()>([] {PrintThread(); std::this_thread::sleep_for(std::chrono::seconds(5)); return 1; }),
        Task<int()>([] {PrintThread(); return 2; }),
        Task<int()>([] {PrintThread(); return 3; }),
        Task<int()>([] {PrintThread(); return 4; })
    };
    
    cout << "when all " << endl;
    WhenAll(v).Get();
}

void TestWhenAny() {
    vector<Task<int()>> v = {
        Task<int()>([] {PrintThread(); std::this_thread::sleep_for(std::chrono::seconds(5)); return 1; }),
        Task<int()>([] {PrintThread(); return 2; }),
        Task<int()>([] {PrintThread(); return 3; }),
        Task<int()>([] {PrintThread(); return 4; })
    };
    
    cout << "when any " << endl;
    WhenAny(v).Then([](std::pair<int, int>& result) {
        cout << " index " << result.first << " result " << result.second << endl;
        return result.second;
    }).Then([](int result) {cout << "any result: " << result << endl; }).Get();
}

void TestTaskGroup() {
    Task<int()> t1([] {PrintThread(); return 1; });
    Task<double()> t2([] {PrintThread(); return 2.123; });
    Task<void()> t3([] {PrintThread(); });
    Task<string()> t4([] {PrintThread(); return "ok"; });
    
    TaskGroup group;
    group.Run(t1);
    group.Run(t2);
    group.Run(t3);
    group.Run(t4);
    
    // 如果你觉得这样一个一个Run加入任务，你也可以一起Run
    group.Run(t1, t2, t3, [] {PrintThread(); return 1; });
    
    group.Wait();
}

bool check_prime(int x) { // 为了体现效果, 该函数故意没有优化.
    for (int i = 2; i < x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

void TestParallelFor() {
    vector<int> v;
    for (int i = 0; i < 100000; i++) {
        v.push_back(i + 1);
    }
    
    //boost::timer t;
    
    ParallelForeach(v.begin(), v.end(), check_prime);
    ParallelForeach(v.begin(), v.end(), check_prime);
    
    //cout << "taskcpp: " << t.elapsed() << endl;
}

void TestParaInvoke() {
    auto f = [] {cout << "1" << endl; return 1; };
    ParallelInvoke(f, [] {cout << "2" << endl; });
}

void TestParallelSum() {
    vector<int> v;
    const int Size = 100000000;
    v.reserve(Size);
    for (int i = 0; i < Size; i++) {
        v.push_back(i + 1);
    }
    
    int i = 0;
    
    //boost::timer t;
    auto r = ParallelReduce(v, i, [](const vector<int>::iterator& begin,
        vector<int>::iterator&end, int val) {
        return std::accumulate(begin, end, val);
    });
    //cout << t.elapsed() << " " << r << endl;
}

void TestFindString() {
    vector<string> v;
    v.reserve(10000000);
    for (int i = 0; i < 10000000; i++) {
        v.emplace_back(std::to_string(i + 1));
    }
    
    string init = "";
    auto f = [](const vector<string>::iterator& begin, vector<string>::iterator&end, string& val) {
        return *std::max_element(begin, end, [](string& str1, string& str2) {return str1.length()<str2.length(); });
    };
    
    //boost::timer t;
    auto r = ParallelReduce(v, init, f, f);
    //cout << t.elapsed() << " " << r << endl;
}


int main() {
    test_variant01();
    TestTask();
    TestWhenAll();
    TestWhenAny();
    TestTaskGroup();
    TestParallelFor();
    TestParaInvoke();
    TestParallelSum();
    TestFindString();
    return 0;
}