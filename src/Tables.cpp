#include <vector>
#include <functional>
#include "Expr.h"

Rule none;
static Rule rules[] = {
    /*0*/ {Symbol::input, {Symbol::stmt_list, Symbol::SEMICOLON, }},
    /*1*/ {Symbol::stmt_list, {Symbol::stmt_list, Symbol::SEMICOLON, Symbol::stmt, }},
    /*2*/ {Symbol::stmt_list, {Symbol::stmt, }},
    /*3*/ {Symbol::stmt, {Symbol::ID, Symbol::ASSIGN, Symbol::expr, }},
    /*4*/ {Symbol::stmt, {Symbol::PRINT, Symbol::expr, }},
    /*5*/ {Symbol::expr, {Symbol::expr, Symbol::SUM, Symbol::term, }},
    /*6*/ {Symbol::expr, {Symbol::term, }},
    /*7*/ {Symbol::term, {Symbol::term, Symbol::MULT, Symbol::factor, }},
    /*8*/ {Symbol::term, {Symbol::factor, }},
    /*9*/ {Symbol::factor, {Symbol::ID, }},
    /*10*/ {Symbol::factor, {Symbol::NUMBER, }},
    /*11*/ {Symbol::factor, {Symbol::OPEN_PAREN, Symbol::expr, Symbol::CLOSE_PAREN, }},
};

inline PAction shift(int index) {
    return PAction(PActionType::Shift, index);
}

inline PAction reduce(int index) {
    return PAction(PActionType::Reduce, index);
}

inline PAction accept() {
    return PAction(PActionType::Accept, 0);
}

PAction empty;
static std::vector<std::vector<PAction>> action_table = {
    /* 0 */ { empty, empty, shift(2), empty, shift(1), empty, empty, empty, empty, empty, },
    /* 1 */ { empty, empty, shift(9), empty, empty, empty, empty, shift(6), shift(5), empty, },
    /* 2 */ { empty, empty, empty, shift(11), empty, empty, empty, empty, empty, empty, },
    /* 3 */ { empty, shift(12), empty, empty, empty, empty, empty, empty, empty, empty, },
    /* 4 */ { reduce(2), reduce(2), reduce(2), reduce(2), reduce(2), reduce(2), reduce(2), reduce(2), reduce(2), reduce(2), },
    /* 5 */ { empty, empty, shift(9), empty, empty, empty, empty, shift(6), shift(5), empty, },
    /* 6 */ { reduce(10), reduce(10), reduce(10), reduce(10), reduce(10), reduce(10), reduce(10), reduce(10), reduce(10), reduce(10), },
    /* 7 */ { reduce(8), reduce(8), reduce(8), reduce(8), reduce(8), reduce(8), reduce(8), reduce(8), reduce(8), reduce(8), },
    /* 8 */ { reduce(4), reduce(4), reduce(4), reduce(4), reduce(4), shift(14), reduce(4), reduce(4), reduce(4), reduce(4), },
    /* 9 */ { reduce(9), reduce(9), reduce(9), reduce(9), reduce(9), reduce(9), reduce(9), reduce(9), reduce(9), reduce(9), },
    /* 10 */ { reduce(6), reduce(6), reduce(6), reduce(6), reduce(6), reduce(6), shift(15), reduce(6), reduce(6), reduce(6), },
    /* 11 */ { empty, empty, shift(9), empty, empty, empty, empty, shift(6), shift(5), empty, },
    /* 12 */ { accept(), accept(), shift(2), accept(), shift(1), accept(), accept(), accept(), accept(), accept(), },
    /* 13 */ { empty, empty, empty, empty, empty, shift(14), empty, empty, empty, shift(18), },
    /* 14 */ { empty, empty, shift(9), empty, empty, empty, empty, shift(6), shift(5), empty, },
    /* 15 */ { empty, empty, shift(9), empty, empty, empty, empty, shift(6), shift(5), empty, },
    /* 16 */ { reduce(3), reduce(3), reduce(3), reduce(3), reduce(3), shift(14), reduce(3), reduce(3), reduce(3), reduce(3), },
    /* 17 */ { reduce(1), reduce(1), reduce(1), reduce(1), reduce(1), reduce(1), reduce(1), reduce(1), reduce(1), reduce(1), },
    /* 18 */ { reduce(11), reduce(11), reduce(11), reduce(11), reduce(11), reduce(11), reduce(11), reduce(11), reduce(11), reduce(11), },
    /* 19 */ { reduce(5), reduce(5), reduce(5), reduce(5), reduce(5), reduce(5), shift(15), reduce(5), reduce(5), reduce(5), },
    /* 20 */ { reduce(7), reduce(7), reduce(7), reduce(7), reduce(7), reduce(7), reduce(7), reduce(7), reduce(7), reduce(7), },
};

static std::vector<std::vector<int>> goto_table = {
    /* 0 */ { -1, 3, 4, -1, -1, -1, },
    /* 1 */ { -1, -1, -1, 8, 10, 7, },
    /* 2 */ { -1, -1, -1, -1, -1, -1, },
    /* 3 */ { -1, -1, -1, -1, -1, -1, },
    /* 4 */ { -1, -1, -1, -1, -1, -1, },
    /* 5 */ { -1, -1, -1, 13, 10, 7, },
    /* 6 */ { -1, -1, -1, -1, -1, -1, },
    /* 7 */ { -1, -1, -1, -1, -1, -1, },
    /* 8 */ { -1, -1, -1, -1, -1, -1, },
    /* 9 */ { -1, -1, -1, -1, -1, -1, },
    /* 10 */ { -1, -1, -1, -1, -1, -1, },
    /* 11 */ { -1, -1, -1, 16, 10, 7, },
    /* 12 */ { -1, -1, 17, -1, -1, -1, },
    /* 13 */ { -1, -1, -1, -1, -1, -1, },
    /* 14 */ { -1, -1, -1, -1, 19, 7, },
    /* 15 */ { -1, -1, -1, -1, -1, 20, },
    /* 16 */ { -1, -1, -1, -1, -1, -1, },
    /* 17 */ { -1, -1, -1, -1, -1, -1, },
    /* 18 */ { -1, -1, -1, -1, -1, -1, },
    /* 19 */ { -1, -1, -1, -1, -1, -1, },
    /* 20 */ { -1, -1, -1, -1, -1, -1, },
};

PAction lr_action(int state, Symbol t)
{
    return action_table[state][indexOf(t)];
}

int lr_goto(int state, Symbol t)
{
    return goto_table[state][indexOf(t)];
}

const Rule& rule(int index)
{
    return rules[index];
}
