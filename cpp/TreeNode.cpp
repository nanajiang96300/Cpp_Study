#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}

    vector<int> preOrder(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == nullptr)
            return result;
        st.push(root);
        while (!st.empty())
        {
            TreeNode *cur = st.top();
            result.push_back(cur->val);
            st.pop();
            if (cur->right)
                st.push(cur->right);
            if (cur->left)
                st.push(cur->left);
        }
        return result;
    }

    vector<int> postOrder(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == nullptr)
            return result;
        st.push(root);
        while (!st.empty())
        {
            TreeNode *cur = st.top();
            result.push_back(cur->val);
            st.pop();
            if (cur->left)
                st.push(cur->left);
            if (cur->right)
                st.push(cur->right);
        }
        reverse(result.begin(), result.end());
        return result;
    }

    vector<int> inOrder(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root == nullptr)
            return result;
        TreeNode *cur = root;
        while (!st.empty() || cur != nullptr)
        {
            if (cur != nullptr)
            {
                st.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = st.top();
                st.pop();
                result.push_back(cur->val);
                cur = cur->right;
            }
        }
        return result;
    }

    vector<int> inOrderTrans(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root != nullptr)
        {
            st.push(root);
        }

        while (!st.empty())
        {
            TreeNode *cur = st.top();
            if (cur != nullptr)
            {
                st.pop();
                if (cur->right)
                    st.push(cur->right);
                st.push(cur);
                st.push(nullptr);
                if (cur->left)
                    st.push(cur->left);
            }
            else
            {
                st.pop();
                cur = st.top();
                result.push_back(cur->val);
                st.pop();
            }
        }

        return result;
    }

    vector<int> preOrderTrans(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root != nullptr)
        {
            st.push(root);
        }

        while (!st.empty())
        {
            TreeNode *cur = st.top();
            if (cur != nullptr)
            {
                st.pop();
                if (cur->right)
                    st.push(cur->right);
                if (cur->left)
                    st.push(cur->left);
                st.push(cur);
                st.push(nullptr);
            }
            else
            {
                st.pop();
                cur = st.top();
                result.push_back(cur->val);
                st.pop();
            }
        }

        return result;
    }

    vector<int> postOrderTrans(TreeNode *root)
    {
        stack<TreeNode *> st;
        vector<int> result;
        if (root != nullptr)
        {
            st.push(root);
        }

        while (!st.empty())
        {
            TreeNode *cur = st.top();
            if (cur != nullptr)
            {
                st.pop();
                st.push(cur);
                st.push(nullptr);
                if (cur->right)
                    st.push(cur->right);
                if (cur->left)
                    st.push(cur->left);
            }
            else
            {
                st.pop();
                cur = st.top();
                result.push_back(cur->val);
                st.pop();
            }
        }

        return result;
    }

    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> que;
        vector<vector<int>> result;
        if (root != nullptr)
            que.push(root);
        while (!que.empty())
        {
            int size = que.size();
            vector<int> vec;
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = que.front();
                que.pop();
                if (cur->left)
                    que.push(cur->left);
                if (cur->right)
                    que.push(cur->right);
                vec.push_back(cur->val);
            }
            result.push_back(vec);
        }
        return result;
    }

    TreeNode *invertTree1(TreeNode *root)
    {
        if (!root)
            return nullptr;
        swap(root->left, root->right); // 交换左右子树指针
        invertTree1(root->left);
        invertTree1(root->right);
        return root;
    }

    TreeNode *invertTree2(TreeNode *root)
    {
        stack<TreeNode *> st;
        if (root != nullptr)
            st.push(root);
        while (!st.empty())
        {
            TreeNode *cur = st.top();
            st.pop();
            swap(cur->left, cur->right);
            if (cur->left)
                st.push(cur->left);
            if (cur->right)
                st.push(cur->right);
        }
        return root;
    }

    TreeNode *invertTree3(TreeNode *root)
    {
        queue<TreeNode *> que;
        if (root != nullptr)
            que.push(root);
        while (!que.empty())
        {
            int size = que.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = que.front();
                que.pop();
                swap(cur->left, cur->right);
                if (cur->left)
                    que.push(cur->left);
                if (cur->right)
                    que.push(cur->right);
            }
        }
        return root;
    }

    bool compare(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
            return true;
        else if (left != nullptr && right == nullptr)
            return false;
        else if (left == nullptr && right != nullptr)
            return false;
        else if (left->val != right->val)
            return false;

        bool outside = compare(left->left, right->right);
        bool inside = compare(left->right, right->left);
        return outside && inside;
    }

    bool isSymatric(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return compare(root->left, root->right);
    }

    int getDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int leftDepth = getDepth(root->left);
        int rightDepth = getDepth(root->right);
        return 1 + max(leftDepth, rightDepth);
    }

    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        queue<TreeNode *> que;
        que.push(root);
        int depth = 0;
        while (!que.empty())
        {
            depth++;
            int size = que.size();
            for (int i = 0; i < size; ++i)
            {
                TreeNode *cur = que.front();
                que.pop();
                if (cur->left)
                    que.push(cur->left);
                if (cur->right)
                    que.push(cur->right);
            }
        }

        return depth;
    }

    int getMinDepth(TreeNode *node) // 递归
    {
        if (node == nullptr)
            return 0;
        if (node->left == nullptr)
            return 1 + getMinDepth(node->right);
        if (node->right == nullptr)
            return 1 + getMinDepth(node->left);
        return 1 + min(getMinDepth(node->left), getMinDepth(node->right));
    }

    int minDepth(TreeNode *root) // 迭代更快
    {
        if (root == nullptr)
            return 0;
        queue<TreeNode *> que;
        que.push(root);
        int depth = 0;
        while (!que.empty())
        {
            depth++;
            int size = que.size();
            for (int i = 0; i < size; ++i)
            {
                TreeNode *cur = que.front();
                que.pop();
                if (cur->left)
                    que.push(cur->left);
                if (cur->right)
                    que.push(cur->right);
                if (!cur->left && cur->right)
                    return depth;
            }
        }

        return depth;
    }
};

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    TreeNode helper(0);

    vector<int> pre = helper.preOrderTrans(root);
    vector<int> in = helper.inOrderTrans(root);
    vector<int> post = helper.postOrderTrans(root);

    cout << "preOrder: ";
    for (int x : pre)
        cout << x << ' ';
    cout << endl;

    cout << "inOrder: ";
    for (int x : in)
        cout << x << ' ';
    cout << endl;

    cout << "postOrder: ";
    for (int x : post)
        cout << x << ' ';
    cout << endl;

    cout << boolalpha;

    // 对称二叉树测试：
    //       1
    //     /   \
    //    2     2
    //   / \   / \
    //  3   4 4   3
    TreeNode *sym = new TreeNode(1);
    sym->left = new TreeNode(2);
    sym->right = new TreeNode(2);
    sym->left->left = new TreeNode(3);
    sym->left->right = new TreeNode(4);
    sym->right->left = new TreeNode(4);
    sym->right->right = new TreeNode(3);
    cout << "isSymatric(sym): " << helper.isSymatric(sym) << endl;

    // 非对称二叉树测试：
    //       1
    //     /   \
    //    2     2
    //     \     \
    //      3     3
    TreeNode *non = new TreeNode(1);
    non->left = new TreeNode(2);
    non->right = new TreeNode(2);
    non->left->right = new TreeNode(3);
    non->right->right = new TreeNode(3);
    cout << "isSymatric(non): " << helper.isSymatric(non) << endl;

    // 空树测试
    cout << "isSymatric(nullptr): " << helper.isSymatric(nullptr) << endl;

    // 最大深度测试
    cout << "\n-- Depth Tests --" << endl;
    cout << "getDepth(root): " << helper.getDepth(root) << " (expected 3)" << endl;

    cout << "getDepth(sym): " << helper.getDepth(sym) << " (expected 3)" << endl;

    cout << "getDepth(non): " << helper.getDepth(non) << " (expected 3)" << endl;

    TreeNode *single = new TreeNode(10);
    cout << "getDepth(single): " << helper.getDepth(single) << " (expected 1)" << endl;

    cout << "getDepth(nullptr): " << helper.getDepth(nullptr) << " (expected 0)" << endl;

    // 迭代法最大深度测试
    cout << "\n-- Iterative Depth Tests (maxDepth) --" << endl;
    cout << "maxDepth(root): " << helper.maxDepth(root) << " (expected 3)" << endl;
    cout << "maxDepth(sym): " << helper.maxDepth(sym) << " (expected 3)" << endl;
    cout << "maxDepth(non): " << helper.maxDepth(non) << " (expected 3)" << endl;
    cout << "maxDepth(single): " << helper.maxDepth(single) << " (expected 1)" << endl;
    cout << "maxDepth(nullptr): " << helper.maxDepth(nullptr) << " (expected 0)" << endl;

    return 0;
}