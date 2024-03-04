// DG, Mario Calvarro Marines

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

//first: número de letras añadidas
//second: palabra final
using res_t = pair<size_t, string>;

using matriz_t = vector<vector<size_t>>;

size_t aibofobia(const string& word, matriz_t& tabla) {
    size_t n = word.size();
    for (size_t d = 1; d < n; ++d) {
        for (size_t ii = d; ii < n; ++ii) {
            size_t r = ii-d, c = ii;
            if (word[r] == word[c]) {
                tabla[r][c] = tabla[r+1][c-1];
            }
            else {
                tabla[r][c] = min(tabla[r+1][c], tabla[r][c-1]) + 1;
            }
        }
    }
    return tabla[0][n-1];
}

void reconstruir_sol(const string& word, const matriz_t& tabla, string& nueva_palabra) {
    
}

res_t resolver(const string& word) {
    size_t n = word.size();
    matriz_t tabla = matriz_t(n, vector<size_t>(n, 0));
    size_t num_letras = aibofobia(word, tabla);

    string nueva_palabra = "";
    reconstruir_sol(word, tabla, nueva_palabra);
    return {num_letras, nueva_palabra};
}

bool resuelveCaso() {
    // Leer
    string word;
    cin >> word;

    if (!cin)
        return false;

    res_t sol = resolver(word);

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
