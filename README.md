# C++学习

## 前缀和的概念

首先，我们使用一个叫做“前缀和”的概念。对于数组中的任何位置 j，前缀和 pre[j] 是数组中从第一个元素到第 j 个元素的总和。这意味着如果你想知道从元素 i+1 到 j 的子数组的和，你可以用 pre[j] - pre[i] 来计算。

使用 Map 来存储前缀和
在代码中，我们用一个 Map（哈希表）来存储每个前缀和出现的次数。这是为了快速检查某个特定的前缀和是否已经存在，以及它出现了多少次。

核心逻辑解析
当我们在数组中向前移动时，我们逐步增加 pre（当前的累积和）。对于每个新的 pre 值，我们检查 pre - k 是否在 Map 中：

pre - k 的意义：这个检查的意义在于，如果 pre - k 存在于 Map 中，说明之前在某个点的累积和是 pre - k。由于当前的累积和是 pre，这意味着从那个点到当前点的子数组之和恰好是 k（因为 pre - (pre - k) = k）。

如何使用这个信息：如果 pre - k 在 Map 中，那么 pre - k 出现的次数表示从不同的起始点到当前点的子数组和为 k 的不同情况。这是因为每一个 pre - k 都对应一个起点，使得从那个起点到当前点的子数组和为 k。

因此，每当我们找到一个 pre - k 存在于 Map 中时，我们就把它的计数（即之前这种情况发生的次数）加到 count 上，因为这表示我们又找到了相应数量的以当前元素结束的子数组，其和为 k。

例子
假设 k = 7，并且我们当前的累积和 pre 是 10，如果在 Map 中 3（即 10 - 7）出现了两次，这表示存在两个不同的起始点，使得从那些起始点到当前点的子数组之和是 7。

## ASCII

```c++
string t = "ABC";
// 创建一个长度为 128 的 vector，并将所有元素初始化为 0
vector<int> need(128, 0); 

for (char c : t) {
	need[c]++;
}
```

```c++
#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

class Solution {
public:
	string minWindow(string s, string t) {
		int n = s.size(), m = t.size();
		if (n < m) return "";

		// 1. 初始化需求数组
		vector<int> need(128, 0);
		for (char c : t) {
			need[c]++;
		}

		int left = 0, right = 0;
		int minLen = INT_MAX;
		int needCount = m; // 还需要匹配的字符总数
		int start = 0;     // 记录最小窗口的起始位置

		// 2. 右指针开始滑动
		while (right < n) {
			char c = s[right];
            
			// 如果是需要的字符（即配额 > 0），总需求减 1
			if (need[c] > 0) {
				needCount--;
			}
			// 无论是不是需要的，配额都要减 1
			need[c]--;
			right++; // 窗口右移

			// 3. 当满足全部覆盖条件时，尝试收缩左边界
			while (needCount == 0) {
				// 更新结果
				if (right - left < minLen) {
					minLen = right - left;
					start = left;
				}

				char d = s[left];
				// 释放左边界字符，配额加 1
				need[d]++;
				// 如果释放后配额大于 0，说明刚才释放的是一个“必需”字符
				if (need[d] > 0) {
					needCount++;
				}
				left++; // 窗口左收
			}
		}

		// 4. 返回结果
		return minLen == INT_MAX ? "" : s.substr(start, minLen);
	}
};
```

## 封装

Q1: struct 和 class 在封装上有什么区别？
默认权限：struct 默认成员和继承权限都是 public；class 默认是 private。

使用习惯：通常 struct 用于纯数据结构（POD），而 class 用于包含复杂逻辑和封装要求的对象。

Q2: 什么是“虚析构函数”，它和封装有关系吗？
虽然它更多涉及多态，但在封装体系中，为了保证基类指针指向派生类时能正确释放资源，基类析构函数必须设为 virtual。否则会导致子类中封装的特有资源（如动态内存）发生泄漏。

Q3: 为什么要将成员变量设为 private 而不是 public？
解耦：如果变量是 public，一旦改名，所有调用代码都要改。

控制权：private 配合 set/get 可以实现“只读”或“写时校验”，而 public 没有任何拦截能力。

