#include<iostream>
#include<ctime>

using namespace std;

const int SIZE = 99999999;

int elements[SIZE];

int n,q;

void Init()
{
    cin>>n>>q;
    for(int i = 0; i < n; i++)
        cin>>elements[i];
}
int Query(int left, int right)
{
    int mini = SIZE;
    for(int i = left; i <= right; i++)
    {
        if(elements[i] < mini)
            mini = elements[i];
    }
    return mini;
}

void Solve()
{
    for(int i = 0; i < q; i++)
    {
        int l,r;
        cin>>l>>r;
        Query(l,r);
    }
}

int main()
{
    time_t a;
    a = time(NULL);
    Init();
    Solve();
    time_t b;
    b = time(NULL);
    cout<<b-a<<endl;
    return 0;
}
