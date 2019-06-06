#include "Concurrency04.h" 
#include <future>
#include <thread>
#include <vector>
#include <string>
// 4.2.2 将任务与future相关联
namespace {
    //template<>
    class packaged_task/*<std::string(std::vector<char>*, int)>*/
    {
    public:
        template<typename Callable>
        explicit packaged_task(Callable&& f);
        std::future<std::string> get_future();
        void operator()(std::vector<char>*, int);
    };
}
void Concurrency04_08() {
}