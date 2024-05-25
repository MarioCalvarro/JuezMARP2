// DG, Mario Calvarro Marines

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

using res_t = int;

//First: duracion, Second: puntuacion
using cancion = pair<int, int>;

bool operator<(const cancion& lhs, const cancion& rhs) {
    return float(lhs.second) / lhs.first > float(rhs.second) / rhs.first;
}

int estimacion(const vector<cancion> &v, int d, int t1, int t2, int k, int val) {
    int n = v.size();
	int r = 2 * d - t1 - t2;
	int i = k + 1;

	while (i < n && v[i].first <= r) {
		r -= v[i].first;
		val += v[i].second;
		i++;
	}

	if (i < n) {
		val += (r * v[i].second) / v[i].first;
	}

	return val;
}

void resolver(const vector<cancion> &v, int d, int t1, int t2, int k, int val, int &maximo) {
    int n = v.size();
	maximo = max(maximo, val);

	if (k < n) {
		val += v[k].second;
		t1 += v[k].first;
		if (t1 <= d) {
			resolver(v, d, t1, t2, k + 1, val, maximo);
		}
		t1 -= v[k].first;
	
		t2 += v[k].first;
		if (t2 <= d) {
			resolver(v, d, t1, t2, k + 1, val, maximo);
		}
		t2 -= v[k].first;
		val -= v[k].second;

		if (estimacion(v, d, t1, t2, k, val) > maximo) {
			resolver(v, d, t1, t2, k + 1, val, maximo);
		}
	}
}

bool resuelveCaso() 
{
    //Leer
    int n, d;
    cin >> n;

    if (n == 0)
        return false;

    cin >> d;
    vector<cancion> canciones(n);
    for (auto &c : canciones) {
        cin >> c.first >> c.second;
    }

    int maximo = 0;
	sort(canciones.begin(), canciones.end());
	resolver(canciones, d, 0, 0, 0, 0, maximo);

    //Escribir
    cout << maximo << '\n';

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
