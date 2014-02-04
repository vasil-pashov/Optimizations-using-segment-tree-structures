#include<iostream>
#include<vector>

using namespace std;

const int SIZE = 10000;

class Tree
{
    private:
        vector<int>tree[SIZE];
        int used[SIZE];
        int euler_order[SIZE];
        int dfs_lvl[SIZE];
        int first_appearance[SIZE];
        int nodes;
        int edges;
    public:
        int lvl=0,order_idx=0;
        Tree()
        {
            this -> nodes = 0;
            this -> edges = 0;
        }
        void Set()
        {
            cin>>this -> nodes>>this -> edges;
            for(int i = 0; i < edges; i++)
            {
                int u,v;
                cin>>u>>v;
                this -> tree[u].push_back(v);
                this -> tree[v].push_back(u);
            }
        }
        void DFS(int node)
        {
            used[node] = 1;
            order_idx++;
            this -> euler_order[order_idx] = node;
            this -> first_appearance[node] = order_idx;
            this -> dfs_lvl[order_idx] = lvl;
            for(int i = 0; i < tree[node].size(); i++)
            {
                int v = tree[node][i];
                if(used[v] != 1)
                {
                    lvl++;
                    DFS(v);
                    lvl--;
                    order_idx++;
                    this -> dfs_lvl[order_idx] = lvl;
                    this -> euler_order[order_idx] = node;
                }

            }
        }
        int GetEulerOrder(int index)
        {
            return this -> euler_order[index];
        }
        int GetDFSLvl(int index)
        {
            return this -> dfs_lvl[index];
        }
        int GetFirstAppearance(int index)
        {
            return this -> first_appearance[index];
        }
};

class SegmentTree : public Tree
{
    private:
        class Node
        {
            private:
                int left_bound;
                int right_bound;
                int index;
                Node *left;
                Node *right;
            public:
                Node()
                {
                    this -> left_bound = -2;
                    this -> right_bound = -2;
                    this -> index = -2;
                    this -> left = NULL;
                    this -> right = NULL;
                }
                void SetBounds(int left_bound, int right_bound)
                {
                    this -> left_bound = left_bound;
                    this -> right_bound = right_bound;
                }
                void SetSons(Node *left, Node *right)
                {
                    this -> left = left;
                    this -> right = right;
                }
                void SetIndex(int index)
                {
                    this -> index = index;
                }
                Node *GetLeft()
                {
                    return this -> left;
                }
                Node *GetRight()
                {
                    return this -> right;
                }
                int GetLeftBound()
                {
                    return this -> left_bound;
                }
                int GetRightBound()
                {
                    return this -> right_bound;
                }
                int GetIndex()
                {
                    return this -> index;
                }
        };
        Node *root;
        public:
            SegmentTree()
            {
                this -> root = new Node();
            }
        void BuildSegTree(Node *node, int left_bound, int right_bound)
        {
            if(left_bound == right_bound)
            {
                node -> SetBounds(left_bound, left_bound);
                node -> SetIndex(left_bound);
                node -> SetSons(NULL, NULL);
                return;
            }
            else

            {
                Node *left = new Node();
                left -> SetBounds(left_bound, (left_bound+right_bound)/2);
                Node *right = new Node();
                right -> SetBounds((left_bound+right_bound)/2+1,right_bound);
                node -> SetSons(left, right);
                BuildSegTree(left,left_bound, (left_bound+right_bound)/2);
                BuildSegTree(right,(left_bound+right_bound)/2+1,right_bound);
                int l = node -> GetLeft() -> GetIndex();
                int r = node -> GetRight() -> GetIndex();
                if(GetDFSLvl(l) < GetDFSLvl(r))
                {
                    node -> SetIndex(l);
                }
                else
                {
                    node -> SetIndex(r);
                }
            }

            }
            void BuildSegTree()
            {
                BuildSegTree(this -> root, 1, order_idx);
                this -> root -> SetBounds(1, order_idx);
            }
            int Query(Node *node, int left, int right)
            {
                int l,r;
                if(right < node -> GetLeftBound() || left > node -> GetRightBound())
                    return -1;
                if(node -> GetLeftBound() >= left && node -> GetRightBound() <= right)
                    return node -> GetIndex();
                l = Query(node -> GetLeft(), left, right);
                r = Query(node -> GetRight(), left, right);
                if(l == -1)
                    return r;
                if(r == -1)
                    return l;
                if(GetDFSLvl(l) < GetDFSLvl(r))
                    return l;
                return r;
            }
            int Query(int u, int v)
            {

                int left = GetFirstAppearance(u);
                int right = GetFirstAppearance(v);
                int index = Query(this -> root, left, right);

                return GetEulerOrder(index);
            }

};

int main()
{
    SegmentTree A;
    A.Set();
    A.DFS(1);
    A.BuildSegTree();
    int q;
    cin>>q;
    for(int i = 0; i < q; i++)
    {
        int u, v;
        cin>>u>>v;
        cout<<A.Query(u, v)<<endl;
    }
    return 0;
}
