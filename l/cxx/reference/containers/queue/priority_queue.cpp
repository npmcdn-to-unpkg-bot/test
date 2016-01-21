#include <iostream>
#include <queue>
#include <vector>

/*
    http://blog.csdn.net/sup_heaven/article/details/8036982

    priority_queue 对于基本类型的使用方法相对简单。他的模板声明带有三个参数，priority_queue<Type, Container, Functional>
    Type 为数据类型， Container 为保存数据的容器，Functional 为元素比较方式。
    Container 必须是用数组实现的容器，比如 vector, deque 但不能用 list.
    STL里面容器默认用的是 vector. 比较方式默认用 operator< , 所以如果你把后面俩个参数 缺省的话，优先队列就是大顶堆，队头元素最大。

*/

int main(int argc, char** argv) {
    // std::priority_queue<int, std::vector<int>, std::less<int>> q3;
    std::priority_queue<int> q;
    // std::cout << "an empty priority_queue top is " << q.top() << std::endl; // coredump

    for (int i = 5; i>0; i--) {
        q.push(i);
        std::cout << "top of the q is " << q.top() << std::endl;
    }

    // 如果要用到小顶堆，则一般要把模板的三个参数都带进去。
    // STL里面定义了一个仿函数 greater<>, less<>，对于基本类型可以用这个仿函数声明小顶堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> q2;
    for (int i = 5; i>0; i--) {
        q2.push(i);
        std::cout << "top of the q is " << q2.top() << std::endl;
    }

}