#include<iostream>
#include<vector>
using namespace std;



class Tree
{
    private:
        int used[20000];
        int dfs_lvl[20000];
        int euler_order[20000];
        int first_appearance[20000];
        vector<int>tree[20000];
        int nodes; int edges;
        int seg_tree[20000];

    public:
        int lvl=0,order_idx=0;
        void InitSeg(int node, int left_bound, int right_bound)
        {
            if(left_bound == right_bound)
                this -> seg_tree[node] = left_bound;
            else
            {
                InitSeg(node*2,left_bound,
                        (left_bound+right_bound)/2);
                InitSeg(node*2+1,(left_bound+right_bound)/2+1,
                        right_bound);
                int left = seg_tree[node*2];
                int right = seg_tree[node*2+1];
                if(this -> dfs_lvl[left] <= this -> dfs_lvl[right])
                    this -> seg_tree[node] = left;
                else
                    this -> seg_tree[node] = right;
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

        void Set(int nodes, int edges)
        {
            this -> nodes = nodes;
            this -> edges = edges;
            for(int i = 0; i < edges; i++)
            {
                int u,v;
                cin>>u>>v;
                this -> tree[u].push_back(v);
                this -> tree[v].push_back(u);
            }
            DFS(1);
            InitSeg(1,1,order_idx);
        }
        int RMQ(int node, int left_bound, int right_bound,
                int left, int right)
        {
            int l,r;
            if(left_bound > right || left > right_bound)
                return -1;
            if(left <= left_bound && right >= right_bound)
                return this -> seg_tree[node];
            l = RMQ(node*2,left_bound,
                (left_bound+right_bound)/2,left,right);
            r = RMQ(node*2+1,(left_bound+right_bound)/2+1,
                right_bound,left,right);
            if(l == -1)
                return r;
            if(r == -1)
                return l;
            if(this -> dfs_lvl[l] < this -> dfs_lvl[r])
                return l;
            return r;
        }
        int LCA_Query(int u, int v)
        {
            int left  = this -> first_appearance[u];
            int right = this -> first_appearance[v];
            int idx = RMQ(1,1,order_idx, left, right);
            return this -> euler_order[idx];
        }

};

int main()
{
    Tree A;
    A.Set();

    return 0;
}
