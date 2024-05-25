// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>

using namespace std;

using res_t = int;

res_t resolver() 
{
    return 0;
}

void resuelveCaso() 
{
    //Leer

    res_t sol = resolver();

    //Escribir
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    size_t numCasos;
    std::cin >> numCasos;
    for (size_t i = 0; i < numCasos; ++i) 
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
