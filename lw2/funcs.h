#pragma once

#include <vector>

#include "TNode.h"
#include "TPlayer.h"
#include "TSensation.h"


TNode* create_table_of_tournament(int);
void create_table_of_sensations(std::vector<TSensation>&, TNode*, TPlayer*, int);
void random_shuffle(TPlayer*, int);

void print_tree_level(TNode*, TPlayer*, int);
void print_node(std::string, TNode*, TPlayer*);
void print_result(TNode*, TPlayer*, int);
void freemem_of_tree(TNode*);
