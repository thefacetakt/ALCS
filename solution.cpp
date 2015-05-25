#include <cstdio>
#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <algorithm>
#include <random>

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



namespace Testing
{
    
    std::string currentString[2];
    
    bool test(const std::string &a, const std::string &b)
    {
        return (ALCSSquare::solution(a, b) != ALCSCubic::solution(a, b));
    }
    
    namespace TestEveryPossibleString
    {
        const char alphabet[] = {'A', 'T', 'G', 'C'};
        const int alphabetSize = 4;
        const int MAXN = 5;
        
        bool generate(size_t i, size_t currentStringIndex)
        {
            if (i != 0)
            {
                if (currentStringIndex == 0)
                {
                    if (!generate(0, currentStringIndex + 1))
                    {
                        return false;
                    }
                }
                else
                {
                    if (!test(currentString[0], currentString[1]))
                    {
                        return false;
                    }
                }
            }
            if (i != MAXN)
            {
                for (size_t j = 0; j < alphabetSize; ++j)
                {
                    currentString[currentStringIndex].push_back(alphabet[j]);
                    if (!generate(i + 1, currentStringIndex))
                    {
                        return false;
                    }
                    currentString[currentStringIndex].pop_back();
                }
            }
            return true;
        }
    };
    
    namespace TestRandomString
    {
        
        std::default_random_engine generator;
        void init()
        {
            generator.seed(1);
        }
        
        bool generate(int maxN, char maxLetter, bool measureTime)
        {
            std::uniform_int_distribution<size_t> sizeGetter(1, maxN);
            std::uniform_int_distribution<char> letterGetter('a', maxLetter);
            size_t length[2];
            for (size_t i = 0; i < 2; ++i)
            {
                length[i] = sizeGetter(generator);
                currentString[i].resize(length[i]);
                for (size_t j = 0; j < length[i]; ++j)
                    currentString[i][j] = letterGetter(generator);
            }
            if (!measureTime)
            {
                return test(currentString[0], currentString[1]);
            }
            else
            {
                FILE *timeLog = fopen("timeLog.txt", "a");
                clock_t start = clock();
                ALCSSquare::solution(currentString[0], currentString[1]);
                fprintf(timeLog, "%zu, %lf\n", length[0] * length[1], static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
                fclose(timeLog);
                return true;
            }
        }
    };
    
    void test()
    {
        FILE *timeLog = fopen("timeLog.txt", "w");
        fclose(timeLog);
        const char smallLetter = 'd';
        const char largeLetter = 'z';
        
        if (!TestEveryPossibleString::generate(0, 0))
        {
            return void(printf("FAIL\n"));
        }
        printf("OK ALL POSSIBLE TEST\n");
        TestRandomString::init();
        
        for (size_t i = 1; i <= 500; i += 10)
        {
            if (!TestRandomString::generate(i, smallLetter, 0) || !TestRandomString::generate(i, largeLetter, 0))
            {
                return void(printf("FAIL\n"));
            }
        }
        for (size_t i = 1; i <= 5000; i += 50)
        {
            TestRandomString::generate(i, smallLetter, 1);
            TestRandomString::generate(i, largeLetter, 1);
        }
        printf("OK RANDOM TESTS\n");
    }
};

int main(int argc, char **argv)
{
    Testing::test();
    return 0;
}