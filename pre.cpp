#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

// 自定义结构体：学生
struct Student {
    string name;
    int score;

    // 重载 < 运算符，定义排序规则
    // 在 priority_queue 中，默认是“小于号”返回 true 时，优先级低（排在后面）
    bool operator<(const Student& other) const {
        return score < other.score; // 分数低的排在后面，即高分优先
    }
};

int main() {
    SetConsoleOutputCP(65001);
    // 1. 默认大顶堆 (Max-Heap)
    // 默认使用 vector 作为底层容器，less<int> 作为比较器
    priority_queue<int> maxHeap;
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);

    cout << "大顶堆顶部 (最大值): " << maxHeap.top() << endl; // 输出 30
    maxHeap.pop();

    // 2. 小顶堆 (Min-Heap)
    // 需要显式指定底层容器和比较器 greater<int>
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(10);
    minHeap.push(30);
    minHeap.push(20);

    cout << "小顶堆顶部 (最小值): " << minHeap.top() << endl; // 输出 10
    minHeap.pop();

    // 3. 自定义结构体优先队列
    priority_queue<Student> school;
    school.push({"小明", 85});
    school.push({"小红", 98});
    school.push({"小刚", 72});

    cout << "成绩最好的学生: " << school.top().name << " (" << school.top().score << ")" << endl;

    return 0;
}