```c++
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief 算子配置封装类
 * 展示点：私有成员、公有接口、数据合法性校验
 */
class OpConfig {
private:
	// 1. 私有属性：外部无法直接修改，防止误设参数导致硬件挂死
	int core_count;        // 使用的核心数
	std::string op_type;   // 算子类型 (FFT/MMSE/Conv)
	bool is_ready;         // 内部状态位

public:
	// 2. 构造函数：初始化内部私有状态
	OpConfig(std::string type) 
		: op_type(type), core_count(1), is_ready(false) {
		std::cout << "Config created for: " << op_type << std::endl;
	}

	// 3. Setter 接口：包含逻辑校验（封装的关键点）
	void setCoreCount(int n) {
		if (n >= 1 && n <= 24) { // 假设硬件只有24核
			core_count = n;
			is_ready = true;
			std::cout << "Cores assigned: " << core_count << std::endl;
		} else {
			std::cerr << "Error: Hardware only supports 1-24 cores!" << std::endl;
		}
	}

	// 4. Getter 接口：只读访问
	int getCoreCount() const {
		return core_count;
	}

	// 5. 业务逻辑接口
	void deploy() {
		if (is_ready) {
			std::cout << "Deploying " << op_type << " on " << core_count << " cores..." << std::endl;
		} else {
			std::cout << "Deploy failed: Config not initialized." << std::endl;
		}
	}
};

int main() {
	OpConfig mmse("MMSE_Detection");

	// ❌ 错误尝试：外部直接访问私有变量（编译报错）
	// mmse.core_count = 100; 

	// ✅ 正确做法：通过公有接口进行安全设置
	mmse.setCoreCount(8);  // 合法设置
	mmse.setCoreCount(64); // 触发内部校验逻辑，拦截错误输入

	mmse.deploy();

	return 0;
}
```

## STL 概览

### 1. STL 六大组件（总览）

- 容器（Containers）：`vector`、`list`、`deque`、`array`、`string`、`set`、`map`、`unordered_map` 等
- 迭代器（Iterators）：对容器元素的“指针抽象”，统一访问接口
- 算法（Algorithms）：`sort`、`find`、`count`、`accumulate`、`for_each` 等
- 仿函数（Functors）：重载 `operator()` 的类，用作比较器或回调
- 适配器（Adapters）：对容器/迭代器/仿函数进行包装，如 `stack`、`queue`、`priority_queue`
- 分配器（Allocators）：负责内存申请与释放，如默认的 `std::allocator`

面试时可以用一句话概括：**“STL = 容器 + 算法 + 迭代器，再加仿函数、适配器和分配器的支撑体系。”**

### 2. 序列式容器对比（vector / list / deque / array）

#### vector

- 底层：连续内存（动态数组）
- 访问：随机访问 $O(1)$，支持下标和随机访问迭代器
- 插入/删除：
	- 尾部 `push_back` / `pop_back`：$O(1)$ 均摊
	- 中间插入/删除：需要搬移大量元素，$O(n)$
- 扩容：容量不足时按倍数扩容，重新分配内存并搬运旧元素，**所有迭代器/指针/引用失效**

小结：读多写少、需要随机访问，用 `vector`。

#### list

- 底层：双向链表
- 访问：不支持随机访问，访问第 $i$ 个元素为 $O(n)$
- 插入/删除：已知迭代器位置处为 $O(1)$，不需要搬移其他元素
- 迭代器：插入/删除不会影响其他迭代器（被删元素本身除外）

小结：频繁在中间插入/删除、对随机访问要求不高时可以考虑 `list`，但工程里仍以 `vector` 为主。

#### deque

- 底层：分段连续内存 + 中央控制结构
- 支持：
	- 头尾插入/删除 $O(1)$：`push_front` / `push_back`
	- 随机访问 $O(1)$：`d[i]`

常见场景：单调队列、滑动窗口、需要高效头尾操作且偶尔随机访问。

#### array

- 固定长度数组封装：`std::array<int, 10>`
- 大小在编译期确定，不能动态改变
- 优点：支持迭代器和 STL 算法，比 C 风格数组更安全。

