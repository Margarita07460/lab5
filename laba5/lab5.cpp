#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale.h>

using namespace std;

// Функция для поиска изолированных вершин (матрицей смежности)
vector<int> findIsolatedVertices(const vector<vector<int>>& cmej_mat) {
    vector<int> isolated_vertices;
    for (int i = 1; i < cmej_mat.size(); ++i) {
        bool isolated = true;
        for (int j = 1; j < cmej_mat[i].size(); ++j) {
            if (cmej_mat[i][j] == 1) {
                isolated = false;
                break;
            }
        }
        if (isolated) {
            isolated_vertices.push_back(i);
        }
    }
    return isolated_vertices;
}

// Функция для поиска концевых вершин (работа с матрицей смежности)
vector<int> findLeafVertices(const vector<vector<int>>& cmej_mat) {
    vector<int> leaf_vertices;
    for (int i = 1; i < cmej_mat.size(); ++i) {
        int degree = 0;
        for (int j = 1; j < cmej_mat[i].size(); ++j) {
            if (cmej_mat[i][j] == 1) {
                degree++;
            }
        }
        if (degree == 1) {
            leaf_vertices.push_back(i);
        }
    }
    return leaf_vertices;
}

// Функция для поиска доминирующих вершин (работа с матрицей смежности)
vector<int> findDominatingVertices(const vector<vector<int>>& cmej_mat) {
    vector<int> dominating_vertices;
    for (int i = 1; i < cmej_mat.size(); ++i) {
        bool dominating = true;
        for (int j = 1; j < cmej_mat[i].size(); ++j) {
            if (i != j && cmej_mat[i][j] != 1) {
                dominating = false;
                break;
            }
        }
        if (dominating) {
            dominating_vertices.push_back(i);
        }
    }
    return dominating_vertices;
}

// Функция для создания и вывода матрицы инцидентности 
vector < vector < int>> createAndPrintIncidenceMatrix(const vector < vector < int>>& cmej_mat, int colich_reb) {
    vector < vector < int>> incidence_matrix(cmej_mat.size(), vector<int>(colich_reb, 0));
    int edge_idx = 0;
    for (int i = 1; i < cmej_mat.size(); ++i) {
        for (int j = i + 1; j < cmej_mat[i].size(); ++j) {
            if (cmej_mat[i][j] == 1) {
                incidence_matrix[i][edge_idx] = 1;
                incidence_matrix[j][edge_idx] = 1;
                edge_idx++;
            }
        }
    }

    printf("Матрица инцидентности:\n");
    for (int i = 1; i < incidence_matrix.size(); ++i) {
        for (int j = 0; j < colich_reb; ++j) {
            printf("%d ", incidence_matrix[i][j]);
        }
        printf("\n");
    }
    return incidence_matrix;
}

int getGraphSizeFromIncidenceMatrix(const vector < vector < int>>& incidence_matrix) {
    // Возвращает количество столбцов в матрице инцидентности, что является размером графа
    return incidence_matrix[0].size(); // предполагается, что матрица не пуста
}

void printIncidenceMatrixDimensions(int col_ver, int colich_reb) {
    printf("Размерность матрицы инцидентности: %d x %d\n", col_ver, colich_reb);
}

//Функция для поиска изолированных вершин на основе матрицы инцидентности
vector<int> findIsolatedVerticesIncidence(const vector < vector < int>>& incidence_matrix) {
    vector<int> isolated_vertices;
    for (int i = 0; i < incidence_matrix.size(); ++i) {
        bool isolated = true;
        for (int j = 0; j < incidence_matrix[i].size(); ++j) {
            if (incidence_matrix[i][j] != 0) {
                isolated = false;
                break;
            }
        }
        if (isolated) {
            isolated_vertices.push_back(i);
        }
    }
    return isolated_vertices;
}

//Функция для поиска концевых вершин на основе матрицы инцидентности
vector<int> findLeafVerticesIncidence(const vector < vector < int>>& incidence_matrix) {
    vector<int> leaf_vertices;
    for (int i = 1; i < incidence_matrix.size(); ++i) {
        int degree = 0;
        for (int j = 0; j < incidence_matrix[i].size(); ++j) {
            if (incidence_matrix[i][j] != 0) {
                degree++;
            }
        }
        if (degree == 1) {
            leaf_vertices.push_back(i);
        }
    }
    return leaf_vertices;
}

