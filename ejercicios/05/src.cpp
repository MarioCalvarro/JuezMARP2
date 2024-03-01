// DG, Mario Calvarro Marines

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

using Matriz = vector<vector<size_t>>;

size_t resolver(Matriz& tablero) {
    size_t n = tablero.size(), m = tablero[0].size();

    //Posibles caminos desde (i,j) hasta (n,m)
    Matriz tabla = Matriz(n, vector<size_t>(m, 0));

    //Camino constante
    tabla[n-1][m-1] = 1;
    for (size_t i = n; i > 0; --i) {
        for (size_t ii = m; ii > 0; --ii) {
            size_t r = i - 1, c = ii - 1;
            size_t salto = tablero[r][c];
            if (r + salto < n) {
                tabla[r][c] += tabla[r + salto][c];
            }
            if (c + salto < m) {
                tabla[r][c] += tabla[r][c + salto];
            }
        }
    }
    

    return tabla[0][0];
}

bool resuelveCaso() {
    // Leer
    int n, m;
    cin >> n >> m;

    if (!cin)
        return false;

    Matriz tablero = Matriz(n, vector<size_t>(m));

    for (size_t i = 0; i < n; i++) {
        for (size_t ii = 0; ii < m; ii++) {
            cin >> tablero[i][ii];
        }
    }

    cout << resolver(tablero) << '\n';

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
