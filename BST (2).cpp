//BST
struct node
{
    int val, subsize;
    node *left, *right;
    node(int v) {val = v, subsize = 1, left = right = NULL;}
};
class BST
{
    node *head;
    void insert(int val, node *now)
    {
        ++now->subsize;
        if (val < now->val)
        {
            if (now->left == NULL)
            {
                now->left = new node(val);
                return;
            }
            else insert(val, now->left);
        }
        else
        {
            if (now->right == NULL)
            {
                now->right = new node(val);
                return;
            }
            else insert(val, now->right);
        }
    }
    long long calc(node *now)
    {
        if (now == NULL) return 1;
        long long left, right, ret;
        left = calc(now->left);
        right = calc(now->right);
        ret = (left * right) % MOD;
        if (now->left != NULL && now->right != NULL) ret = ret * rec(now->left->subsize, now->right->subsize);
        if (now->left != NULL) delete now->left;
        if (now->right != NULL) delete now->right;
        return ret % MOD;
    }
public:
    BST(int n) { head = new node(n); }
    void insert(int n) { insert(n,head); }
    long long calc() { return calc(head); }
};
