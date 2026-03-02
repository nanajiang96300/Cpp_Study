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
