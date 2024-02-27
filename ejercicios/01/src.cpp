// DG, Mario Calvarro Marines

#include <cstdint>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

//Cordeles: Longitud, coste
using cordel = pair<size_t, size_t>;

//Return: Posible, nº de formas, mínimo cuerdas, mínimo coste
using res_t = tuple<bool, size_t, size_t, size_t>;

res_t resolver(size_t longitud, const vector<cordel>& cordeles)
{
    vector<size_t> posibles(longitud + 1, 0); posibles[0] = 1;
    vector<size_t> min_cuerdas(longitud + 1, SIZE_MAX); min_cuerdas[0] = 0;
    vector<size_t> min_coste(longitud + 1, SIZE_MAX); min_coste[0] = 0;

    for (auto cordel : cordeles) {
        for (size_t l = longitud; l >= cordel.first; --l) {
            posibles[l] += posibles[l - cordel.first];
            if (min_cuerdas[l - cordel.first] < SIZE_MAX) {         //Check overflow
                min_cuerdas[l] = min(min_cuerdas[l], min_cuerdas[l - cordel.first] + 1);
                min_coste[l] = min(min_coste[l], min_coste[l - cordel.first] + cordel.second);
            }
        }
    }

    return {posibles[longitud] > 0, posibles[longitud], min_cuerdas[longitud], min_coste[longitud]};
}

bool resuelveCaso() 
{
    //Leer
    size_t N, longitud;
    cin >> N >> longitud;

    if (!cin)
        return false;

    vector<cordel> cordeles(N);

    for (size_t i = 0; i < N; i++) {
        cin >> cordeles[i].first >> cordeles[i].second;
    }


    auto [sol, posibles, min_cuerdas, min_coste] = resolver(longitud, cordeles);

    //Escribir
    if (sol) {
        cout << "SI " << posibles << ' ' << min_cuerdas << ' ' << min_coste << '\n';
    }
    else {
        cout << "NO\n";
    }

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
