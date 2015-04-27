#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <climits>

using namespace std;


int main()
{
    string a, b;
    cin >> a >> b;
    vector <vector <int> > horisontalEdges(a.length() + 1, vector <int> (b.length() + 1, 0));
    for (int j = 0; j <= b.length(); ++j)
    {
        horisontalEdges[0][j] = j;
    }
    vector <vector <int> > verticalEdges(a.length() + 1, vector <int> (b.length() + 1, 0));
    for (size_t i = 1; i <= a.length(); ++i)
    {
        for (int j = 1; j <= b.length(); ++j)
        {
            if (a[i] != b[j])
            {
                horisontalEdges[i][j] = max(verticalEdges[i][j - 1], horisontalEdges[i - 1][j]);
                verticalEdges[i][j] = min(verticalEdges[i][j - 1], horisontalEdges[i - 1][j]);
            }
            else
            {
                horisontalEdges[i][j] = verticalEdges[i][j - 1];
                verticalEdges[i][j] = horisontalEdges[i - 1][j];
            }
           // printf("%d\t", horisontalEdges[i][j]);
           // printf("%d %d %d %d\n", i, j, horisontalEdges[i][j], verticalEdges[i][j]);
        }
        //printf("\n");
    }
    
    printf("\n");
    vector <int> criticalPoint(b.length() + 1, INT_MAX);
    
    for (int j = 1; j <= b.length(); ++j)
    {
        if (horisontalEdges[a.length()][j] != 0)
        {
            criticalPoint[horisontalEdges[a.length()][j]] = j;
        }
    }
    vector <vector <int> > restore(b.length() + 1, vector <int> (b.length() + 1, 0));
    
    for (int i = b.length() - 1; i >= 0; --i)
    {
        for (int j = b.length(); j >= 0; --j)
        {
            if (j <= criticalPoint[i] && j > i)
            {
                restore[i][j] = restore[i + 1][j] + 1;
            }
            else
            {
                restore[i][j] = restore[i + 1][j];
            }
        }
    }
    for (int i = 0; i <= b.length(); ++i)
    {
        printf("%d:\t", i);
        for (int j = 0; j <= b.length(); ++j)
            printf("%d\t", restore[i][j]);
        printf("\n");
    }
    for (int i = 0; i <= b.length(); ++i)
    {
        printf("%d %d\n", i, criticalPoint[i]);
    }
    return 0;
}