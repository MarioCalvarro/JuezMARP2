// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

//-1 indica desconexión
using res_t = int;

//Vamos a pasar los string a enteros positivos
using grafo_t = vector<vector<size_t>>;


//BFS para ver la distancia mínima para alcanzar todos los nodos
res_t resolver(const grafo_t& grafo)
{
    int res = 0;
    for (size_t v = 0; v < grafo.size(); ++v) {
        vector<bool> marcados = vector<bool>(grafo.size(), false); marcados[v] = true;

        queue<size_t> cola;
        cola.push(v);
        marcados[v] = true;
        size_t num_visitados = 1;
        vector<int> distancias (grafo.size(), 0);
        while(!cola.empty()) {
            size_t curr = cola.front();
            cola.pop();

            for (size_t w : grafo[curr]) {
                if (!marcados[w]) {
                    distancias[w] = distancias[curr] + 1;
                    res = max(distancias[w], res);

                    cola.push(w);
                    marcados[w] = true;
                    num_visitados++;
                }
            }
        }

        if (num_visitados != grafo.size()) {
            return -1;
        }
    }

    return res; 
}

bool resuelveCaso() 
{
    //Leer
    size_t personas, relaciones;
    size_t siguiente_id = 0;
    cin >> personas >> relaciones;

    if (!cin)
        return false;

    grafo_t grafo = grafo_t(personas, vector<size_t>());
    unordered_map<string, size_t> string_to_int = unordered_map<string, size_t>();
    string aux1, aux2;
    for (size_t i = 0; i < relaciones; ++i) {
        cin >> aux1 >> aux2;

        //Si no había aparecido todavía → lo añadimos
        if (!string_to_int.count(aux1)) {
            string_to_int[aux1] = siguiente_id++;
        }
        if (!string_to_int.count(aux2)) {
            string_to_int[aux2] = siguiente_id++;
        }

        grafo[string_to_int[aux1]].push_back(string_to_int[aux2]);
        grafo[string_to_int[aux2]].push_back(string_to_int[aux1]);
    }

    res_t sol = resolver(grafo);

    //Escribir
    if (sol == -1) {
        cout << "DESCONECTADA\n";
    }
    else{
        cout << sol << '\n';
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
