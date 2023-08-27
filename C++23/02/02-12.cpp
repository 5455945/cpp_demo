#include "02-12.h"

#include <utility>  // std::move


// 12、特性十二：forward_like（P2445）
// 同样的作者在"Deducing this"一节中也使用了这个例子来说明。让我们回顾一下这个例子：

//auto callback = [m = get_message(), &scheduler](this auto&& self) -> bool {
//    return scheduler.submit(std::forward_like<decltype(self)>(m));
//    };

void test02_12_01() {
    //callback();            // retry(callback)
    //std::move(callback)(); // try-or-fail(rvalue)
}

// C++中的中加入了std::forward_like函数，它可以根据模板参数的值类别来转发参数。 
// 如果closure type为左值，那么m将转发为左值；如果为右值，将转发为右值。 
// 据说，Clang 16和MSVC v19.34都支持这个特性，但目前还没有发布。


void test02_12() {
    test02_12_01();
}
