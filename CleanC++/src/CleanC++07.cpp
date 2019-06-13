// 7 函数式编程
// 7.1 什么是函数式编程
// 采用类似于数学函数形式的编程范式。程序由一系列函数和函数链的求值构成。
// 函数式编程的优势：
// 通过避免(全局)共享可变的状态消除副作用。
// 不可变的数据和对象。
// 函数组合和高阶函数。
// 更好更容易的并行化。
// 易于测试。
// 7.1.1 什么是函数
// 引用透明(referential transparency)
// 7.1.2 pure函数和impure函数
// 7.2 现代C++中的函数式编程
// 7.2.1 C++模板函数编程
// 7.2.2 仿函数
// 生成器：没有参数的仿函数
// 一元仿函数:一个参数的仿函数
// 谓词：返回bool类型值的反函数叫做谓词。
// 带有一个参数并返回bool型结果的仿函数叫做一元谓词。
// 带有两个参数并返回bool型结果的仿函数叫做二元谓词。
// 7.2.3 绑定和函数包装
// std::bind,std::function
// 7.2.4 Lambda表达式
// [capture](params)opt->return type{body}
// 7.2.5 通用Lambda表达式(C++14)
// 7.3 高阶函数
// Map、Filter、Reduce
// std::transform
// std::erase(std::remove_if())
// std::accumulate
// 左fold:std::accumulate(begin, end, init_value, binary_operator)
// 右fold:std::accumulate(rbegin, rend, init_value, binary_operator)
// 7.4 整洁的函数式编程代码
