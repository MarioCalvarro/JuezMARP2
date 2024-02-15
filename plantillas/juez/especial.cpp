// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>

tSol resolver(tDatos datos) 
{

}

bool resuelveCaso() 
{
    //Leer

    if (caso especial)
        return false;

    tSol sol = resolver(datos);

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
