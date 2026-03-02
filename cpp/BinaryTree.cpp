#include <iostream>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/**********************
 * 一、二叉树的链式存储
 *    用指针连接左右孩子
 **********************/

struct TreeNode
{
    int val;         // 结点存储的数据，这里用 int 做示例
    TreeNode *left;  // 左孩子指针
    TreeNode *right; // 右孩子指针

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**********************
 * LeetCode 144 / 94 两种解法
 *  - 递归版：利用系统栈
 *  - 迭代版：显式使用 stack
 **********************/
class Solution
{
public:
    vector<int> preOrder(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == NULL)
            return result;
        st.push(root);
        while (!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();
            result.push_back(cur->val);
            if (cur->right)
            {
                st.push(cur->right);
            }
            if (cur->left)
            {
                st.push(cur->left);
            }
        }
        return result;
    }

    vector<int> postOrder(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == NULL)
            return result;
        st.push(root);
        while (!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();
            result.push_back(cur->val);
            // 为了得到后序遍历，可以先按「根-右-左」顺序遍历，再整体 reverse
            // 这里先压左再压右，这样出栈顺序就是根-右-左
            if (cur->left)
            {
                st.push(cur->left);
            }
            if (cur->right)
            {
                st.push(cur->right);
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }

    vector<int> inOrder(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        TreeNode *cur = root;
        while (cur != NULL || !st.empty())
        {
            if (cur != NULL)
            {
                st.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = st.top();
                result.push_back(cur->val);
                st.pop();
                cur = cur->right;
            }
        }

        return result;
    }
};

class Solution
{
public:
    // ---------- 144. 二叉树的前序遍历 ----------

    // 递归版：根 -> 左 -> 右
    void preorderRec(TreeNode *root, vector<int> &res)
    {
        if (!root)
            return;
        res.push_back(root->val);
        preorderRec(root->left, res);
        preorderRec(root->right, res);
    }

    vector<int> preorderTraversal_recursive(TreeNode *root)
    {
        vector<int> res;
        preorderRec(root, res);
        return res;
    }

    // 迭代版：显式栈模拟递归
    vector<int> preorderTraversal_iterative(TreeNode *root)
    {
        vector<int> res;
        if (!root)
            return res;

        stack<TreeNode *> st;
        st.push(root);
        while (!st.empty())
        {
            TreeNode *node = st.top();
            st.pop();
            res.push_back(node->val); // 根

            // 注意：先压右再压左，这样弹出时先访问左
            if (node->right)
                st.push(node->right);
            if (node->left)
                st.push(node->left);
        }
        return res;
    }

    // ---------- 94. 二叉树的中序遍历 ----------

    // 递归版：左 -> 根 -> 右
    void inorderRec(TreeNode *root, vector<int> &res)
    {
        if (!root)
            return;
        inorderRec(root->left, res);
        res.push_back(root->val);
        inorderRec(root->right, res);
    }

    vector<int> inorderTraversal_recursive(TreeNode *root)
    {
        vector<int> res;
        inorderRec(root, res);
        return res;
    }