面试常问：“vector、list、deque 的区别和使用场景”，上面几条记清楚即可。

### 3. 关联式容器（map / set / unordered_*）

#### 有序容器：map / set / multimap / multiset

- 底层：红黑树
- 特性：按 key 自动有序
- 时间复杂度：查找 / 插入 / 删除约 $O(\log n)$

常见区分：

- `set` vs `multiset`：前者 key 唯一，后者允许重复 key
- `map` vs `multimap`：前者 key 唯一，后者允许重复 key

#### 无序容器：unordered_map / unordered_set

- 底层：哈希表
- 时间复杂度：平均查找 / 插入 / 删除 $O(1)$，最坏 $O(n)$
- 元素无序，迭代顺序与插入顺序无关

选择建议：

- 需要有序遍历或下界查找（`lower_bound`）：用 `map` / `set`
- 只关心查找效率、不关心顺序：用 `unordered_map` / `unordered_set`

### 4. 迭代器与失效

#### 迭代器类别（了解）

- 输入 / 输出迭代器：单向读 / 单向写
- 前向迭代器：可多次读写，单向移动
- 双向迭代器：支持 `++`、`--`（如 list / set / map）
- 随机访问迭代器：支持 `it + n`、`it[n]`（如 vector / deque）

#### 迭代器失效规则（高频）

- vector：
	- 扩容后：所有迭代器 / 指针 / 引用失效
	- 中间插入/删除：从操作点到末尾的迭代器失效
- deque：
	- 头尾插入可能导致部分迭代器失效
	- 中间插入/删除通常导致全部失效
- list：
	- 插入/删除不会影响其他迭代器（被删元素自身除外）

错误示例：

```c++
for (auto it = v.begin(); it != v.end(); ++it) {
		if (*it % 2 == 0) {
				v.erase(it); // ❌ it 及后续迭代器失效
		}
}
```

正确写法：

```c++
for (auto it = v.begin(); it != v.end(); ) {
		if (*it % 2 == 0) {
				it = v.erase(it); // 使用返回的新迭代器
		} else {
				++it;
		}
}
```

### 5. 常用算法与 erase-remove 惯用法

常用算法：

- 排序：`std::sort(begin, end)` / `std::stable_sort`
- 查找：`std::find` / `std::find_if` / `std::binary_search`
- 计数：`std::count` / `std::count_if`
- 累加：`std::accumulate`
- 下界 / 上界：`std::lower_bound` / `std::upper_bound`（要求区间有序）

erase-remove 惯用法（vector 删除所有等于某值的元素）：

```c++
std::vector<int> v = {1, 2, 3, 2, 4};

v.erase(std::remove(v.begin(), v.end(), 2), v.end());
// 删除所有值为 2 的元素
```

记忆：

- `remove` 只把不删除的元素搬到前面，返回“新的逻辑结尾”迭代器，不改变 size；
- `erase` 才真正缩小容器。

### 6. push_back vs emplace_back

- `push_back`：
	- 需要一个已经构造好的对象（或可转换对象）
	- 可能产生一次或多次拷贝 / 移动
- `emplace_back`：
	- 直接在容器内部原地构造对象
	- 传入的是构造函数参数，通常更高效

示例：

```c++
std::vector<std::pair<int, std::string>> v;

v.push_back(std::make_pair(1, "abc")); // 先构造临时 pair 再插入
v.emplace_back(2, "xyz");             // 在容器中原地构造 pair(2, "xyz")
```

### 7. STL 高频简答题

- Q1：`vector` 的 `size` 和 `capacity` 有什么区别？
	- `size`：当前存储的元素个数；
	- `capacity`：当前不重新分配内存最多能容纳的元素个数。

- Q2：如何用 `vector` 实现一个栈？
	- `push_back` 入栈，`pop_back` 出栈，`back` 取栈顶，`empty` 判空。

- Q3：为什么 `list` 没有 `operator[]`？
	- 底层是链表，访问第 $i$ 个元素需要从头遍历，复杂度 $O(n)$，提供 `[]` 容易误导认为是 $O(1)$。

