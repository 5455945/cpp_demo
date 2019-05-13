#include "05-03.h"

// 5.3 条件变量
// 条件变量是C++11是一种用于等待的同步机制,它能阻塞一个或多个线程，
// 直到收到另外一个线程发出的通知或者超时，才会唤醒当前阻塞的线程。
// 条件变量需要和互斥量配合起来用。C++11提供了两种条件变量:
// condition_variable,配合std::unique_lock<std::mutex>进行wait操作。
// condition_variable_any,和任意带有lock，unlock语义的mutex搭配使用,比较灵活，但效率必condition_variable差一些。
/*
关键点是：
1. wait()函数的内部实现是：先释放互斥量的锁，然后阻塞以等待条件为真；
2. 套路是：
a.A线程拿住锁，然后wait, 此时已经释放锁，只是阻塞了在等待条件为真；
b.B线程拿住锁，做一些业务处理，然后令条件为真，释放锁，再调用notify函数；
c.A线程被唤醒，接着运行。
*/
void test05_03() {
	
	return;
}