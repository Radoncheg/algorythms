#pragma once

// ��������� ���� ������.
struct TNode
{
    // �����.
    int place = 0;
    // �������.
    int level = 0;

    // ��������� �� ��������� ������ ���� ������. 
    struct TNode* left = nullptr;
    // ��������� �� ��������� ������� ���� ������.
    struct TNode* right = nullptr;
    // ��������� �� ��������� ���� ������ � ����������� (��������� � ��������� ���� �������).
    struct TNode* winner = nullptr;
};
