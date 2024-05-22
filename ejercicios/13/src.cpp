// DG, Mario Calvarro Marines

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

using res_t = pair<bool, size_t>;
using datos_t = pair<size_t, size_t>;

res_t resolver(const vector<datos_t>& monedas, const size_t P)
{
    size_t N = monedas.size() - 1;
    vector<vector<size_t>> coins(N + 1, vector<size_t>(P + 1, INT_MAX));
    for (auto &row : coins) {
        row[0] = 0;
    }

    for (size_t i = 1; i < N + 1; i++) {
        auto const [valor, cantidad] = monedas[i];

        for (size_t j = 0; j < P + 1; ++j) {
            size_t val = coins[i - 1][j];

            for (size_t k = 1; k <= cantidad && j >= k * valor; k++) {
                val = min(val, coins[i - 1][j - k * valor] + k);
            }

            coins[i][j] = val;
        }
    }

    return {coins[N][P] != INT_MAX, coins[N][P]};
}

bool resuelveCaso() 
{
    //Leer
    size_t N;
    cin >> N;

    if (!std::cin)
        return false;


    vector<datos_t> monedas(N + 1);
    monedas[0] = {0, 0};
    for (size_t i = 1; i <= N; i++) {
        cin >> monedas[i].first;
    }
    for (size_t i = 1; i <= N; i++) {
        cin >> monedas[i].second;
    }
    sort(monedas.begin(), monedas.end());

    size_t P; cin >> P;

    res_t sol = resolver(monedas, P);

    //Escribir
    if (sol.first) {
        cout << "SI " << sol.second;
    } else {
        cout << "NO";
    }

    cout << '\n';

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
