// DG, Mario Calvarro Marines

#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

//Vamos a pasar las nombres a identificadores
using linea_t = vector<size_t>;

//Vamos construyendo la solución parcial
using matriz_t = vector<vector<pair<vector<size_t>, vector<size_t>>>>;

// linea_t resolver(const linea_t& linea1, const linea_t& linea2)
// {
//     //Tabla(i, j): solución parcial considerando hasta i de la primera linea y
//     //hasta j de la segunda
//     //
//     //Si i = 0 || j = 0 → no consideramos ninguna canción de alguna de las listas → lista
//     //vacía
//     size_t n = linea1.size(), m = linea2.size();
//     matriz_t tabla = matriz_t(n + 1, vector<linea_t>(m + 1, linea_t()));
//
//     for (size_t d = 2; d < n + m + 1; ++d)
//     {
//         size_t fila_ini = min(d, n);
//         size_t col_ini = d - fila_ini;
//         size_t len_diag = min(fila_ini, m - col_ini) + 1;
//
//         for (int j = 0; j < len_diag; ++j)
//         {
//             size_t r  = fila_ini - j, c = col_ini + j;
//             
//             if (r > 0 && c > 0) {
//                 if (tabla[r-1][c].size() >= tabla[r][c-1].size()) {
//                     tabla[r][c] = tabla[r-1][c];
//                 }
//                 else {
//                     tabla[r][c] = tabla[r][c-1];
//                 }
//
//                 if (linea1[r - 1] == linea2[c - 1]) {
//                     tabla[r][c].push_back(linea1[r-1]);
//                 }
//             }
//         }
//     }
//
//     return tabla[linea1.size()][linea2.size()];
// }

pair<vector<size_t>, vector<size_t>> resolver2(const linea_t& linea1, const linea_t& linea2)
{
    size_t n = linea1.size(), m = linea2.size();
    matriz_t tabla = matriz_t(n + 1, vector<pair<vector<size_t>, vector<size_t>>>(m+1, {vector<size_t>(), vector<size_t>()}));

    for (size_t d = 2; d < n + m + 1; ++d)
    {
        size_t fila_ini = min(d, n);
        size_t col_ini = d - fila_ini;
        size_t len_diag = min(fila_ini, m - col_ini) + 1;

        for (int j = 0; j < len_diag; ++j)
        {
            size_t r  = fila_ini - j, c = col_ini + j;

            if (r > 0 && c > 0) {
                if (tabla[r-1][c].first.size() == tabla[r][c-1].first.size()
                    && n + 1 - r >= m + 1 - c)
                {
                    tabla[r][c] = tabla[r-1][c];
                }
                else if (tabla[r-1][c].first.size() == tabla[r][c-1].first.size()
                    && n + 1 - r < m + 1 - c)
                {
                    tabla[r][c] = tabla[r][c-1];
                }
                else if (tabla[r-1][c].first.size() > tabla[r][c-1].first.size()) {
                    tabla[r][c] = tabla[r-1][c];
                }
                else {
                    tabla[r][c] = tabla[r][c-1];
                }

                if (linea1[r - 1] == linea2[c - 1]
                    && (!binary_search(tabla[r][c].first.begin(), tabla[r][c].first.end(), r-1)
                    && !binary_search(tabla[r][c].second.begin(), tabla[r][c].second.end(), c-1)))
                {
                    tabla[r][c].first.push_back(r-1);
                    tabla[r][c].second.push_back(c-1);
                }
            }
        }
    }

    return tabla[n][m];
}

bool resuelveCaso() 
{
    //Leer
    vector<int> cl;
    string line;
    getline(cin, line);

    if (!cin)
        return false;

    unordered_map<string, size_t> nombres_id;
    vector<string> id_nombres;

    vector<size_t> linea1;
    vector<size_t> linea2;

    string aux; size_t aux_id = 0;
    istringstream iss1(line);
    while (iss1 >> aux) {
        if (!nombres_id.count(aux)) {
            id_nombres.push_back(aux);
            nombres_id[aux] = aux_id++;
        }
        linea1.push_back(nombres_id[aux]);
    }

    getline(cin, line);
    istringstream iss2(line);
    while (iss2 >> aux) {
        if (!nombres_id.count(aux)) {
            nombres_id[aux] = aux_id++;
        }
        linea2.push_back(nombres_id[aux]);
    }

    auto sol = resolver2(linea1, linea2);

    //Escribir
    for (size_t i = 0; i < sol.first.size(); ++i) {
        cout << id_nombres[linea1[sol.first[i]]] << ' ';
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
