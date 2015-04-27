#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <climits>

using namespace std;


namespace ALCSSquare
{
    const size_t SIZE_T_MAX(-1);

    vector <vector <size_t> > parseCriticalPoints(const vector <size_t> &criticalPoints)
    {
        vector <vector <size_t> > restore(criticalPoints.size() + 1, vector <size_t> (criticalPoints.size() + 1, 0));
        
        for (size_t i = criticalPoints.size() - 1; i != SIZE_T_MAX; --i)
        {
            for (size_t j = criticalPoints.size(); j != SIZE_T_MAX; --j)
            {
                if (j < criticalPoints[i + 1] && j > i)
                {
                    restore[i][j] = restore[i + 1][j] + 1;
                }
                else
                {
                    restore[i][j] = restore[i + 1][j];
                }
            }
        }
        return restore;
    }

    vector <size_t> getCriticalPoints(const string &a, const string &b)
    {
        vector <vector <size_t> > horisontalEdges(a.length() + 1, vector <size_t> (b.length() + 1, 0));
        for (size_t j = 0; j <= b.length(); ++j)
        {
            horisontalEdges[0][j] = j;
        }
        vector <vector <size_t> > verticalEdges(a.length() + 1, vector <size_t>    (b.length() + 1, 0));
        for (size_t i = 1; i <= a.length(); ++i)
        {
            for (size_t j = 1; j <= b.length(); ++j)
            {
                if (a[i - 1] != b[j - 1])
                {
                    horisontalEdges[i][j] = max(verticalEdges[i][j - 1], horisontalEdges[i - 1][j]);
                    verticalEdges[i][j] = min(verticalEdges[i][j - 1], horisontalEdges[i - 1][j]);
                }
                else
                {
                    horisontalEdges[i][j] = verticalEdges[i][j - 1];
                    verticalEdges[i][j] = horisontalEdges[i - 1][j];
                }
            }
        }
        
        vector <size_t> criticalPoints(b.length() + 1, INT_MAX);
        
        for (size_t j = 1; j <= b.length(); ++j)
        {
            if (horisontalEdges[a.length()][j] != 0)
            {   
                criticalPoints[horisontalEdges[a.length()][j]] = j;
            }
        }
        return criticalPoints;
    }

    vector <vector <size_t> > solution(const string &a, const string &b)
    {
        return parseCriticalPoints(getCriticalPoints(a, b));
    }
};

namespace ALCSCubic
{
    vector <size_t> LCS(const string &a, const string &b)
    {
        vector <vector <size_t> > answer(a.length() + 1, vector <size_t> (b.length() + 1, 0));
        for (size_t i = 1; i <= a.length(); ++i)
        {
            for (size_t j = 1; j <= b.length(); ++j)
            {
                answer[i][j] = max(answer[i - 1][j], answer[i][j - 1]);
                if (a[i - 1] == b[j - 1])
                {
                    answer[i][j] = max(answer[i][j], answer[i - 1][j - 1] + 1);
                }
            }
        }
        return answer[a.length()];
    }
    
    vector <vector <size_t> > solution(const string &a, const string &b)
    {
        vector <vector <size_t> > answer(b.length() + 1, vector <size_t> (b.length() + 1, 0));
        for (size_t i = 0; i < b.length(); ++i)
        {
            vector <size_t> currentLCS = LCS(a, string(b.begin() + i, b.end()));
            copy(currentLCS.begin(), currentLCS.end(), answer[i].begin() + i);
        }
        return answer;
    }
};

int main()
{
    string a, b;
    cin >> a >> b;
    
    vector <vector<size_t> > restore = ALCSCubic::solution(a, b);


    for (size_t i = 0; i <= b.length(); ++i)
    {
        printf("%d:\t", i);
        for (size_t j = 0; j <= b.length(); ++j)
            printf("%d ", restore[i][j]);
        printf("\n");
    }
    return 0;
}