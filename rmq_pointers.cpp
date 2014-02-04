#include<iostream>
#include<ctime>

using namespace std;

const int SIZE = 500000;

class Tree
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
                    this -> left_bound = 0;
                    this -> right_bound = 0;
                    this -> left = NULL;
                    this -> right = NULL;
                }
                void Set(int left_bound, int right_bound, int index)
                {
                    this -> left_bound = left_bound;
                    this -> right_bound = right_bound;
                    this -> index = index;
                }
                void SetBounds(int left_bound, int right_bound)
                {
                    this -> left_bound = left_bound;
                    this -> right_bound = right_bound;
                }
                void SetPtr(Node *left, Node *right)
                {
                    this -> left = left;
                    this -> right = right;
                }
                void SetLeft(Node *left)
                {
                    this -> left = left;
                }
                void SetRight(Node *right)
                {
                    this -> right = right;
                }
                void SetIndex(int index)
                {
                    this -> index = index;
                }
                int GetIndex()
                {
                    return this -> index;
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
        };
        int elements[SIZE];
        int elements_number;
        Node *root;
    public:
        Tree()
        {
            this -> root = new Node();
        }
        void SetElemnts(int elements_number)
        {
            this -> elements_number = elements_number;
            for(int i = 1; i <= elements_number; i++)
                cin>>this -> elements[i];
        }
        void BuildTree(Node *node, int left_bound, int right_bound)
        {
            //cout<<left_bound<<" "<<right_bound<<endl;;
            if(left_bound == right_bound)
            {
                node -> Set(left_bound, left_bound, left_bound);
                node -> SetPtr(NULL, NULL);
                return;
            }
            else

            {
                Node *left = new Node();
                left -> SetBounds(left_bound, (left_bound+right_bound)/2);
                Node *right = new Node();
                right -> SetBounds((left_bound+right_bound)/2+1,right_bound);
                node -> SetPtr(left, right);
                BuildTree(left,left_bound, (left_bound+right_bound)/2);
                BuildTree(right,(left_bound+right_bound)/2+1,right_bound);
                int l = node -> GetLeft() -> GetIndex();
                int r = node -> GetRight() -> GetIndex();
                if(this -> elements[l] < this -> elements[r])
                {
                    node -> SetIndex(l);
                }
                else
                {
                    node -> SetIndex(r);
                }
            }
        }
        void Build()
        {
            this -> root -> SetBounds(1,elements_number);
            BuildTree(root,1,elements_number);
        }
        int Query(Node *node, int left, int right)
        {
            //cout<<node->GetLeftBound()<<" "<<node->GetRightBound()<<endl;
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
            if(this -> elements[l] < this -> elements[r])
                return l;
            return r;
        }
        int Query(int left, int right)
        {
            //cout<<this->root->GetRightBound()<<endl;
            return this -> elements[Query(this -> root, left, right)];
        }
        void ModifyElement(int index, int value)
        {
            this -> elements[index] = value;
        }
        void ModiyTree(Node *node, int index)
        {
            if(node -> GetLeftBound() == node -> GetRightBound())
                return;
            int mid = (node -> GetLeftBound() + node -> GetRightBound())/2;
            if(index >= node -> GetLeftBound() && index <= mid)
                ModiyTree(node -> GetLeft(), index);
            else
                ModiyTree(node -> GetRight(), index);
            int lindex = node -> GetLeft() -> GetIndex();
            int rindex = node -> GetRight() -> GetIndex();
            if(this -> elements[lindex] < this -> elements[rindex])
                node -> SetIndex(lindex);
            else
                node -> SetIndex(rindex);

        }
};

int main()
{
    time_t e;
    e = time(NULL);
    Tree A;
    int a,b;
    cin>>a>>b;
    A.SetElemnts(a);
    A.Build();
    for(int i = 0; i < b; i++)
    {
        int c,d;
        cin>>c>>d;
        A.Query(c,d);
    }
    time_t f;
    f = time(NULL);
    cout<<f-e<<endl;
    return 0;
}
