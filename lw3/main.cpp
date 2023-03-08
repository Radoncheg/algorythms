/*
 18.Реализовать алгоритм поиска кратчайших путей Дейкстры и
проиллюстрировать по шагам этапы его выполнения (10)
 Ошаев Олег CiLion
 */
#include <fstream>
#include "funcs.h"

int main()
{
    // Установка кодировки в консоли Windows для корректного вывода кириллицы.
    system("chcp 1251 > nul");

    // Путь к входному файлу с названиями городов.
    const std::string input_filename_cities = "data_cities.txt";

    // Открытие входного файла с названиями городов.
    std::ifstream fin_cities(input_filename_cities, std::ios::in);

    // Если ошибка открытия файла, то завершаем программу.
    if (!fin_cities)
    {
        std::cerr << "Ошибка открытия файла " << input_filename_cities << ".\n";

        // Ожидание нажатия клавиши перед завершением работы программы.
        system("pause");

        return 1;
    }

    // Количество вершин (городов).
    int cnt_vertexes;
    fin_cities >> cnt_vertexes;

    std::string* names = new std::string[cnt_vertexes];

    // Чтение названий городов.
    for (int i = 0; i < cnt_vertexes; i++)
        fin_cities >> names[i];

    // Закрытие входного файла с названиями городов.
    fin_cities.close();


    // Путь к входному файлу с матрицей смежности графа.
    const std::string input_filename_matr = "data_matr.txt";

    // Открытие входного файла с матрицей смежности графа.
    std::ifstream fin_matr(input_filename_matr, std::ios::in);

    // Если ошибка открытия файла, то завершаем программу.
    if (!fin_matr)
    {
        std::cerr << "Ошибка открытия файла " << input_filename_matr << ".\n";

        // Ожидание нажатия клавиши перед завершением работы программы.
        system("pause");

        return 1;
    }
       
    // Создание двумерного динамического массива.
    int** matr_graph = new int*[cnt_vertexes];
    for (int i = 0; i < cnt_vertexes; i++)
        matr_graph[i] = new int[cnt_vertexes];

    for (int i = 0; i < cnt_vertexes; i++)
        for (int j = 0; j < cnt_vertexes; j++)
            fin_matr >> matr_graph[i][j];

    // Закрытие входного файла с матрицей смежности графа.
    fin_matr.close();
    
    dijkstra_shortest_paths(matr_graph, 0, names, cnt_vertexes);

    // Очистка памяти.
    delete[] names;
    for (int i = 0; i < cnt_vertexes; i++)
        delete[] matr_graph[i];
    delete[] matr_graph;

    // Ожидание нажатия клавиши перед завершением работы программы.
    system("pause");

    return 0;
}
