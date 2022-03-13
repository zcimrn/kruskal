#include <fstream>

int main(int argc, char* argv[]) {
    int max_node_count = 5, max_edge_length = 10;
    if (argc > 1 && atoi(argv[1]) > 0) {
        max_node_count = atoi(argv[1]);
    }
    if (argc > 2 && atoi(argv[2]) > 0) {
        max_edge_length = atoi(argv[2]);
    }
    std::ofstream out("input.txt");
    srand(time(0));
    out << max_node_count << std::endl;
    for (int i = 0; i < max_node_count; i++) {
        for (int j = 0; j < max_node_count; j++) {
            out << (i == j ? 0 : rand() % max_edge_length + 1) << ' ';
        }
        out << std::endl;
    }
    out.close();
    return 0;
}
