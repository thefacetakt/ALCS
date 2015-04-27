#include <cstdio>
#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <algorithm>

namespace ALCSSquare
{
    const size_t SIZE_T_MAX(-1);

    std::vector <std::vector <size_t> > parseCriticalPoints(const std::vector <size_t> &criticalPoints)
    {
        std::vector <std::vector <size_t> > restore(criticalPoints.size() + 1, std::vector <size_t> (criticalPoints.size() + 1, 0));
        
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

    std::vector <size_t> getCriticalPoints(const std::string &a, const std::string &b)
    {
        std::vector <std::vector <size_t> > horisontalEdges(a.length() + 1, std::vector <size_t> (b.length() + 1, 0));
        for (size_t j = 0; j <= b.length(); ++j)
        {
            horisontalEdges[0][j] = j;
        }
        std::vector <std::vector <size_t> > verticalEdges(a.length() + 1, std::vector <size_t>    (b.length() + 1, 0));
        for (size_t i = 1; i <= a.length(); ++i)
        {
            for (size_t j = 1; j <= b.length(); ++j)
            {
                if (a[i - 1] != b[j - 1])
                {
                    horisontalEdges[i][j] = std::max(verticalEdges[i][j - 1], horisontalEdges[i - 1][j]);
                    verticalEdges[i][j] = std::min(verticalEdges[i][j - 1], horisontalEdges[i - 1][j]);
                }
                else
                {
                    horisontalEdges[i][j] = verticalEdges[i][j - 1];
                    verticalEdges[i][j] = horisontalEdges[i - 1][j];
                }
            }
        }
        
        std::vector <size_t> criticalPoints(b.length() + 1, INT_MAX);
        
        for (size_t j = 1; j <= b.length(); ++j)
        {
            if (horisontalEdges[a.length()][j] != 0)
            {   
                criticalPoints[horisontalEdges[a.length()][j]] = j;
            }
        }
        return criticalPoints;
    }

    std::vector <std::vector <size_t> > solution(const std::string &a, const std::string &b)
    {
        return parseCriticalPoints(getCriticalPoints(a, b));
    }
};

namespace ALCSCubic
{
    std::vector <size_t> LCS(const std::string &a, const std::string &b)
    {
        std::vector <std::vector <size_t> > answer(a.length() + 1, std::vector <size_t> (b.length() + 1, 0));
        for (size_t i = 1; i <= a.length(); ++i)
        {
            for (size_t j = 1; j <= b.length(); ++j)
            {
                answer[i][j] = std::max(answer[i - 1][j], answer[i][j - 1]);
                if (a[i - 1] == b[j - 1])
                {
                    answer[i][j] = std::max(answer[i][j], answer[i - 1][j - 1] + 1);
                }
            }
        }
        return answer[a.length()];
    }
    
    std::vector <std::vector <size_t> > solution(const std::string &a, const std::string &b)
    {
        std::vector <std::vector <size_t> > answer(b.length() + 1, std::vector <size_t> (b.length() + 1, 0));
        for (size_t i = 0; i < b.length(); ++i)
        {
            std::vector <size_t> currentLCS = LCS(a, std::string(b.begin() + i, b.end()));
            std::copy(currentLCS.begin(), currentLCS.end(), answer[i].begin() + i);
        }
        return answer;
    }
};

int main(int argc, char **argv)
{
    std::string a, b;
    std::cin >> a >> b;
    
    std::vector <std::vector<size_t> > restore = ALCSSquare::solution(a, b);


    for (size_t i = 0; i <= b.length(); ++i)
    {
        std::cout << i << "\t";
        for (size_t j = 0; j <= b.length(); ++j)
            std::cout << restore[i][j] << "\t";
        std::cout << std::endl;
    }
    return 0;
}