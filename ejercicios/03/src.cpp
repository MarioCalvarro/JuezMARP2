// DG, Mario Calvarro Marines

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

using Matriz = vector<vector<char>>;

size_t resolver(const Matriz& ciudad) {
    return 0;
}

bool resuelveCaso() {
    // Leer
    int fil, col;
    cin >> fil >> col;

    if (!cin)
        return false;

    Matriz ciudad = Matriz(fil, vector<char>(col));

    for (size_t i = 0; i < fil; i++) {
        for (size_t ii = 0; ii < col; ii++) {
            cin >> ciudad[i][ii];
        }
    }

    cout << resolver(ciudad);

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso())
        ;

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