- Q4：`map` 的遍历顺序是什么？
	- 按 key 从小到大（或自定义比较器指定的顺序）。

- Q5：什么时候优先使用 `unordered_map`？
	- 不关心 key 顺序、主要操作是查找/插入/删除、希望平均 $O(1)$ 性能时。

这一节可以作为你 STL 的复习提纲：

- 先按容器类型背熟“底层结构 + 复杂度 + 典型场景”；
- 再理解迭代器失效规则和几种经典算法用法（尤其是 erase-remove 惯用法）；
- 最后把上面的 Q&A 用自己的话复述一遍，基本能覆盖大部分 STL 相关面试题。

## BFS 与 DFS 对比（何时用哪种）

两者时间复杂度通常为 O(V+E)，但适用场景和空间开销不同。下面列出要点、示例与常见变体，方便在面试或写算法时快速选型。

### 要点概览
- **BFS（广度优先）**：按层遍历，适合求无权图最短路径、层序遍历、最小步数问题。空间消耗与层宽度相关。  
- **DFS（深度优先）**：沿一条路径走到底再回溯，适合回溯枚举、拓扑排序、强连通分量、检测环。空间与递归/显式栈深度相关。

### 典型例子
- 最短步数（迷宫/网格最短路径，无权）：用 BFS。伪代码：

```text
queue q; q.push(start); dist[start]=0;
while q not empty:
	u = q.pop();
	for v in neighbors(u):
		if not visited[v]: visited[v]=true; dist[v]=dist[u]+1; q.push(v)
```

- 层序遍历二叉树（按层处理节点）：用 BFS（队列）。
- 组合/排列/数独 等回溯问题：用 DFS（递归或显式栈），因为需要穷举并在失败时回溯。

示例：用 DFS 求字符串所有排列（回溯思想）

```cpp
void dfs(string &s, int l, vector<string>& ans){
	if(l==s.size()){ ans.push_back(s); return; }
	for(int i=l;i<s.size();++i){ swap(s[l],s[i]); dfs(s,l+1,ans); swap(s[l],s[i]); }
}
```

### 为什么在某些场景 BFS 优于 DFS
- 无权最短路问题：BFS 一旦第一次到达目标即为最短（按边数），DFS 需要遍历更多路径才能保证最短。  
- 层相关计算（例如距离为 k 的所有节点、树的每一层聚合）自然用 BFS 实现更简洁。

### 为什么在某些场景 DFS 优于 BFS
- 回溯/枚举类问题需要探索完整解空间且可在深处剪枝时，DFS 更节省内存且实现直观。  
- 某些图算法（如拓扑排序、Tarjan 强连通分量）天然基于 DFS。

### 常见折衷与变体
- **迭代加深深度优先（IDS）**：结合 DFS 的内存优势和 BFS 的逐层特性，适合内存受限又需最短解的情况。  
- **双向 BFS**：当起点和终点都已知，双向同时搜索可将复杂度从 O(b^d) 降到 O(b^(d/2))（b 为分支因子，d 为距离）。
- **启发式搜索（A*）**：带启发函数时比盲搜更高效，适用于有代价或启发信息的最短路径问题。

### 实践建议（简短）
- 需要“最短步数/按层” → 用 BFS；需要“枚举/回溯/拓扑/连通性” → 用 DFS；遇到内存或最短性冲突时考虑 IDS、双向 BFS 或 A*。

---


# 二叉树学习笔记（遍历 + 反转）

> 代码环境：C++（MinGW g++），工作区示例文件：`TreeNode.cpp`

## 1. TreeNode 基本结构

典型二叉树节点：

```cpp
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};
```

常用头文件：
- 栈：`#include <stack>`
- 队列：`#include <queue>`
- 反转/交换：`#include <algorithm>`（或 `#include <utility>` + `std::swap`）

## 2. 三种遍历（前序 / 中序 / 后序）

二叉树三大深度优先遍历顺序（通常说的“三种遍历”就是这三个）：
- 前序：根 → 左 → 右
- 中序：左 → 根 → 右
- 后序：左 → 右 → 根

