#include <iostream>
#include <iomanip>

// �������� ����������� ���������� �� ������� ����������.
int get_min_distance(int* dist, bool* vertexes, int cnt_vertexes)
{
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < cnt_vertexes; v++)
        if (vertexes[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// ����� ����������.
void print_result(int** matr_graph, int* dist, std::string* names, int cnt_vertexes)
{
    std::cout << "������� ����������:\n" << std::setw(20) << ' ';
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

    std::cout << "\n������� ���������� ����� �� " << names[0] << " �� �������:\n";
    std::cout << std::setw(25) << "�������� ������"
        << std::setw(35) << "����������� ����\n";
    for (int i = 0; i < cnt_vertexes; i++)
    {
        std::cout << std::setw(25) << names[i];

        if (dist[i] == INT_MAX)
            std::cout << std::setw(35) << "�";
        else
            std::cout << std::setw(35) << dist[i] << std::endl;
    }

    // ��������� ������ ��� ������� ����.
    int* path = new int[cnt_vertexes * cnt_vertexes];

    std::cout << "\n����������� ����:\n";
    // ������ ��������� �������, �� ������� ����� �������������� ����.
    int begin_vertex_index = 0;
    // ����� ������ (�������� ������� �� ������� ����� �������������� ����).
    for (int j = 0; j < cnt_vertexes; j++)
    {
        // ������� �������� �������.
        int end_vertex_index = j;

        if (dist[end_vertex_index] == INT_MAX)
        {
            std::cout << "�\n";
            continue;
        }

        // ���������� ������� ����.
        for (int i = 1; i < cnt_vertexes * cnt_vertexes; i++)
            path[i] = INT_MAX;

        // ��������� ������� ���� � ������� �������� �������.
        path[0] = end_vertex_index;

        // ������ ���������� �������.
        int k = 1;
        // ��� �������� �������.
        int w = dist[end_vertex_index];

        // ����� ���� ������.
        while (end_vertex_index != begin_vertex_index)
            for (int i = 0; i < cnt_vertexes; i++)
            {
                // ���� ���������� ����� ����� ���������.
                if (matr_graph[i][end_vertex_index] != 0)
                {
                    // ��� ���� �� ����������.
                    int temp = w - matr_graph[i][end_vertex_index];
                    // ���� ��� ������ � ������������, �� ������� ��� ���������� �� ���� �������.
                    if (temp == dist[i])
                    {
                        // ����� ��� �������.
                        w = temp;
                        // ����� ���������� �������.
                        end_vertex_index = i;
                        // ������ � ������ ����.
                        path[k++] = i;
                    }
                }
            }

        // ����� ���������� ����� � ������� ����.
        for (int i = cnt_vertexes * cnt_vertexes - 1; i > 0; i--)
            if (path[i] != INT_MAX)
                std::cout << names[path[i]] << "-> ";
        std::cout << names[path[0]] << std::endl;
    }

    delete[] path;
}

// ���������� ����������� ����� � ������� ��������� ��������.
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
