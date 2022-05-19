#include <iostream>
#include <vector>
using namespace std;
void insert(int a, vector<int> g)
{
    int n = g.size();
    g.push_back(g[n - 1]);
    for (int i = n - 1; i >= 0; i--)
    {
        g[i] = g[i - 1];
    }
    g[0] = a;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int p[4];
        for (int i = 0; i < n; i++)
        {
            cin >> p[i];
        }
        vector<int> dequeue;
        dequeue[0] = p[0];
        for (int i = 1; i < n; i++)
        {
            if (p[i] > p[i - 1])
            {
                dequeue.push_back(p[i]);
            }
            else
            {
                insert(p[i], dequeue);
            }
        }
        for (int j = 0; j < n; j++)
        {
            // cout << dequeue[j] << " ";
            cout << p[j] << " ";
        }
        cout << endl;
    }
    return 0;
}