// Функция для поиска доминирующих вершин на основе матрицы инцидентности
vector<int> findDominatingVerticesIncidence(const vector < vector < int>>& incidence_matrix) {
    vector<int> dominating_vertices;
    int total_vertices = incidence_matrix.size();
    for (int i = 1; i < incidence_matrix.size(); ++i) {
        int edge_count = 0;
        for (int j = 1; j < incidence_matrix[i].size(); ++j) {
            if (incidence_matrix[i][j] != 1) {
                edge_count++;
            }
        }
        if (edge_count == total_vertices - 1) {
            dominating_vertices.push_back(i);
        }
    }
    return dominating_vertices;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int col_ver;
    
    

    printf("Введите количество вершин: ");
    scanf("%d", &col_ver);


    
    srand(time(NULL));
    vector<vector<int>> cmej_mat(col_ver + 1, vector<int>(col_ver + 1, 0));
    int colich_reb = 0;
    for (int i = 1; i <= col_ver; ++i) {
        for (int j = i + 1; j <= col_ver; ++j) {
            if (static_cast<double>(rand()) / RAND_MAX < 1) {
                
                cmej_mat[i][j] = 1;
                cmej_mat[j][i] = 1;
              colich_reb++;
            }
        }
    }

    printf("Матрица смежности:\n");
    for (int i = 1; i <= col_ver; ++i) {
        for (int j = 1; j <= col_ver; ++j) {
            printf("%d ", cmej_mat[i][j]);
        }
        printf("\n");
    }

    printf("Количество вершин: %d\n", col_ver);
    printf("Количество рёбер: %d\n", colich_reb);

    vector<int> isolated_vertices = findIsolatedVertices(cmej_mat);
    if (!isolated_vertices.empty()) {
        printf("Изолированные вершины (матрица смежности):");
        for (int i = 0; i < isolated_vertices.size(); ++i) {
            printf(" %d", isolated_vertices[i]);
        }
        printf("\n");
    }
    else {
        printf("Нет изолированных вершин (матрица смежности).\n");
    }

    vector<int> leaf_vertices = findLeafVertices(cmej_mat);
    if (!leaf_vertices.empty()) {
        printf("Концевые вершины (матрица смежности):");
        for (int i = 0; i < leaf_vertices.size(); ++i) {
            printf(" %d", leaf_vertices[i]);
        }
        printf("\n");
    }
    else {
        printf("Нет концевых вершин (матрица смежности).\n");
    }

    vector<int> dominating_vertices = findDominatingVertices(cmej_mat);
    if (!dominating_vertices.empty()) {
        printf("Доминирующие вершины (матрица смежности):");
        for (int i = 0; i < dominating_vertices.size(); ++i) {
            printf(" %d", dominating_vertices[i]);
        }
        printf("\n");
    }
    else {
        printf("Нет доминирующих вершин (матрица смежности).\n\n\n");
    }

    
    printIncidenceMatrixDimensions(col_ver, colich_reb);
    vector < vector < int>> incidence_matrix = createAndPrintIncidenceMatrix(cmej_mat, colich_reb);
    vector<int> isolated_vertices_incidence = findIsolatedVerticesIncidence(incidence_matrix);

    // Определение размера графа
    int graph_size = getGraphSizeFromIncidenceMatrix(incidence_matrix);
    printf("Размер графа: %d\n", graph_size);

    if (!isolated_vertices_incidence.empty()) {
        printf("Изолированные вершины (матрица инцидентности):");
        for (int vertex : isolated_vertices_incidence) {
            printf(" %d", vertex);
        }
        printf("\n");
    }
    else {
        printf("Нет изолированных вершин (матрица инцидентности).\n");
    }

    vector<int> leaf_vertices_incidence = findLeafVerticesIncidence(incidence_matrix);
    if (!leaf_vertices_incidence.empty()) {
        printf("Концевые вершины (матрица инцидентности):");
        for (int vertex : leaf_vertices_incidence) {
            printf(" %d", vertex);
        }
        printf("\n");
    }
    else {
        printf("Нет концевых вершин (матрица инцидентности).\n");
    }


    if (!dominating_vertices.empty()) {
        printf("Доминирующие вершины (матрица инцидентности):");
        for (int i = 0; i < dominating_vertices.size(); ++i) {
            printf(" %d", dominating_vertices[i]);
        }
        printf("\n");
    }
    else {
        printf("Нет доминирующих вершин (матрица инцидентности).\n\n\n");
    }


    return 0;
}

