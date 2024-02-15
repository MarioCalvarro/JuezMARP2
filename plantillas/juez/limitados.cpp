// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>

tSol resolver(tDatos datos) 
{

}

void resuelveCaso() 
{
    //Leer

    tSol sol = resolver(datos);

    //Escribir
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (size_t i = 0; i < numCasos; ++i) 
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
