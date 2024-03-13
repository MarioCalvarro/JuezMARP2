// DG, Mario Calvarro Marines

#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

//Vamos a pasar las nombres a identificadores
using linea_t = vector<size_t>;

using sol_t = pair<unordered_set<size_t>, unordered_set<size_t>>;

//Vamos construyendo la solución parcial
using matriz_t = vector<vector<sol_t>>;

sol_t resolver(const linea_t& linea1, const linea_t& linea2)
{
    size_t n = linea1.size(), m = linea2.size();
    matriz_t tabla = matriz_t(n + 1, vector<sol_t>(m+1, {unordered_set<size_t>(), unordered_set<size_t>()}));

    for (size_t d = 2; d < n + m + 1; ++d)
    {
        size_t fila_ini = min(d, n);
        size_t col_ini = d - fila_ini;
        size_t len_diag = min(fila_ini, m - col_ini) + 1;

        for (int j = 0; j < len_diag; ++j)
        {
            size_t r  = fila_ini - j, c = col_ini + j;

            if (r > 0 && c > 0) {
                if (tabla[r-1][c].first.size() > tabla[r][c-1].first.size() 
                    || (tabla[r-1][c].first.size() == tabla[r][c-1].first.size()
                    && n + 1 - r >= m + 1 - c))
                {
                    tabla[r][c] = tabla[r-1][c];
                }
                else {
                    tabla[r][c] = tabla[r][c-1];
                }

                if (linea1[r - 1] == linea2[c - 1]
                    && (!tabla[r][c].first.count(r-1)
                    && !tabla[r][c].second.count(c-1)))
                {
                    tabla[r][c].first.insert(r-1);
                    tabla[r][c].second.insert(c-1);
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

    auto sol = resolver(linea1, linea2);

    //Tienen que aparecer en orden
    set<size_t> aux_set = set<size_t>();
    for (auto s : sol.first) {
        aux_set.insert(s);
    }
    //Escribir
    for (auto index : aux_set) {
        cout << id_nombres[linea1[index]] << ' ';
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
