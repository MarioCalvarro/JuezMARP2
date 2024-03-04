// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>

using namespace std;

using res_t = int;

res_t resolver() 
{
    return 0;
}

bool resuelveCaso() 
{
    //Leer

    if (/* caso especial */)
        return false;

    res_t sol = resolver();

    //Escribir

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
