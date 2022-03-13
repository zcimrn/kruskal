#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

class DSU {
private:
    std::vector<int> parent, rank;
    int size = 0;

    int find_set_rec(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find_set_rec(parent[x]);
    }

public:
    DSU(int size_) {
        size = size_;
        parent.resize(size, -1);
        rank.resize(size);
    }

    void make_set(int x) {
        assert(x >= 0 && x < size);
        parent[x] = x;
        rank[x] = 0;
    }

    int find_set(int x) {
        assert(x >= 0 && x < size);
        if (parent[x] == -1) {
            make_set(x);
        }
        return find_set_rec(x);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a == b) {
            return;
        }
        if (rank[a] < rank[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        if (rank[a] == rank[b]) {
            rank[a]++;
        }
    }
};

struct Edge {
    int a, b, l;

    Edge(int a = -1, int b = -1, int l = 0) : a{a}, b{b}, l{l} {}
};

std::vector<Edge> read_edges(std::istream& in, int node_count) {
    std::vector<Edge> edges;
    std::string s;
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            in >> s;
            if (s != "~" && i != j) {
                edges.push_back({i, j, stoi(s)});
            }
        }
    }
    return std::move(edges);
}

bool edges_cmp(const Edge& e1, const Edge& e2) {
    return e1.l < e2.l || e1.l == e2.l && e1.a < e2.a || e1.l == e2.l && e1.a == e2.a && e1.b < e2.b;
}

std::vector<Edge> kruskal(std::vector<Edge>& edges, int node_count) {
    std::sort(edges.begin(), edges.end(), edges_cmp);
    std::vector<Edge> mst_edges;
    DSU dsu(node_count);
    for (const auto& edge : edges) {
        int a = dsu.find_set(edge.a), b = dsu.find_set(edge.b);
        if (a != b) {
            mst_edges.push_back(edge);
            dsu.union_sets(a, b);
        }
    }
    return std::move(mst_edges);
}

void write_answer(std::ostream& out, const std::vector<Edge>& edges) {
    int answer = 0;
    for (const auto& edge : edges) {
        answer += edge.l;
    }
    out << answer << std::endl;
    for (const auto& edge : edges) {
        out << edge.a + 1 << ' ' << edge.b + 1 << std::endl;
    }
}

int main() {
    int clocks = clock();

    std::ifstream in("input.txt");
    int node_count;
    in >> node_count;
    auto edges = read_edges(in, node_count);
    in.close();

    auto mst_edges = kruskal(edges, node_count);

    std::ofstream out("output.txt");
    write_answer(out, mst_edges);
    out.close();

    clocks = clock() - clocks;
    std::cerr.setf(std::ios::fixed, std::ios::floatfield);
    std::cerr.precision(8);
    std::cerr << static_cast<long double>(clocks) / CLOCKS_PER_SEC << std::endl;

    return 0;
}