    // 迭代版：指针配合栈
    vector<int> inorderTraversal_iterative(TreeNode *root)
    {
        vector<int> res;
        stack<TreeNode *> st;
        TreeNode *cur = root;

        while (cur || !st.empty())
        {
            // 一路向左下走，把路径上的结点压栈
            while (cur)
            {
                st.push(cur);
                cur = cur->left;
            }
            // 此时栈顶是当前最左侧的结点
            cur = st.top();
            st.pop();
            res.push_back(cur->val); // 访问根
            // 然后转向右子树
            cur = cur->right;
        }
        return res;
    }
};

// 中序遍历：左 -> 根 -> 右
void inOrder(TreeNode *root)
{
    if (!root)
        return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

// 后序遍历：左 -> 右 -> 根
void postOrder(TreeNode *root)
{
    if (!root)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}

/**********************
 * 二、二叉树的顺序存储
 *    用数组/向量存储：
 *    下标从 1 开始：
 *      i  位置的结点：
 *        左孩子下标 = 2 * i
 *        右孩子下标 = 2 * i + 1
 *    这里用 -1 表示空结点
 **********************/

// 顺序存储的先序遍历，idx 为当前结点下标
void preOrderArray(const vector<int> &tree, int idx)
{
    if (idx >= (int)tree.size())
        return; // 越界
    if (tree[idx] == -1)
        return; // -1 表示空

    cout << tree[idx] << " ";         // 访问当前结点
    preOrderArray(tree, idx * 2);     // 左孩子
    preOrderArray(tree, idx * 2 + 1); // 右孩子
}

void inOrderArray(const vector<int> &tree, int idx)
{
    if (idx >= (int)tree.size())
        return;
    if (tree[idx] == -1)
        return;

    inOrderArray(tree, idx * 2);
    cout << tree[idx] << " ";
    inOrderArray(tree, idx * 2 + 1);
}

void postOrderArray(const vector<int> &tree, int idx)
{
    if (idx >= (int)tree.size())
        return;
    if (tree[idx] == -1)
        return;

    postOrderArray(tree, idx * 2);
    postOrderArray(tree, idx * 2 + 1);
    cout << tree[idx] << " ";
}

int main()
{
    /************** 链式存储示例 **************/
    // 构造一棵简单的二叉树：
    //        1
    //      /   \
    //     2     3
    //    / \   /
    //   4   5 6
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n2 = new TreeNode(2);
    TreeNode *n3 = new TreeNode(3);
    TreeNode *n4 = new TreeNode(4);
    TreeNode *n5 = new TreeNode(5);
    TreeNode *n6 = new TreeNode(6);

    // 连接指针形成二叉树
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;
    n3->left = n6;

    cout << "链式存储二叉树遍历:" << endl;
    cout << "先序遍历:   ";
    preOrder(n1);
    cout << endl;

    cout << "中序遍历:   ";
    inOrder(n1);
    cout << endl;

    cout << "后序遍历:   ";
    postOrder(n1);
    cout << endl
         << endl;

    // 使用 Solution 演示 144 / 94 的递归与迭代两种写法
    Solution sol;

    vector<int> pre_rec = sol.preorderTraversal_recursive(n1);
    vector<int> pre_it = sol.preorderTraversal_iterative(n1);
    vector<int> in_rec = sol.inorderTraversal_recursive(n1);
    vector<int> in_it = sol.inorderTraversal_iterative(n1);

    cout << "前序遍历 (递归): ";
    for (int x : pre_rec)
        cout << x << ' ';
    cout << endl;

    cout << "前序遍历 (迭代): ";
    for (int x : pre_it)
        cout << x << ' ';
    cout << endl;

    cout << "中序遍历 (递归): ";
    for (int x : in_rec)
        cout << x << ' ';
    cout << endl;

    cout << "中序遍历 (迭代): ";
    for (int x : in_it)
        cout << x << ' ';
    cout << endl
         << endl;

    /************** 顺序存储示例 **************/
    // 用数组(向量)表示同一棵树，索引从 1 开始
    // 0 位置不用，所以 size 取 7+1 = 8
    vector<int> tree(8, -1); // 初始全为 -1，表示空

    tree[1] = 1; // 根
    tree[2] = 2; // 左孩子
    tree[3] = 3; // 右孩子
    tree[4] = 4; // 2 的左孩子
    tree[5] = 5; // 2 的右孩子
    tree[6] = 6; // 3 的左孩子
    // tree[7] 仍为 -1，表示 3 的右孩子为空

    cout << "顺序存储二叉树遍历:" << endl;
    cout << "先序遍历:   ";
    preOrderArray(tree, 1);
    cout << endl;

    cout << "中序遍历:   ";
    inOrderArray(tree, 1);
    cout << endl;

    cout << "后序遍历:   ";
    postOrderArray(tree, 1);
    cout << endl;

    // 简单释放链式存储的结点内存
    delete n6;
    delete n5;
    delete n4;
    delete n3;
    delete n2;
    delete n1;

    return 0;
}
