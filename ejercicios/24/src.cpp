// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using res_t = size_t;
using matriz_t = vector<vector<vector<bool>>>;

enum Fruta {Nada, Naranja, Limon};

res_t resolver(const vector<Fruta> &b)
{
    int n = b.size();

    vector<vector<int>> tabla(n, vector<int>(n));
    for (int i = n - 2; 0 <= i; i--) {
        for (int j = i + 1; j < n; j++) {
            //Coinciden uno de cada lado
            if (b[i] == b[j] && b[i] != Nada) {
                tabla[i][j] = 1 + tabla[i + 1][j - 1];
            }
            //Coinciden a la izquierda
            else if (b[i] == b[i + 1] && b[i] != Nada) {
                tabla[i][j] = 1 + (i + 2 < n ? tabla[i + 2][j] : 0);
            }
            //Coinciden a la derecha
            else if (b[j] == b[j - 1] && b[j] != Nada) {
                tabla[i][j] = 1 + (0 <= j - 2 ? tabla[i][j - 2] : 0);
            }
            //No coinciden en ningun caso
            else {
                tabla[i][j] = max(max(0 <= j - 2 ? tabla[i][j - 2] : 0, i + 2 < n ? tabla[i + 2][j] : 0), tabla[i + 1][j - 1]);
            }
        }
    }
    return tabla[0][n - 1];
}

bool resuelveCaso() 
{
    //Leer
    size_t N;
    cin >> N;

    if (!std::cin)
        return false;

    vector<Fruta> v(N);
    for (size_t i = 0; i < N; i++) {
        size_t x; cin >> x;
        switch(x) {
            case 0: v[i] = Nada; break;
            case 1: v[i] = Naranja; break;
            default: v[i] = Limon;
        }
    }

    res_t sol = resolver(v);

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
