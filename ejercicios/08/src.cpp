// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using res_t = size_t;

using matriz_t = vector<vector<size_t>>;

res_t resolver(const vector<size_t>& cubos)
{
    size_t n = cubos.size();
    //Tabla(i, j) : maximo que puede comer considerando los cubos desde i hasta j
    matriz_t tabla = matriz_t(n + 2, vector<size_t>(n + 2, 0));
        //Dejamos un borde alrededor vacío para evitar RTE

    //Casos base
    for (size_t i = 1; i <= n; ++i) {
        tabla[i][i] = cubos[i-1];
    }

    for (size_t d = 1; d < n; ++d) {
        for (size_t p = d + 1; p <= n; ++p) {
            size_t r = p - d, c = p;
            size_t ini = r - 1, fin = c - 1;        //Para tener en cuenta que
                                                    //hemos añadido una fila y
                                                    //columna vacías
            if (cubos[ini + 1] >= cubos[fin] && cubos[ini] >= cubos[fin - 1]) {
                tabla[r][c] = max(tabla[r+2][c] + cubos[ini], tabla[r+1][c-1] + cubos[fin]);
            }
            else if (cubos[ini + 1] >= cubos[fin] && cubos[ini] < cubos[fin - 1]) {
                tabla[r][c] = max(tabla[r+2][c] + cubos[ini], tabla[r][c-2] + cubos[fin]);
            }
            else if (cubos[ini + 1] < cubos[fin] && cubos[ini] >= cubos[fin - 1]) {
                tabla[r][c] = max(tabla[r+1][p-1] + cubos[ini], tabla[r+1][c-1] + cubos[fin]);
            }
            else {
                tabla[r][c] = max(tabla[r+1][p-1] + cubos[ini], tabla[r][c-2] + cubos[fin]);
            }
        }
    }

    return tabla[1][n];
}

bool resuelveCaso() 
{
    //Leer
    size_t num_cubos;
    cin >> num_cubos;

    if (num_cubos == 0)
        return false;

    vector<size_t> cubos = vector<size_t>(num_cubos);

    for (size_t i = 0; i < num_cubos; ++i) {
        cin >> cubos[i];
    }

    res_t sol = resolver(cubos);

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
