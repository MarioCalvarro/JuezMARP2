// DG, Mario Calvarro Marines

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//first: valor solución
//second: columna en la última fila
using res_t = pair<size_t, size_t>;

using Matriz = vector<vector<size_t>>;

res_t resolver(Matriz& tablero) {
    size_t n = tablero.size();

    //Primera fila se queda igual
    for (size_t i = 1; i < n; ++i) {
        for (size_t ii = 0; ii < n; ++ii) {
            size_t aux = tablero[i-1][ii];
            if (ii > 0 && tablero[i-1][ii-1] > aux) {
                aux = tablero[i-1][ii-1];
            }
            if (ii < n-1 && tablero[i-1][ii+1] > aux) {
                aux = tablero[i-1][ii+1];
            }
            tablero[i][ii] += aux;
        }
    }

    //Encontramos el máximo de la última fila
    size_t max_value = tablero[n-1][0], pos = 1;
    for (size_t ii = 1; ii < n; ++ii) {
        if (tablero[n-1][ii] > max_value) {
            max_value = tablero[n-1][ii];
            pos = ii + 1;
        }
    }

    return {max_value, pos};
}

bool resuelveCaso() {
    // Leer
    int n;
    cin >> n;

    if (!cin)
        return false;

    Matriz tablero = Matriz(n, vector<size_t>(n));

    for (size_t i = 0; i < n; i++) {
        for (size_t ii = 0; ii < n; ii++) {
            cin >> tablero[i][ii];
        }
    }

    res_t sol = resolver(tablero);
    cout << sol.first << ' ' << sol.second << '\n';

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