本次学习中，为了写出这三种遍历，常见有三类“实现思路”（注意：这是实现方式，不是遍历顺序）：
1) **递归思路**（最直观）
2) **迭代栈模拟**（常用面试写法）
3) **统一迭代（标记法 / nullptr 标记）**（一套模板写三种顺序）

> 你当前 `TreeNode.cpp` 主要使用：
> - 前/中/后：迭代栈（普通写法）
> - 前/中/后：统一迭代（用 `nullptr` 作为“访问标记”）
> - （扩展）层序：队列 BFS

---

### 2.1 前序遍历（迭代栈：最常用）

**核心思想：**
- 先访问根。
- 为保证“左先于右”，入栈顺序要反过来：先 push 右，再 push 左。

```cpp
vector<int> preOrder(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        res.push_back(cur->val);
        if (cur->right) st.push(cur->right);
        if (cur->left)  st.push(cur->left);
    }
    return res;
}
```

复杂度：
- 时间：O(N)
- 额外空间：O(h)（h 为树高；最坏 O(N)，平衡树 O(logN)）

---

### 2.2 中序遍历（迭代栈：指针一路压左）

**核心思想：**
- 用指针 `cur` 一路向左压栈。
- 到空后弹栈访问，再转向右子树。

```cpp
vector<int> inOrder(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top(); st.pop();
        res.push_back(cur->val);
        cur = cur->right;
    }
    return res;
}
```

复杂度同前序：时间 O(N)，额外空间 O(h)。

---

### 2.3 后序遍历（常用技巧：先“根右左”再 reverse）

**核心思想：**
- 后序是：左 → 右 → 根。
- 可以先做：根 → 右 → 左（用栈实现很容易）。
- 最后整体 `reverse` 得到：左 → 右 → 根。

```cpp
vector<int> postOrder(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        res.push_back(cur->val);
        if (cur->left)  st.push(cur->left);
        if (cur->right) st.push(cur->right);
    }
    reverse(res.begin(), res.end());
    return res;
}
```

复杂度同样：时间 O(N)，额外空间 O(h)。

---

## 3. 统一迭代（标记法 nullptr）

**目的：**用同一套“模板”实现前/中/后序，避免每种遍历分别记忆不同的栈技巧。

**统一迭代的核心：**
- 栈里放指针。
- 当遇到非空节点 `cur` 时：
  - 把它“展开”成：若干子节点 + 自己 + `nullptr` 标记。
- 当遇到 `nullptr` 时：
  - 表示“下一次弹出的节点要被访问”。

> 你代码中 `nullptr` 标记的写法是正确的思路。

### 3.1 前序统一迭代（根左右）

前序：访问顺序是“根先访问”。
- 入栈展开时，要让“访问根”发生在左右子树之前。
- 模板写法（栈顶先出）：把访问动作（`cur + nullptr`）放在最后入栈，这样会最先弹出并访问。

（你项目里实现：`preOrderTrans`）

### 3.2 中序统一迭代（左根右）

中序：根在中间访问。
- 展开顺序让“访问根”发生在左子树之后、右子树之前。

（你项目里实现：`inOrderTrans`）

> 注意：建议统一用 `nullptr`，不要混用 `NULL`。

### 3.3 后序统一迭代（左右根）

后序：根最后访问。
- 展开时让 `cur + nullptr` 在左右子树之后才触发。

（你项目里实现：`postOrderTrans`）

统一迭代的优缺点：
- 优点：一个模板覆盖三种遍历，写法统一、可迁移。
- 缺点：初学时不直观，栈操作多，常数开销略大。

复杂度：
- 时间：O(N)
- 额外空间：O(h)

---

## 4. 扩展：层序遍历（BFS，队列）

**层序遍历 = 广度优先搜索 BFS**：一层一层访问。

### 4.1 按层分组返回（二维数组）

