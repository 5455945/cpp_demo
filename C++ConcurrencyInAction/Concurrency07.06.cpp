#include "Concurrency07.h" 
#include <atomic>
#include <memory>
namespace {
    //// 用风险指针检测不能被回收的节点
    //std::shared_ptr<T> pop()
    //{
    //    std::atomic<void*>& hp = get_hazard_pointer_for_current_thread();
    //    node* old_head = head.load();
    //    do
    //    {
    //        node* temp;
    //        do
    //        {
    //            temp = old_head;
    //            hp.store(old_head);
    //            old_head = head.load();
    //        } while (old_head != temp);
    //    } while (old_head &&
    //        !head.compare_exchange_strong(old_head, old_head->next));
    //    hp.store(nullptr);
    //    std::shared_ptr<T> res;
    //    if (old_head)
    //    {
    //        res.swap(old_head->data);
    //        if (outstanding_hazard_pointers_for(old_head))
    //        {
    //            reclaim_later(old_head);
    //        }
    //        else
    //        {
    //            delete old_head;
    //        }
    //        delete_nodes_with_no_hazards();
    //    }
    //    return res;
    //}
}
void Concurrency07_06() {
}
