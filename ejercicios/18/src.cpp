//DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int k, snow, optimistic;
    vector<bool> assigned;
};

bool operator<(const Node& l, const Node& r) {
    return l.optimistic < r.optimistic;
}

vector<int> Matrix;
vector<int> carros;
vector<int> caminos;
int N, M;

vector<int> lower_bound_lookup;
vector<int> upper_bound_lookup;

void fill_lower_bound_lookup() {
    lower_bound_lookup.resize(N);
    int row_min = 10001;
    
    for (int j = 0; j < M; ++j)
        row_min = min(row_min, Matrix[M*(N-1) + j]);
    lower_bound_lookup[N - 1] = row_min;

    for (int i = N-2; 0 <= i; i--) {
        row_min = 10001;
        for (int j = 0; j < M; ++j)
            row_min = min(row_min, Matrix[i*M + j]);
        lower_bound_lookup[i] = row_min + lower_bound_lookup[i + 1];
    }
    
}

void fill_upper_bound_lookup() {
    upper_bound_lookup.resize(N);
    int row_max = 0;

    for (int j = 0; j < M; ++j)
        row_max = max(row_max, Matrix[M*(N-1) + j]);
    upper_bound_lookup[N - 1] = row_max;

    for (int i = N-2; 0 <= i; i--) {
        row_max = 0;
        for (int j = 0; j < M; ++j)
            row_max = max(row_max, Matrix[i*M + j]);
        upper_bound_lookup[i] = row_max + upper_bound_lookup[i + 1];
    }
    
}

int lower_bound(Node x) {
    return x.snow + lower_bound_lookup[x.k];
}

int upper_bound(Node x) {
    return x.snow + upper_bound_lookup[x.k];
}

bool is_solution(Node x) {
    return x.k == N;
}

int branch_bound() {
    Node y = {0, 0, 0, vector<bool>(M)}; // root
    int maxSnow = lower_bound(y);
    priority_queue<Node> queue;
    queue.push(y);

    while (not queue.empty() and upper_bound(queue.top()) >= maxSnow) {
        y = queue.top(); queue.pop();

        for (int i = 0; i < M; ++i) {
            if (not y.assigned[i] and carros[y.k] <= caminos[i]) {
                Node x = {y.k + 1, y.snow + Matrix[y.k * M + i], 0, y.assigned};
                x.optimistic = upper_bound(x);
                x.assigned[i] = true;

                if (is_solution(x)) {
                    if (maxSnow < x.snow) {
                        maxSnow = x.snow;
                    }
                } else {
                    if (maxSnow <= x.optimistic) {
                        queue.push(x);

                        if (maxSnow < lower_bound(x)) {
                            maxSnow = lower_bound(x);
                        }
                    }
                }
            }
        }
    }

    return maxSnow;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int a;
    cin >> a;
    for (int i = 0; i < a; i++) {
        cin >> N >> M;
        carros.resize(N);
        for (auto& a : carros) cin >> a;
        caminos.resize(M);
        for (auto& a : caminos) cin >> a;
        Matrix.resize(N*M);
        for (auto &c : Matrix) cin >> c;

        fill_lower_bound_lookup();
        fill_upper_bound_lookup();


        cout << branch_bound() << '\n';
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
