// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using res_t = int;
using matriz_t = vector<vector<int>>;

res_t resolver(const string &s)
{
    int n = s.size();
    vector<vector<int>> m(n, vector<int>(n, n));

    for (int i = 0; i < n; i++) {
        m[i][i] = 1; 
    }
    
    for (int i = n - 2; 0 <= i; i--) {
        for (int j = i + 1; j < n; j++) {
            if (s[i] == s[i + 1]) {
                m[i][j] = min(m[i][j], m[i + 1][j]);
            }
            if (s[j] == s[j - 1]) {
                m[i][j] = min(m[i][j], m[i][j - 1]);
            }
            if (s[i] == s[j]) {
                m[i][j] = min(m[i][j], m[i + 1][j - 1] + 1);
            }

            m[i][j] = min(m[i][j], min(m[i + 1][j], m[i][j - 1]) + 1);
        }
    }
    return m[0][n - 1];
}

bool resuelveCaso() 
{
    //Leer
    string s;
    cin >> s;

    if (!std::cin)
        return false;

    res_t sol = resolver(s);

    //Escribir
    cout << sol << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
