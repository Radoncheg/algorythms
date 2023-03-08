/*
 ������� ��������� ���� ������� � ��������� �������� �����. 
 ������������� ���� ����� ���������� ������� ���������� � ������� ����������.
*/
#include <fstream>

#include "merge_sort.h"


int main()
{    
    // ��������� ��������� � ������� Windows ��� ����������� ������ ���������.
    system("chcp 1251 > nul");

    // ���� � �������� �����.
    const std::string input_filename = "data.txt";
    // ���� � ��������� �����.
    const std::string output_filename = "data_sorted.txt";

    // �������� �������� �����.
    std::ifstream fin(input_filename, std::ios::in);

    // ������ �������.
    std::vector<TRecord> records;

    // ���� ������ �������� �����, �� ��������� ���������.
    if (!fin)
    {
        std::cerr << "������ �������� ����� " << input_filename << ".\n";
        
        // �������� ������� ������� ����� ����������� ������ ���������.
        system("pause");

        return 1;
    }
       


    // ���� �� ����� ����� ��������� ������ � �������.
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

    // �������� �������� �����.
    fin.close(); 

    // ���������� ������� ��������.
    merge_sort(records, 0, records.size() - 1);


    std::cout << "���������� ���������� ����� ������ �������: "
        << input_filename << " -> " << output_filename << ".\n";

    // �������� ��������� �����.
    std::ofstream fout(output_filename, std::ios::out);

    // ���� ������ �������� �����, �� ��������� ���������.
    if (!fout)
    {
        std::cerr << "������ �������� ����� " << output_filename << ".\n";

        // �������� ������� ������� ����� ����������� ������ ���������.
        system("pause");

        return 2;
    }

    // ����� ��������������� �������� ������� � �������� ����.
    for (int i = 0; i < records.size(); i++)
    {
        fout << records[i].index << std::endl
            << records[i].field << std::endl;
    }

    // �������� ��������� �����.
    fout.close();

    // �������� ������� ������� ����� ����������� ������ ���������.
    system("pause");

    return 0;
}
