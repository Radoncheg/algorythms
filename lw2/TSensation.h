#pragma once

// ��������� �������� �� ������� (����� ����� � ������� ��������� �������).
struct TSensation
{
    // ��������� �� ��������� ����������� ������.
    struct TNode* winner = nullptr;
    // ��������� �� ��������� ������������ ������.
    struct TNode* loser = nullptr;
};
