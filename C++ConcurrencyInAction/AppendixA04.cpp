#include "AppendixA.h"
#include <mutex>
#include <condition_variable>
namespace {
    std::condition_variable cond;
    bool data_ready;
    std::mutex m;
    void wait_for_data()
    {
        std::unique_lock<std::mutex> lk(m);
        cond.wait(lk, [] {return data_ready; });
    }
}
void AppendixA_04() {

}