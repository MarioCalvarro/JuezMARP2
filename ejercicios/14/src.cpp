// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>

#define MOD 1000000007

using namespace std;
using res_t = size_t;

res_t resolver(size_t n, size_t max_salto)
{
    vector<size_t> v(n, 0); v[0] = 1;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 1; j < max_salto + 2; ++j) {
            if (i + j <= n - 1) {
                v[i + j] = (v[i] + v[i + j]) % MOD;
            }
        }
    } 

    return v[n - 1];
}

bool resuelveCaso() 
{
    //Leer
    size_t n, max_salto;
    cin >> n >> max_salto;

    if (n == 0 && max_salto == 0)
        return false;

    res_t sol = resolver(n, max_salto);

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
