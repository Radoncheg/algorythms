/*
 Имеется текстовый файл записей с некоторым ключевым полем. 
 Отсортировать файл путем совмещения методов внутренней и внешней сортировок.
*/
#include <fstream>

#include "merge_sort.h"


int main()
{    
    // Установка кодировки в консоли Windows для корректного вывода кириллицы.
    system("chcp 1251 > nul");

    // Путь к входному файлу.
    const std::string input_filename = "data.txt";
    // Путь к выходному файлу.
    const std::string output_filename = "data_sorted.txt";

    // Открытие входного файла.
    std::ifstream fin(input_filename, std::ios::in);

    // Вектор записей.
    std::vector<TRecord> records;

    // Если ошибка открытия файла, то завершаем программу.
    if (!fin)
    {
        std::cerr << "Ошибка открытия файла " << input_filename << ".\n";
        
        // Ожидание нажатия клавиши перед завершением работы программы.
        system("pause");

        return 1;
    }
       


    // Пока не конец файла считываем записи в векторы.
    while (!fin.eof())
    {
        int buf_index = 0;
        std::string buf_field = "";

        fin >> buf_index;

        if (buf_index == 0)
            continue;

        fin >> buf_field;
        if (buf_field == "")
            continue;

        TRecord buf_record = { buf_index, buf_field };        

        records.push_back(buf_record);
    }

    // Закрытие входного файла.
    fin.close(); 

    // Сортировка записей слиянием.
    merge_sort(records, 0, records.size() - 1);


    std::cout << "Сортировка текстового файла прошла успешно: "
        << input_filename << " -> " << output_filename << ".\n";

    // Открытие выходного файла.
    std::ofstream fout(output_filename, std::ios::out);

    // Если ошибка открытия файла, то завершаем программу.
    if (!fout)
    {
        std::cerr << "Ошибка открытия файла " << output_filename << ".\n";

        // Ожидание нажатия клавиши перед завершением работы программы.
        system("pause");

        return 2;
    }

    // Вывод отсортированных векторов записей в выходной файл.
    for (int i = 0; i < records.size(); i++)
    {
        fout << records[i].index << std::endl
            << records[i].field << std::endl;
    }

    // Закрытие выходного файла.
    fout.close();

    // Ожидание нажатия клавиши перед завершением работы программы.
    system("pause");

    return 0;
}
