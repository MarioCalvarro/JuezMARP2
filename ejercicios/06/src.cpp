// DG, Mario Calvarro Marines
// Descenso = profundidad
// Ascenso = 2 * profundidad
// Total = 3 * profundidad

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//first: profundidad
//second: oro
using cofre_t = pair<size_t, size_t>;

//first: oro total
//second: cofres elegidos y número
using res_t = pair<size_t, pair<vector<bool>, size_t>>;

//a_{i,j} = valor con j seg restante y considerados los objetos hasta i
using Matrix = vector<vector<size_t>>;

res_t resolver(size_t segundos_disp, const vector<cofre_t>& cofres) {
    size_t n = cofres.size() + 1, m = segundos_disp+1;
    Matrix tabla = Matrix(n, vector<size_t>(m, 0));

    for (size_t i = 1; i < n; ++i) {
        size_t coste_real = 3*cofres[i-1].first;
        for (size_t ii = 1; ii < m; ++ii) {
            if (coste_real > ii) {
                tabla[i][ii] = tabla[i-1][ii];
            }
            else {
                tabla[i][ii] = max(tabla[i-1][ii],
                                   tabla[i-1][ii - coste_real] + cofres[i-1].second);
            }
        }
    }

    size_t resto = segundos_disp, total = 0;
    vector<bool> elegidos = vector<bool>(cofres.size(), false);
    for (size_t i = n-1; i > 0; --i) {
        if (!(tabla[i][resto] == tabla[i-1][resto])) {
            elegidos[i-1] = true;
            resto -= 3*cofres[i-1].first;
            total += 1;
        }
    }

    return {tabla[n-1][segundos_disp], {elegidos, total}};
}

bool resuelveCaso() {
    // Leer
    int segundos_disp, num_cofres;
    cin >> segundos_disp >> num_cofres;

    if (!cin)
        return false;

    size_t prof, oro;
    vector<cofre_t> cofres = vector<cofre_t>(num_cofres);
    for (size_t i = 0; i < num_cofres; ++i) {
        cin >> prof >> oro;
        cofres[i] = {prof, oro};
    }

    res_t sol = resolver(segundos_disp, cofres);

    cout << sol.first << '\n' << sol.second.second << '\n';
    for (size_t i = 0; i < sol.second.first.size(); ++i) {
        if (sol.second.first[i]) {
            cout << cofres[i].first << ' ' << cofres[i].second << '\n';
        }
    }

    cout << "---\n";

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
