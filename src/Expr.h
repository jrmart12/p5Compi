#ifndef __EXPR_H__
#define __EXPR_H__

#include <vector>

enum class Symbol: unsigned {
    input = 0,
    stmt_list = 1,
    stmt = 2,
    expr = 3,
    term = 4,
    factor = 5,
    Eof = 6,
    SEMICOLON = 7,
    ID = 8,
    ASSIGN = 9,
    PRINT = 10,
    SUM = 11,
    MULT = 12,
    NUMBER = 13,
    OPEN_PAREN = 14,
    CLOSE_PAREN = 15,
    Epsilon = 16
};

struct Rule {
    Rule() = default;
    Rule(const Rule&) = delete;

    Symbol lhs;
    std::vector<Symbol> rhs;
    bool isEmpty() const { return rhs.empty(); }
};

using RuleRef = std::reference_wrapper<Rule>;

enum class PActionType {
    Shift,
    Reduce,
    Accept,
    Empty
};

class PAction {
public:
    PAction(): action(PActionType::Empty), value(0) {}
    PAction(PActionType action, int value): action(action), value(value) {}
    bool isShift() const { return action == PActionType::Shift; }
    bool isReduce() const { return action == PActionType::Reduce; }
    bool isAccept() const { return action == PActionType::Accept; }
    bool isEmpty() const { return action == PActionType::Empty; }
    int getValue() const { return value; }
private:
    PActionType action;
    int value;
};

static inline unsigned indexOf(Symbol s) {
    unsigned index = static_cast<unsigned>(s);
    if (index < 6) return index;
    else return (index - 6);
}

static inline bool isTerminal(Symbol s) {
    return static_cast<unsigned>(s) >= 6;
}

const Rule& rule(int index);
PAction lr_action(int state, Symbol t);
int lr_goto(int state, Symbol t);

#endif
