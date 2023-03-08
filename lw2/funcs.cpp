#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

#include "TNode.h"
#include "TPlayer.h"
#include "TSensation.h"


// Создание таблицы турнира. Возвращает Корень дерева
TNode* create_table_of_tournament(int n)
{
    // Создание узла.
    TNode* node = new TNode;

    // Место в турнире.
    node->place = 1;
    // Уровень дерева.
    node->level = 0;
    // Указатели на левую и правую ветки и победителя.
    node->left = nullptr;
    node->right = nullptr;
    node->winner = nullptr;

    // Количество уровней дерева в зависимости от количества игроков.
    int h = (int)(log(n) / log(2.0));

    // Указатель на корень дерева.
    TNode* root = node;

    // Флаг создания игр.
    bool flag_create_games = true;
    // Пока возможно создавать игры.
    while (flag_create_games)
    {
        do
        {
            // Заполнение левой ветки дерева.
            if (node->left == nullptr)
            {
                node->left = new TNode;
                node->left->winner = node;
                node->left->place = node->place;
                node = node->left;

                node->left = nullptr;
                node->right = nullptr;

                node->level = node->winner->level + 1;
            }
            else
            {
                // Заполнение правой ветки дерева.
                if (node->right == nullptr)
                {
                    node->right = new TNode;
                    node->right->winner = node;
                    node = node->right;

                    node->left = nullptr;
                    node->right = nullptr;

                    node->level = node->winner->level + 1;
                    node->place = (int(pow(2.0, node->level))) / 2 + node->winner->place;



                    // Если добавлены все игроки, то устанавливаем флаг для завершения.
                    if (node->place == n)
                        flag_create_games = false;
                }
                else
                {
                    node = node->winner;
                }
            }

        } while (node->level != h);

        node = node->winner;
    }

    // Возвращаем указатель на корень дерева.
    return root;
}


// Создание таблицы сенсаций. Возвращает Вектор сенсаций
void create_table_of_sensations(std::vector<TSensation>& sensations, TNode* node, TPlayer* players, int lvl)
{
    if (node != nullptr)
    {

        if (node->level == lvl - 1)
        {
            if (players[node->left->place - 1].score < players[node->right->place - 1].score)
            {
                TSensation sensation;
                sensation.winner = node->left;
                sensation.loser = node->right;
                sensations.push_back(sensation);
            }

        }

        create_table_of_sensations(sensations, node->left, players, lvl);
        create_table_of_sensations(sensations, node->right, players, lvl);
    }
}

// Псевдослучайное перемешивание массива с данными игроков.
void random_shuffle(TPlayer* players, int n)
{
    srand((unsigned)time(nullptr));

    for (int i = 0; i < n; ++i)
        std::swap(players[i], players[std::rand() % n]);
}



// Рекурсивный вывод узлов дерева.
void print_tree_level(TNode* node, TPlayer* players, int lvl)
{
    if (node != nullptr)
    {
        if (node->level == lvl - 1)
        {
            std::cout << "----------------------------------------------------------------\n"
                "----- [ Игра ] -----\n"
                "----------------------------------------------------------------\n";
        }

        if (node->level == lvl)
        {
            std::cout << "| " << std::setw(5) << node->place << " | "
                << std::setw(25) << players[node->place - 1].name << " | "
                << std::setw(10) << players[node->place - 1].score
                << std::endl;
        }

        print_tree_level(node->left, players, lvl);
        print_tree_level(node->right, players, lvl);
    }
}

// Вывод результата.
void print_result(TNode* root, TPlayer* players, int n)
{
    int h = (int)(log(n) / log(2.0));
    std::cout << "Таблица проведённых игр с выявленным победителем:\n";
    for (int i = h; i > 0; i--)
        print_tree_level(root, players, i);

    std::cout << "----------------------------------------------------------------\n"
        "----- [ Победитель ] -----\n"
        "----------------------------------------------------------------\n";

    std::cout << "| " << std::setw(5) << root->place << " | "
        << std::setw(25) << players[root->place - 1].name << " | "
        << std::setw(10) << players[root->place - 1].score
        << "\n----------------------------------------------------------------\n";

    std::vector<TSensation> sensations;
    create_table_of_sensations(sensations, root, players, h);

    int max_diff_score = 0;
    int main_sensation_num = 0;
    std::cout << "\nСенсации турнира:\n"
        "----------------------------------------------------------------\n";
    for (unsigned int i = 0; i < sensations.size(); i++)
    {
        int diff_score = players[sensations[i].loser->place - 1].score -
            players[sensations[i].winner->place - 1].score;

        if (diff_score > max_diff_score)
        {
            max_diff_score = diff_score;
            main_sensation_num = i;
        }

        std::cout << '[' << (i + 1) << "] "
            << "Игрок " << players[sensations[i].winner->place - 1].name
            << " (" << players[sensations[i].winner->place - 1].score << ") победил игрока "
            << players[sensations[i].loser->place - 1].name
            << " (" << players[sensations[i].loser->place - 1].score << ")!\n"
            << "Разница рейтинга: " << diff_score << std::endl;
    }

    std::cout << "----------------------------------------------------------------\n"
        "\nГлавная сенсация турнира:\n"
        "----------------------------------------------------------------\n"
        << '[' << (main_sensation_num + 1) << "] "
        << "Игрок " << players[sensations[main_sensation_num].winner->place - 1].name
        << " (" << players[sensations[main_sensation_num].winner->place - 1].score << ") победил игрока "
        << players[sensations[main_sensation_num].loser->place - 1].name
        << " (" << players[sensations[main_sensation_num].loser->place - 1].score << ")!\n"
        << "Разница рейтинга: " << max_diff_score
        << "\n----------------------------------------------------------------\n";
}

// Рекурсивный вывод дерева с заданного узла.
void print_node(std::string filler, TNode* node, TPlayer* players)
{
    // Если текущий узел непустой.
    if (node != NULL)
    {
        print_node(filler + ("     "),
            node->left, players);

        std::cout << filler
            <<  ("|---*")
            << players[node->place - 1].name <<
            " /" << players[node->place - 1].score << "/\n";

        print_node(filler + ("     "),
            node->right, players);
    }
}

// Рекурсивное освобождение памяти (удаление узлов дерева).
void freemem_of_tree(TNode* node)
{
    if (node != nullptr)
    {
        freemem_of_tree(node->left);
        freemem_of_tree(node->right);

        delete node;
    }
}
