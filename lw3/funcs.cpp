#include <iostream>
#include <iomanip>

// Получить минимальное расстояние из массива расстояний.
int get_min_distance(int* dist, bool* vertexes, int cnt_vertexes)
{
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < cnt_vertexes; v++)
        if (vertexes[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Вывод результата.
void print_result(int** matr_graph, int* dist, std::string* names, int cnt_vertexes)
{
    std::cout << "Матрица расстояний:\n" << std::setw(20) << ' ';
    for (int i = 0; i < cnt_vertexes; i++)
        std::cout << std::setw(20) << names[i];

    std::cout << std::endl;

    for (int i = 0; i < cnt_vertexes; i++)
    {
        std::cout << std::setw(20) << names[i];
        for (int j = 0; j < cnt_vertexes; j++)
            std::cout << std::setw(20) << matr_graph[i][j];

        std::cout << std::endl;
    }       

    std::cout << "\nТаблица кратчайших путей из " << names[0] << " до городов:\n";
    std::cout << std::setw(25) << "Название города"
        << std::setw(35) << "Минимальный путь\n";
    for (int i = 0; i < cnt_vertexes; i++)
    {
        std::cout << std::setw(25) << names[i];

        if (dist[i] == INT_MAX)
            std::cout << std::setw(35) << "—";
        else
            std::cout << std::setw(35) << dist[i] << std::endl;
    }

    // Выделение памяти для массива пути.
    int* path = new int[cnt_vertexes * cnt_vertexes];

    std::cout << "\nМинимальные пути:\n";
    // Индекс начальной вершины, из которой будут рассчитываться пути.
    int begin_vertex_index = 0;
    // Обход вершин (конечные вершины до которых будут рассчитываться пути).
    for (int j = 0; j < cnt_vertexes; j++)
    {
        // Текущая конечная вершина.
        int end_vertex_index = j;

        if (dist[end_vertex_index] == INT_MAX)
        {
            std::cout << "–\n";
            continue;
        }

        // Заполнение массива пути.
        for (int i = 1; i < cnt_vertexes * cnt_vertexes; i++)
            path[i] = INT_MAX;

        // Начальный элемент пути — текущая конечная вершина.
        path[0] = end_vertex_index;

        // Индекс предыдущей вершины.
        int k = 1;
        // Вес конечной вершины.
        int w = dist[end_vertex_index];

        // Обход всех вершин.
        while (end_vertex_index != begin_vertex_index)
            for (int i = 0; i < cnt_vertexes; i++)
            {
                // Если существует связь между вершинами.
                if (matr_graph[i][end_vertex_index] != 0)
                {
                    // Вес пути из предыдущей.
                    int temp = w - matr_graph[i][end_vertex_index];
                    // Если вес совпал с рассчитанным, то переход был осуществлён из этой вершины.
                    if (temp == dist[i])
                    {
                        // Новый вес вершины.
                        w = temp;
                        // Новая предыдущая вершина.
                        end_vertex_index = i;
                        // Запись в массив пути.
                        path[k++] = i;
                    }
                }
            }

        // Вывод полученных путей в удобном виде.
        for (int i = cnt_vertexes * cnt_vertexes - 1; i > 0; i--)
            if (path[i] != INT_MAX)
                std::cout << names[path[i]] << "-> ";
        std::cout << names[path[0]] << std::endl;
    }

    delete[] path;
}

// Нахождение минимальных путей с помощью алгоритма Дейкстры.
void dijkstra_shortest_paths(int** matr_graph, int src, std::string* names, int cnt_vertexes)
{
    int* dist = new int[cnt_vertexes];
    bool* vertexes = new bool[cnt_vertexes];

    for (int i = 0; i < cnt_vertexes; i++)
        dist[i] = INT_MAX, vertexes[i] = false;

    dist[src] = 0;

    for (int count = 0; count < cnt_vertexes; count++)
    {
        int u = get_min_distance(dist, vertexes, cnt_vertexes);
        vertexes[u] = true;
        for (int v = 0; v < cnt_vertexes; v++)
        {
            if (!vertexes[v] && matr_graph[u][v] && dist[u] != INT_MAX && (dist[u] + matr_graph[u][v] < dist[v]))
            {
                dist[v] = dist[u] + matr_graph[u][v];
            }
        }
    }
       
    print_result(matr_graph, dist, names, cnt_vertexes);

    delete[] vertexes;
    delete[] dist;
}
