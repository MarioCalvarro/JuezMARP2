// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using res_t = int;

void resuelveCaso() 
{
    //Leer
    size_t k, s;
    cin >> k >> s;

    vector<size_t> v(s + 1);
    v[0] = 1;

    for (size_t i = 1; i <= k; i++) {
        for (size_t j = 0; j + i <= s; j++) {
            v[j + i] += v[j];
        }
    }

    //Escribir
    cout << v[s] << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    size_t numCasos;
    std::cin >> numCasos;
    for (size_t i = 0; i < numCasos; ++i) 
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
