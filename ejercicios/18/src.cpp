// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

using matriz_t = vector<vector<size_t>>;
using cota_t = vector<size_t>;
using res_t = size_t;

struct Nodo {
    size_t k, nieve, optimista;
    vector<bool> asignado;
};

bool operator<(const Nodo& lhs, const Nodo& rhs) {
    return lhs.optimista < rhs.optimista;
}

void rellenar_cota_inferior(cota_t &cota, const matriz_t &m) {
    size_t N = cota.size();
    size_t M = m[0].size();
    size_t min_fila = 10001;

    for (size_t j = 0; j < M; ++j) {
        min_fila = min(min_fila, m[N-1][j]);
    }
    cota[N - 1] = min_fila;

    for (size_t i = N-1; i > 0; i--) {
        size_t aux_i = i - 1;
        min_fila = 10001;

        for (size_t j = 0; j < M; ++j) {
            min_fila = min(min_fila, m[aux_i][j]);
        }

        cota[aux_i] = min_fila + cota[aux_i + 1];
    }
}

void rellenar_cota_superior(cota_t &cota, const matriz_t &m) {
    size_t N = cota.size();
    size_t M = m[0].size();
    size_t max_fila = 0;

    for (size_t j = 0; j < M; ++j) {
        max_fila = max(max_fila, m[N-1][j]);
    }
    cota[N - 1] = max_fila;

    for (size_t i = N-1; i > 0; i--) {
        size_t aux_i = i - 1;
        max_fila = 0;

        for (size_t j = 0; j < M; ++j) {
            max_fila = max(max_fila, m[aux_i][j]);
        }

        cota[aux_i] = max_fila + cota[aux_i + 1];
    }
}

res_t resolver(const matriz_t &m, const cota_t &c_inf, const cota_t &c_sup,
        const vector<size_t> &carros, const vector<size_t> &caminos)
{
    size_t N = m.size();
    size_t M = m[0].size();

    //Raíz
    Nodo y = {0, 0, 0, vector<bool>(M)};
    size_t mayor_nieve = y.nieve + c_inf[y.k];

    priority_queue<Nodo> cola;
    cola.push(y);

    while (!cola.empty() && (cola.top().nieve + c_sup[cola.top().k]) >= mayor_nieve) {
        y = cola.top(); cola.pop();

        for (size_t i = 0; i < M; ++i) {
            if (!y.asignado[i] && carros[y.k] <= caminos[i]) {
                Nodo x = {y.k + 1, y.nieve + m[y.k][i], 0, y.asignado};
                x.optimista = x.nieve + c_sup[x.k];
                x.asignado[i] = true;

                if (x.k == N) {     //Solución?
                    if (x.nieve > mayor_nieve) {
                        mayor_nieve = x.nieve;
                    }
                } else {
                    if (x.optimista >= mayor_nieve) {
                        cola.push(x);

                        if ((x.nieve + c_inf[x.k]) > mayor_nieve) {
                            mayor_nieve = x.nieve + c_inf[x.k];
                        }
                    }
                }
            }
        }
    }

    return mayor_nieve;
}

bool resuelveCaso()
{
    //Leer
    size_t n, m;
    cin >> n >> m;

    vector<size_t> carros(n);
    for (auto &c : carros) {
        cin >> c;
    }

    vector<size_t> caminos(m);
    for (auto &c : caminos) {
        cin >> c;
    }

    matriz_t matriz (n, vector<size_t>(m, 0));
    for (size_t i = 0; i < n; i++) {
        for (size_t ii = 0; ii < m; ii++) {
            cin >> matriz[i][ii];
        }
    }

    cota_t cota_inferior(n), cota_superior(n);
    rellenar_cota_inferior(cota_inferior, matriz);
    rellenar_cota_superior(cota_superior, matriz);

    res_t sol = resolver(matriz, cota_inferior, cota_superior, carros, caminos);

    //Escribir
    cout << sol << '\n';

    return true;
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
