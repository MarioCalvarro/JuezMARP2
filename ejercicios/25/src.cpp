// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

using res_t = int;

//First: grupos, Second: precio
using dato_t = pair<int, int>;

res_t resolver(const vector<dato_t> &c, int P)
{
    int n = c.size();
    vector<int> v(P + 1);

    for (int i = 0; i < n; i++) {
        for (int j = P; 0 <= j; j--) {
            if (c[i].second <= j) {
                v[j] = max(v[j], v[j - c[i].second] + c[i].first);
            }
        }
    }

    return v[P];
}

bool resuelveCaso() 
{
    //Leer
    size_t P, N;
    cin >> P >> N;

    if (!std::cin)
        return false;

    vector<dato_t> c(N);
    for (size_t i = 0; i < N; i++) {
        int g, p;
        cin >> g >> p;
        c[i] = {g, p};
    }

    res_t sol = resolver(c, P);

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
