// DG, Mario Calvarro Marines

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

// Por el enunciado la puntuacion máxima es 500
#define MAX_ENT 550

using namespace std;

// Resultado: Posible y, si lo es, la solución
using res_t = pair<bool, vector<int>>;

res_t resolver(int objetivo, const vector<int> &puntuaciones) {
    int S = puntuaciones.size();
    vector<int> dardos(objetivo + 1, MAX_ENT);

    // Caso base
    dardos[0] = 0;

    for (int i = 0; i < S; ++i) {
        for (int j = puntuaciones[i]; j <= objetivo; ++j) {
            dardos[j] = min(dardos[j], dardos[j - puntuaciones[i]] + 1);
        }
    }

    if (dardos[objetivo] == MAX_ENT) {
        return {false, vector<int>()};
    }

    vector<int> solucion = vector<int>();
    int j = objetivo, i = S - 1;

    while (j > 0) {
        if (puntuaciones[i] <= j && dardos[j] > dardos[j - puntuaciones[i]]) {
            solucion.push_back(puntuaciones[i]);
            j -= puntuaciones[i];
        } else {
            i -= 1;
        }
    }

    return {true, solucion};
}

bool resuelveCaso() {
    // Leer
    int objetivo, sectores;
    cin >> objetivo >> sectores;

    if (!cin)
        return false;

    vector<int> puntuaciones(sectores);

    for (int i = 0; i < sectores; ++i) {
        cin >> puntuaciones[i];
    }

    res_t sol = resolver(objetivo, puntuaciones);

    bool posible = sol.first;
    vector<int> dardos = sol.second;

    if (posible) {
        cout << dardos.size() << ':';
        for (auto dardo : dardos) {
            cout << ' ' << dardo;
        }
        cout << '\n';
    } else {
        cout << "Imposible\n";
    }

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
