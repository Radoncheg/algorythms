#pragma once

// Структура Узла дерева.
struct TNode
{
    // Место.
    int place = 0;
    // Уровень.
    int level = 0;

    // Указатель на структуру левого узла дерева. 
    struct TNode* left = nullptr;
    // Указатель на структуру правого узла дерева.
    struct TNode* right = nullptr;
    // Указатель на структуру узла дерева с победителем (прошедшем в следующую игру игроком).
    struct TNode* winner = nullptr;
};
