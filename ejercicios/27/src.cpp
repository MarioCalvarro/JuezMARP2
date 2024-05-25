// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int resolver(const vector<int>& km, const vector<int>& beneficio, int separacion)
{
    int n = km.size();

    vector<int> anterior_pos(n, -1);
    int anterior_descanso_pos = -1;
    for (int descanso_act = 1; descanso_act < n; descanso_act++) {
        while ((km[descanso_act] - km[anterior_descanso_pos + 1]) >= separacion) {
            anterior_descanso_pos++;
        }
        anterior_pos[descanso_act] = anterior_descanso_pos;
    }

    vector<int> max_beneficios(n+1);
    max_beneficios[0] = 0;
    for (int i = 0; i < n; ++i) {
        max_beneficios[i+1] = max(max_beneficios[anterior_pos[i] + 1] + beneficio[i], max_beneficios[i]);
    }

    return max_beneficios[n];
}

bool resuelveCaso() 
{
    //Leer
    int N, separacion;
    cin >> N >> separacion;

    if (!std::cin)
        return false;

    vector<int> km(N);
    for (int i = 0; i < N; i++) {
        cin >> km[i];
    }

    vector<int> beneficio(N);
    for (int i = 0; i < N; i++) {
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
