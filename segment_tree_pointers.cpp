#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

const long long SIZE = 100000;
long long cnt = 0;
class Tree
{
    private:
        class Segment
        {
            private:
                long long left_x, right_x;
            public:
                Segment()
                {
                    this -> right_x = 0;
                    this -> left_x = 0;
                }
                Segment(long long left_x, long long right_x)
                {
                    this -> left_x = left_x;
                    this -> right_x = right_x;
                }
                void Set(long long left_x, long long right_x)
                {
                    this -> left_x = left_x;
                    this -> right_x = right_x;
                }
                long long GetLeftX()
                {
                    return this -> left_x;
                }
                long long GetRightX()
                {
                    return this -> right_x;
                }
        };
        class Node
        {
            private:
                long long key, left_bound, right_bound;
                vector<Segment>elements;
                Node *left;
                Node *right;
            public:
                Node()
                {
                    this -> key = 0;
                    this -> left_bound = 0;
                    this -> right_bound = 0;
                    this -> left = NULL;
                    this -> right = NULL;
                }
                Node(long long left_bound, long long right_bound, long long key, Node *left, Node *right)
                {
                    this -> left_bound = left_bound;
                    this -> right_bound = right_bound;
                    this -> key = key;
                    this -> left = left;
                    this -> right = right;
                }
                void SetBounds(long long left_bound, long long right_bound)
                {
                    this -> left_bound = left_bound;
                    this -> right_bound = right_bound;
                }
                void SetKey(long long key)
                {
                    this -> key = key;
                }
                void SetKey()
                {
                    this -> key = (left_bound+right_bound)/2;
                }
                void SetLeft(Node *left)
                {
                    this -> left = left;
                }
                void SetRight(Node *right)
                {
                    this -> right = right;
                }
                void PushSegment(Segment a)
                {
                    this -> elements.push_back(a);
                }
                long long GetLeftBound()
                {
                    return this -> left_bound;
                }
                long long GetRightBound()
                {
                    return this -> right_bound;
                }
                long long GetKey()
                {
                    return this -> key;
                }
                Node *GetLeft()
                {
                    return this -> left;
                }
                Node *GetRight()
                {
                    return this -> right;
                }
                long long GetElements()
                {
                    long long s = elements.size();
                        return s;
                }

        };
    Node *root;
    Segment e[SIZE];
    public:
        long long mini = 999999, maxi = -999999;
        Tree()
        {
            this -> root = new Node();
        }
        void SetSegments(long long n)
        {
            for(long long i = 0; i < n; i++)
            {
                long long p,q;
                cin>>p>>q;
                if(mini > p)
                    mini = p;
                if(q > maxi)
                    maxi = q;
                e[i].Set(p,q);
            }
        }
        void InsertSegment(Node *node, long long left_bound, long long right_bound, Segment a)
        {
            long long l = a.GetLeftX();
            long long r = a.GetRightX();
            if(left_bound >= l && right_bound <= r)
            {
                node -> PushSegment(a);
                return;
            }
            long long mid = (left_bound+right_bound)/2;
            if(node -> GetLeft() == NULL)
            {
                Node *left = new Node();
                left -> SetBounds(left_bound,mid);
                left -> SetKey();
                node -> SetLeft(left);
            }
            if(node -> GetRight() == NULL)
            {
                Node *right = new Node();
                right -> SetBounds(mid+1,right_bound);
                right -> SetKey();
                node -> SetRight(right);
            }
            node -> SetKey();
            if(l <= mid)
                InsertSegment(node -> GetLeft(), left_bound, mid, a);
            if(r > mid)
                InsertSegment(node -> GetRight(), mid+1, right_bound, a);
        }
        void Build(long long n)
        {
            SetSegments(n);
            root -> SetBounds(mini, maxi);
            for(long long i = 0; i < n; i++)
                {
                    InsertSegment(this -> root, mini, maxi, e[i]);
                }
        }
        void Query(Node *node,long long poi_ntt)
        {
            if(node -> GetLeftBound() > poi_ntt || node -> GetRightBound() < poi_ntt)
                return;
            long long m = (node -> GetLeftBound() + node -> GetRightBound())/2;
            if(node -> GetLeftBound() <= poi_ntt && node -> GetRightBound() >= poi_ntt)
            {
                    cnt+=node -> GetElements();
                    node -> GetElements();
            }
            Node *left;
            Node *right;
            left = node -> GetLeft();
            right = node -> GetRight();
            if(left != NULL && left -> GetLeftBound() <= poi_ntt && left -> GetRightBound() >= poi_ntt )
                Query(left, poi_ntt);
            if(right != NULL && right -> GetLeftBound() <= poi_ntt && right -> GetRightBound() >= poi_ntt )
                Query(right, poi_ntt);


        }
        void Query(long long poi_ntt)
        {
            Query(this -> root, poi_ntt);
        }
        void Inorder(Node *p)
        {
            if(p -> GetLeft() != 0)
                Inorder(p -> GetLeft());
            if(p -> GetRight())
                Inorder(p -> GetRight());
        }
        void Show()
        {
            Inorder(this -> root);
        }


};

int main()
{
    Tree A;
    long long n,q;
    cin>>n>>q;
    time_t a = time(NULL);
    A.Build(n);
    for(long long i = 0; i < q; i++)
    {
        long long x;
        cin>>x;
        A.Query(x);
        //cout<<cnt<<endl;
        cnt = 0;
    }
    time_t b = time(NULL);
    cout<<b - a<<endl;
    return 0;
}
