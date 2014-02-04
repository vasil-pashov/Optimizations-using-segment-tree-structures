#include<iostream>
#include<ctime>

using namespace std;

const long long SIZE = 100000;

long long n,q,cnt = 0;

class Segment
{
    private:
        long long left;
        long long right;
    public:
        Segment(long long left = 0, long long right = 0)
        {
            this -> left = left;
            this -> right = right;
        }
        void Set(long long left, long long right)
        {
            this -> left = left;
            this -> right = right;
        }
        long long GetLeft()
        {
            return this -> left;
        }
        long long GetRight()
        {
            return this -> right;
        }
        bool Check(long long poi_nt)
        {
            if(this->left<= poi_nt && this -> right >= poi_nt)
                return 1;
            return 0;
        }

}Segments[SIZE];

void Init()
{
    cin>>n>>q;
    for(long long i = 0; i < n; i++)
    {
        long long x,y;
        cin>>x>>y;
        Segments[i].Set(x,y);
    }
}

void Solve()
{
    for(long long i = 0; i < q; i++)
    {
        long long poi_nt;
        cin>>poi_nt;
        for(long long j = 0; j < n; j++)
        {
            if(Segments[j].Check(poi_nt))
            {
                    cnt++;
            }
        }
        //cout<<cnt<<endl;
        cnt = 0;
    }
}

int main()
{
    time_t a = time(NULL);
    Init();
    Solve();
    time_t b = time(NULL);
    cout<<b-a<<endl;
    return 0;
}
