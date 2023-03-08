#pragma once

// —труктура —енсации на турнире (когда игрок с меньшим рейтингом победил).
struct TSensation
{
    // ”казатель на структуру победившего игрока.
    struct TNode* winner = nullptr;
    // ”казатель на структуру проигравшего игрока.
    struct TNode* loser = nullptr;
};
