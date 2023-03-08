#include "merge_sort.h"


/// <summary>
/// ����������� ���������� ��������.
/// </summary>
/// <param name="records">������ �������.</param>
/// <param name="left">����� ������� �������.</param>
/// <param name="right">������ ������� �������.</param>
void merge_sort(std::vector<TRecord>& records, size_t left, size_t right)
{
    //! ������� ������ �� ��������.
    if (left >= right)
        return;

    // �������� ������� (��������� ������ ��������).
    size_t middle = left + (right - left) / 2;

    // ����������� ���������� ���������� ��������.
    merge_sort(records, left, middle);
    merge_sort(records, middle + 1, right);
    merge_sorting(records, left, right, middle);
}


/// <summary>
/// ��������������� ������� ��� ���������� ��������.
/// </summary>
/// <param name="records">������ �������.</param>
/// <param name="left">����� ������� �������.</param>
/// <param name="right">������ ������� �������.</param>
/// <param name="middle">��������� ������ ��������.</param>
void merge_sorting(std::vector<TRecord>& records, size_t left, size_t right, size_t middle)
{
    if (left >= right || middle < left || middle > right)
        return;

    if (right == left + 1 && records[left].index > records[right].index)
    {
        std::swap(records[left], records[right]);

        return;
    }

    std::vector<TRecord> tmp(&records[left], &records[right] + 1);

    for (size_t i = left, j = 0, k = middle - left + 1; i <= right; ++i)
    {
        if (j > middle - left)
            records[i] = tmp[k++];
        else if (k > right - left)
            records[i] = tmp[j++];
        else
            records[i] = (tmp[j].index < tmp[k].index) ? tmp[j++] : tmp[k++];
    }
}