关键技巧：每一层开始时记录 `size = queue.size()`，本层只处理这 `size` 个节点。

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = (int)q.size();
        vector<int> level;
        for (int i = 0; i < sz; ++i) {
            TreeNode* cur = q.front(); q.pop();
            level.push_back(cur->val);
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        res.push_back(level);
    }
    return res;
}
```

复杂度：
- 时间：O(N)
- 额外空间：O(w)，w 为最大层宽（最坏 O(N)）

优缺点：
- 优点：天然按层输出/按层处理（如求每层最大值、最小深度）。
- 缺点：队列可能在“很宽”的树上占用较大内存。

---

## 5. 三种反转二叉树方法（invert tree）

目标：对每个节点交换左右子树：`swap(node->left, node->right)`。

### 5.1 方法 1：递归（DFS）

```cpp
TreeNode* invertTree1(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invertTree1(root->left);
    invertTree1(root->right);
    return root;
}
```

- 时间：O(N)
- 额外空间：O(h)（递归栈）
- 优点：最简洁、最直观。
- 缺点：树很深时可能栈溢出。

### 5.2 方法 2：迭代 + 栈（DFS）

```cpp
TreeNode* invertTree2(TreeNode* root) {
    if (!root) return root;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        swap(cur->left, cur->right);
        if (cur->left)  st.push(cur->left);
        if (cur->right) st.push(cur->right);
    }
    return root;
}
```

- 时间：O(N)
- 额外空间：O(h)（显式栈）
- 优点：避免递归栈溢出风险。
- 缺点：代码略长。

### 5.3 方法 3：迭代 + 队列（BFS）

```cpp
TreeNode* invertTree3(TreeNode* root) {
    if (!root) return root;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        swap(cur->left, cur->right);
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return root;
}
```

- 时间：O(N)
- 额外空间：O(w)（队列，最大层宽）
- 优点：按层处理直观；对“极度偏斜”的树，队列峰值可能很小。
- 缺点：对“很宽”的树，队列可能接近 O(N) 内存。

---

## 6. 三种反转方法的空间复杂度对比：谁更优？

定义：
- N：节点数
- h：树高
- w：最大层宽

对比：
- 递归 DFS（invertTree1）：额外空间 O(h)
- 栈 DFS（invertTree2）：额外空间 O(h)
- 队列 BFS（invertTree3）：额外空间 O(w)

谁更优取决于树形状：
- **平衡树**：h≈logN，w≈N/2 → DFS 更省内存（O(logN) vs O(N)）
- **链状树**：h≈N，w=1 → BFS 更省内存（O(1) vs O(N)）

实践建议：
- 代码最简：递归 DFS。
- 担心深度栈溢出：用迭代栈 DFS。
- 需要按层处理或天然 BFS 思路：用队列。

---

## 7. 常见易错点（来自本次练习）

1) **前序遍历入栈顺序**
- 为保证“左先访问”，入栈要先右后左。

2) **中序遍历不要把 nullptr 入栈**
- 推荐用“双 while”写法：先一路压左到空，再弹栈访问。

3) **统一迭代标记法：统一用 nullptr**
- 你代码里个别位置还写了 `NULL`（例如 `inOrderTrans` 里），建议替换为 `nullptr`，避免旧式宏带来的隐式转换问题。

4) **层序遍历要处理空树**
- `if (!root) return ...;` 或者 `if(root) q.push(root);` 二选一。

5) **VS Code 构建任务注意“当前文件”**
- 若任务用 `${file}`，按 Ctrl+Shift+B 前请确保当前活动文件是 `.cpp`，否则可能把 `.json` 当源文件编译。

---

## 8. 小测试树与预期结果

测试树：

```
      1
     / \
    2   3
   / \ /
  4  5 6
```

预期：
- 前序：1 2 4 5 3 6
- 中序：4 2 5 1 6 3
- 后序：4 5 2 6 3 1
- 层序（按层）：[ [1], [2,3], [4,5,6] ]

---

## 9. 本次收获总结

- 深度优先遍历：用栈模拟递归是常见工程/面试写法。
- 统一迭代（nullptr 标记）可用一个模板写出三种遍历。
- 层序遍历用队列 BFS，通过 `size` 分层。
- 反转二叉树本质：对每个节点做 `swap(left, right)`；实现上可递归、可 DFS 栈、可 BFS 队列。
- 空间复杂度“谁最优”与树的形状有关：平衡树偏向 DFS，链状树 BFS 更省。
