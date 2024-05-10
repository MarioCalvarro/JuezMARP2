// DG, Mario Calvarro Marines

#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>

using namespace std;

//Vamos a pasar las nombres a identificadores
using linea_t = vector<size_t>;

set<size_t> resolver(const linea_t& ordenadas1, const linea_t& ordenadas2, unordered_set<size_t>& desordenadas1, unordered_set<size_t>& desordenadas2) {
    vector<vector<int>> matriz(ordenadas1.size() + 1, vector<int> (ordenadas2.size() + 1, 0));

    for (int i = 1; i < matriz.size(); i++) {
        for (int j = 1; j < matriz[0].size(); j++) {
            if (!desordenadas1.count(ordenadas2[j - 1])) {
                matriz[i][j] = matriz[i][j - 1];
            }
            else if (!desordenadas2.count(ordenadas1[i - 1])) {
                matriz[i][j] = matriz[i - 1][j];
            }
            else {
                if (ordenadas1[i - 1] == ordenadas2[j - 1]) {
                    matriz[i][j] = max(matriz[i - 1][j - 1] + 1, matriz[i - 1][j - 1]);
                }
                else {
                    matriz[i][j] = max(matriz[i - 1][j], matriz[i][j-1]);
                }
            }
        }
    }

    set<size_t> canciones;
    int i = ordenadas1.size();
    int j = ordenadas2.size();
    while (i > 0 && j > 0) {
        if (ordenadas1[i - 1] == ordenadas2[j - 1]) {
            canciones.insert(i - 1);
            i--;
            j--;
        }
        else if(matriz[i-1][j] > matriz[i][j-1]) {
            i -= 1;
        }
        else {
            j -= 1;
        }
    }

    return canciones;
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
    unordered_set<size_t> desordenadas1;
    unordered_set<size_t> desordenadas2;

    string aux; size_t aux_id = 0;
    istringstream iss1(line);
    while (iss1 >> aux) {
        if (!nombres_id.count(aux)) {
            id_nombres.push_back(aux);
            nombres_id[aux] = aux_id++;
        }
        linea1.push_back(nombres_id[aux]);
        desordenadas1.insert(nombres_id[aux]);
    }

    getline(cin, line);
    istringstream iss2(line);
    while (iss2 >> aux) {
        if (!nombres_id.count(aux)) {
            nombres_id[aux] = aux_id++;
        }
        linea2.push_back(nombres_id[aux]);
        desordenadas2.insert(nombres_id[aux]);
    }

    auto sol = resolver(linea1, linea2, desordenadas1, desordenadas2);

    //Escribir
    for (auto index : sol) {
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
