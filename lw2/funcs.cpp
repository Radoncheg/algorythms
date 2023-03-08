#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>

#include "TNode.h"
#include "TPlayer.h"
#include "TSensation.h"


// �������� ������� �������. ���������� ������ ������
TNode* create_table_of_tournament(int n)
{
    // �������� ����.
    TNode* node = new TNode;

    // ����� � �������.
    node->place = 1;
    // ������� ������.
    node->level = 0;
    // ��������� �� ����� � ������ ����� � ����������.
    node->left = nullptr;
    node->right = nullptr;
    node->winner = nullptr;

    // ���������� ������� ������ � ����������� �� ���������� �������.
    int h = (int)(log(n) / log(2.0));

    // ��������� �� ������ ������.
    TNode* root = node;

    // ���� �������� ���.
    bool flag_create_games = true;
    // ���� �������� ��������� ����.
    while (flag_create_games)
    {
        do
        {
            // ���������� ����� ����� ������.
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
                // ���������� ������ ����� ������.
                if (node->right == nullptr)
                {
                    node->right = new TNode;
                    node->right->winner = node;
                    node = node->right;

                    node->left = nullptr;
                    node->right = nullptr;

                    node->level = node->winner->level + 1;
                    node->place = (int(pow(2.0, node->level))) / 2 + node->winner->place;



                    // ���� ��������� ��� ������, �� ������������� ���� ��� ����������.
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

    // ���������� ��������� �� ������ ������.
    return root;
}


// �������� ������� ��������. ���������� ������ ��������
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

// ��������������� ������������� ������� � ������� �������.
void random_shuffle(TPlayer* players, int n)
{
    srand((unsigned)time(nullptr));

    for (int i = 0; i < n; ++i)
        std::swap(players[i], players[std::rand() % n]);
}



// ����������� ����� ����� ������.
void print_tree_level(TNode* node, TPlayer* players, int lvl)
{
    if (node != nullptr)
    {
        if (node->level == lvl - 1)
        {
            std::cout << "----------------------------------------------------------------\n"
                "----- [ ���� ] -----\n"
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

// ����� ����������.
void print_result(TNode* root, TPlayer* players, int n)
{
    int h = (int)(log(n) / log(2.0));
    std::cout << "������� ���������� ��� � ���������� �����������:\n";
    for (int i = h; i > 0; i--)
        print_tree_level(root, players, i);

    std::cout << "----------------------------------------------------------------\n"
        "----- [ ���������� ] -----\n"
        "----------------------------------------------------------------\n";

    std::cout << "| " << std::setw(5) << root->place << " | "
        << std::setw(25) << players[root->place - 1].name << " | "
        << std::setw(10) << players[root->place - 1].score
        << "\n----------------------------------------------------------------\n";

    std::vector<TSensation> sensations;
    create_table_of_sensations(sensations, root, players, h);

    int max_diff_score = 0;
    int main_sensation_num = 0;
    std::cout << "\n�������� �������:\n"
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
            << "����� " << players[sensations[i].winner->place - 1].name
            << " (" << players[sensations[i].winner->place - 1].score << ") ������� ������ "
            << players[sensations[i].loser->place - 1].name
            << " (" << players[sensations[i].loser->place - 1].score << ")!\n"
            << "������� ��������: " << diff_score << std::endl;
    }

    std::cout << "----------------------------------------------------------------\n"
        "\n������� �������� �������:\n"
        "----------------------------------------------------------------\n"
        << '[' << (main_sensation_num + 1) << "] "
        << "����� " << players[sensations[main_sensation_num].winner->place - 1].name
        << " (" << players[sensations[main_sensation_num].winner->place - 1].score << ") ������� ������ "
        << players[sensations[main_sensation_num].loser->place - 1].name
        << " (" << players[sensations[main_sensation_num].loser->place - 1].score << ")!\n"
        << "������� ��������: " << max_diff_score
        << "\n----------------------------------------------------------------\n";
}

// ����������� ����� ������ � ��������� ����.
void print_node(std::string filler, TNode* node, TPlayer* players)
{
    // ���� ������� ���� ��������.
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

// ����������� ������������ ������ (�������� ����� ������).
void freemem_of_tree(TNode* node)
{
    if (node != nullptr)
    {
        freemem_of_tree(node->left);
        freemem_of_tree(node->right);

        delete node;
    }
}
