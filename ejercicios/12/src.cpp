// DG, Mario Calvarro Marines

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

#define MIN_DIA 1450 //24*60 + 10

using namespace std;

//Inicio, duración
using datos_t = pair<size_t, size_t>;

using res_t = size_t;

res_t resolver(const vector<datos_t> &peliculas) 
{
    size_t N = peliculas.size();
    vector<size_t> V (MIN_DIA + 1, 0);

    for (size_t i = 0; i < N; i++) {
        for (size_t j = MIN_DIA; j > 0; j--) {
            if (j >= peliculas[i].first + peliculas[i].second + 10) {
                V[j] = max(V[j], V[peliculas[i].first] + peliculas[i].second);
            }
        }
    }

    return V[MIN_DIA];
}

bool resuelveCaso() 
{
    //Leer
    size_t N;
    cin >> N;

    if (N == 0)
        return false;

    char aux; size_t horas, mins, dur;
    vector<datos_t> peliculas(N);
    for (auto &p : peliculas) {
        cin >> horas >> aux >> mins >> dur;
        p = { horas * 60 + mins, dur };
    }
    sort(peliculas.begin(), peliculas.end());

    res_t sol = resolver(peliculas);

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
