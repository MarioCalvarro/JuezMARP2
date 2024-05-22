// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <limits.h>

using namespace std;

using res_t = size_t;
//Min, formas
using dato_t = pair<size_t, size_t>;

res_t resolver(size_t pagar, const vector<size_t> &monedas)
{
    size_t n = monedas.size();
    vector<dato_t> v(pagar + 1, {INT_MAX, 0});
    v[0] = {0, 1};

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = monedas[i]; j < pagar + 1; ++j) {
            //Nuevo mínimo
            if (v[j - monedas[i]].first + 1 < v[j].first) {
                v[j] = {v[j - monedas[i]].first + 1, v[j - monedas[i]].second};
            }
            //Otra forma para el mismo mínimo
            else if (v[j - monedas[i]].first + 1 == v[j].first) {
                v[j].second += v[j - monedas[i]].second;
            }
        }
    }    

    return v[pagar].second;
}

bool resuelveCaso()
{
    //Leer
    size_t pagar, n;
    cin >> pagar >> n;

    if (!std::cin)
        return false;

    vector<size_t> monedas(n);
    for (auto &m : monedas) {
        cin >> m;
    }

    res_t sol = resolver(pagar, monedas);

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
