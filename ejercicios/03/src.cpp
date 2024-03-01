// DG, Mario Calvarro Marines

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

using MatrizChars = vector<vector<char>>;
using MatrizInts = vector<vector<size_t>>;

size_t resolver(const MatrizChars& ciudad) {
    size_t n = ciudad.size(), m = ciudad[0].size();
    MatrizInts tabla = MatrizInts(n, vector<size_t>(m, 0));

    //Camino constante
    tabla[n - 1][m - 1] = 1;
    for (int i = n - 1; i >= 0; --i) {
        for (int ii = m - 1; ii >= 0; --ii) {
            if (i < n - 1 && ciudad[i][ii] == '.' && ciudad[i + 1][ii] == '.') {
                tabla[i][ii] += tabla[i + 1][ii];
            }
            if (ii < m - 1 && ciudad[i][ii] == '.' && ciudad[i][ii + 1] == '.') {
                tabla[i][ii] += tabla[i][ii + 1];
            }
        }
    }

    return tabla[0][0];
}

bool resuelveCaso() {
    // Leer
    int fil, col;
    cin >> fil >> col;

    if (!cin)
        return false;

    MatrizChars ciudad = MatrizChars(fil, vector<char>(col));

    for (size_t i = 0; i < fil; i++) {
        for (size_t ii = 0; ii < col; ii++) {
            cin >> ciudad[i][ii];
        }
    }

    cout << resolver(ciudad) << '\n';

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
