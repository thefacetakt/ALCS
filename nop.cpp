#include <bits/stdc++.h>
int main() {
    std::string a, c;
    std::cin >> a >> c;
    std::vector <std::vector <int> > answer(a.size() + 1, std::vector <int> (c.size() + 1, 0)), answer2(c.size() + 1, std::vector <int>(c.size() + 1));
    for (int y = 0; y < c.size(); ++y) for (int i = 1; i <= a.size(); ++i) for (int j = 1; j <= c.size() - y; ++j) (i == a.size() ? answer2[y][j] : answer[i][j]) = std::max(std::max(answer[i - 1][j], answer[i][j - 1]), answer[i - 1][j - 1] + (a[i - 1] == c[y + j - 1]));
    for (int y = 0; y <= c.size(); ++y) for (int u = 0; u < c.size(); ++u) (y == c.size() ? void(exit(0)) : void(std::cout << (u < y ? "  " : std::to_string(answer2[y][u - y + 1]) + (u + 1 == c.size() ? "\n" : " "))));
}