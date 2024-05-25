// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using matriz_t = vector<vector<int>>;

void resolver(matriz_t &m)
{
    int n = m.size();
    for (int i = n - 2; 0 <= i; i--) {
        for (int j = i + 1; j < n; j++) {
            for (int k = i; k < j; k++) {
                m[i][j] = std::min(m[i][j], m[i][k] + m[k + 1][j]);
            }
        }
    }
}

bool resuelveCaso() 
{
    //Leer
    int N;
    cin >> N;

    if (!std::cin)
        return false;

    N--;
    matriz_t c(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            cin >> c[i][j];
        }
    }
    resolver(c);

    //Escribir
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            cout << c[i][j] << ' ';
        }
        cout << '\n';
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
