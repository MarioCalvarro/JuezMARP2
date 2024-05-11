// DG, Mario Calvarro Marines

#include <algorithm>
#include <climits>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using res_t = int;

res_t resolver(const vector<size_t> &cortes)
{
    size_t n = cortes.size();
    //0 y l son puntos
    vector<vector<size_t>> matriz(n, vector<size_t>(n, 0));

    for (size_t d = 2; d < n; d++) {
        for (size_t i = 0; i < n - d; i++) {
            size_t j = d + i;
            size_t mejor = INT_MAX;
            for (size_t m = i + 1; m < j; m++) {
                mejor = min(mejor, matriz[i][m] + matriz[m][j]);
            }
            matriz[i][j] = mejor + 2 * (cortes[j] - cortes[i]);
        }
    }

    return matriz[0][n - 1];
}

bool resuelveCaso() 
{
    //Leer
    size_t L, N;
    cin >> L >> N;

    if (L == 0)
        return false;

    vector<size_t> cortes(N + 2, 0);

    cortes[0] = 0; cortes[cortes.size() - 1] = L;
    size_t aux;
    for (size_t i = 1; i < cortes.size() - 1; i++) {
        cin >> aux;
        cortes[i] = aux;
    }

    res_t sol = resolver(cortes);

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
