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
    size_t k, tiempo, optimista;
    vector<bool> asignado;
};

bool operator<(const Nodo& lhs, const Nodo& rhs) {
    return lhs.optimista > rhs.optimista;
}

void rellenar_cota_inferior(cota_t &cota, const matriz_t &m) {
    size_t n = cota.size();
    size_t min_fila = 10001;

    for (size_t j = 0; j < n; ++j) {
        min_fila = min(min_fila, m[n-1][j]);
    }
    cota[n - 1] = min_fila;

    for (size_t i = n-1; i > 0; i--) {
        size_t aux_i = i - 1;
        min_fila = 10001;

        for (size_t j = 0; j < n; ++j) {
            min_fila = min(min_fila, m[aux_i][j]);
        }

        cota[aux_i] = min_fila + cota[aux_i + 1];
    }
}

void rellenar_cota_superior(cota_t &cota, const matriz_t &m) {
    size_t n = cota.size();
    size_t max_fila = 0;

    for (size_t j = 0; j < n; ++j) {
        max_fila = max(max_fila, m[n-1][j]);
    }
    cota[n - 1] = max_fila;

    for (size_t i = n-1; i > 0; i--) {
        size_t aux_i = i - 1;
        max_fila = 0;

        for (size_t j = 0; j < n; ++j) {
            max_fila = max(max_fila, m[aux_i][j]);
        }

        cota[aux_i] = max_fila + cota[aux_i + 1];
    }
}

res_t resolver(const matriz_t &m, const cota_t &c_inf, const cota_t &c_sup)
{
    size_t n = m.size();

    //Raíz
    Nodo y = {0, 0, 0, vector<bool>(n, false)};
    size_t mejor_tiempo = y.tiempo + c_sup[y.k];      //Cota superior

    priority_queue<Nodo> cola;
    cola.push(y);

    //Cota inferior
    while (!cola.empty() && (cola.top().tiempo + c_inf[cola.top().k]) <= mejor_tiempo) {
        y = cola.top(); cola.pop();

        for (size_t i = 0; i < n; ++i) {
            if (!y.asignado[i]) {
                Nodo x = {y.k + 1, y.tiempo + m[y.k][i], 0, y.asignado};
                x.optimista = x.tiempo + c_inf[x.k];    //Cota inferior
                x.asignado[i] = true;

                if (x.k == n) {     //Solución?
                    if (x.tiempo < mejor_tiempo) {
                        mejor_tiempo = x.tiempo;
                    }
                } else {
                    if (x.optimista <= mejor_tiempo) {
                        cola.push(x);

                        //Cota superior
                        if ((x.tiempo + c_sup[x.k]) < mejor_tiempo) {
                            mejor_tiempo = x.tiempo + c_sup[x.k];
                        }
                    }
                }
            }
        }
    }

    return mejor_tiempo;
}

bool resuelveCaso()
{
    //Leer
    size_t n;
    cin >> n;

    if (n == 0)
        return false;

    matriz_t matriz (n, vector<size_t>(n, 0));
    for (auto &row : matriz) {
        for (auto &col : row) {
            cin >> col;
        }
    }

    cota_t cota_inferior(n), cota_superior(n);
    rellenar_cota_inferior(cota_inferior, matriz);
    rellenar_cota_superior(cota_superior, matriz);

    res_t sol = resolver(matriz, cota_inferior, cota_superior);

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
