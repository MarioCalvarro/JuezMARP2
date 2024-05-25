// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using matriz_t = vector<vector<int>>;

int indice(const vector<int>& km, int k, int ini, int fin) {
    if (ini + 1 == fin) {
        return km[ini] <= k ? ini : 0;
    }
    if (ini + 2 == fin) {
        if (km[ini + 1] <= k) return ini + 1;
        else return indice(km, k, ini, fin - 1);
    }

    int m = (ini + fin - 1) / 2;
    if (km[m] <= k) {
        return indice(km, k, m, fin);
    }
    else {
        return indice(km, k, ini, m);
    }
}

int resolver(const vector<int>& km, const vector<int>& beneficio, int separacion)
{
    int n = km.size();
    vector<int> v(n);

    for (int i = 1; i < n; i++) {
        int index = (0 < km[i] - separacion) ? (indice(km, km[i] - separacion, 0, i)) : 0;
        v[i] = max(v[i], v[index] + beneficio[i]);

        for (int j = i + 1; j <= n; j++) {
            v[j] = v[i];
        }
    }

    return v[n];
}

bool resuelveCaso() 
{
    //Leer
    int N, separacion;
    cin >> N >> separacion;

    if (!std::cin)
        return false;

    vector<int> km(N + 1);
    for (int i = 1; i < N + 1; i++) {
        cin >> km[i];
    }

    vector<int> beneficio(N + 1);
    for (int i = 1; i < N + 1; i++) {
        cin >> beneficio[i];
    }

    //Escribir
    cout << resolver(km, beneficio, separacion) << '\n';

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
