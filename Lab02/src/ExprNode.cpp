#include "ExprNode.h"
#include <sstream>


ExprNode::ExprNode(double val)
: isOperator(false), oper(nullptr), value(val), left(nullptr), right(nullptr) {}


ExprNode::ExprNode(Operacion* operacion, ExprNode* left, ExprNode* right)
: isOperator(true), oper(operacion), value(0.0), left(left), right(right) {}


ExprNode::~ExprNode() {
    // Se asume que cada nodo operador tiene su propia instancia de Operacion
    delete oper;
    // borrar recursivamente subarboles
    delete left;
    delete right;
}


std::string ExprNode::toInfix() const {
    if (!isOperator) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
    std::string l = left ? left->toInfix() : "";
    std::string r = right ? right->toInfix() : "";
    std::string s;
    s += '(';
    s += l;
    s += oper ? oper->simbolo() : '?';
    s += r;
    s += ')';
    return s;
}