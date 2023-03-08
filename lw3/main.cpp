/*
 18.����������� �������� ������ ���������� ����� �������� �
����������������� �� ����� ����� ��� ���������� (10)
 ����� ���� CiLion
 */
#include <fstream>
#include "funcs.h"

int main()
{
    // ��������� ��������� � ������� Windows ��� ����������� ������ ���������.
    system("chcp 1251 > nul");

    // ���� � �������� ����� � ���������� �������.
    const std::string input_filename_cities = "data_cities.txt";

    // �������� �������� ����� � ���������� �������.
    std::ifstream fin_cities(input_filename_cities, std::ios::in);

    // ���� ������ �������� �����, �� ��������� ���������.
    if (!fin_cities)
    {
        std::cerr << "������ �������� ����� " << input_filename_cities << ".\n";

        // �������� ������� ������� ����� ����������� ������ ���������.
        system("pause");

        return 1;
    }

    // ���������� ������ (�������).
    int cnt_vertexes;
    fin_cities >> cnt_vertexes;

    std::string* names = new std::string[cnt_vertexes];

    // ������ �������� �������.
    for (int i = 0; i < cnt_vertexes; i++)
        fin_cities >> names[i];

    // �������� �������� ����� � ���������� �������.
    fin_cities.close();


    // ���� � �������� ����� � �������� ��������� �����.
    const std::string input_filename_matr = "data_matr.txt";

    // �������� �������� ����� � �������� ��������� �����.
    std::ifstream fin_matr(input_filename_matr, std::ios::in);

    // ���� ������ �������� �����, �� ��������� ���������.
    if (!fin_matr)
    {
        std::cerr << "������ �������� ����� " << input_filename_matr << ".\n";

        // �������� ������� ������� ����� ����������� ������ ���������.
        system("pause");

        return 1;
    }
       
    // �������� ���������� ������������� �������.
    int** matr_graph = new int*[cnt_vertexes];
    for (int i = 0; i < cnt_vertexes; i++)
        matr_graph[i] = new int[cnt_vertexes];

    for (int i = 0; i < cnt_vertexes; i++)
        for (int j = 0; j < cnt_vertexes; j++)
            fin_matr >> matr_graph[i][j];

    // �������� �������� ����� � �������� ��������� �����.
    fin_matr.close();
    
    dijkstra_shortest_paths(matr_graph, 0, names, cnt_vertexes);

    // ������� ������.
    delete[] names;
    for (int i = 0; i < cnt_vertexes; i++)
        delete[] matr_graph[i];
    delete[] matr_graph;

    // �������� ������� ������� ����� ����������� ������ ���������.
    system("pause");

    return 0;
}
