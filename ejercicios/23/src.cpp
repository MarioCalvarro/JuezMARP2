// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using res_t = bool;
using matriz_t = vector<vector<vector<bool>>>;

res_t resolver(const string &s)
{
    int n = s.size();
    matriz_t tabla(n, vector<vector<bool>>(n, vector<bool>(3, false)));

    for (int i = 0; i < n; i++) {
        tabla[i][i][s[i] - 'a'] = true;
    }

    for (int d = 1; d < n; d++) {
        for (int i = 0; i < n - d; i++) {
            int j = i + d;
            for (int k = i; k < j; k++) {
              tabla[i][j][0] = tabla[i][j][0] ||
                               (tabla[i][k][0] && tabla[k + 1][j][2]) ||
                               (tabla[i][k][1] && tabla[k + 1][j][2]) ||
                               (tabla[i][k][2] && tabla[k + 1][j][0]);

              tabla[i][j][1] = tabla[i][j][1] ||
                               (tabla[i][k][0] && tabla[k + 1][j][0]) ||
                               (tabla[i][k][0] && tabla[k + 1][j][1]) ||
                               (tabla[i][k][1] && tabla[k + 1][j][1]);

              tabla[i][j][2] = tabla[i][j][2] ||
                               (tabla[i][k][1] && tabla[k + 1][j][0]) ||
                               (tabla[i][k][2] && tabla[k + 1][j][1]) ||
                               (tabla[i][k][2] && tabla[k + 1][j][2]);
            }
        }
    }

    return tabla[0][n-1][0];
}

bool resuelveCaso() 
{
    //Leer
    string exp;
    cin >> exp;

    if (!std::cin)
        return false;

    res_t sol = resolver(exp);

    //Escribir
    cout << (sol? "SI" : "NO") << '\n';

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
