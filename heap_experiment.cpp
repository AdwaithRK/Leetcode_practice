#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    priority_queue<int> pq;
    int a[] = {10,
               30,
               20,
               78,
               99,
               100,
               89, 120};

    // 10 20 30 78 89 99 100 120

    for (int i = 0; i < sizeof(a) / sizeof(int); i++)
    {

        if (pq.size() >= 5)
        {
            cout << "\nPoping:" << pq.top() << "\n";
            pq.pop();
        }
        pq.push(a[i]);
    }

    pq.pop();

    cout << pq.top();
}