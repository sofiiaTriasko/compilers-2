#include "ast_evaluator.hh"
#include "../utils/errors.hh"

namespace ast
{
    int ASTEvaluator::visit(const BinaryOperator& binop)
    {
        int left_op = binop.get_left().accept(*this);
        int right_op = binop.get_right().accept(*this);
        switch (binop.op)
        {
        case o_times:
            return left_op * right_op;
        case o_divide:
            return left_op / right_op;
        case o_plus:
            return left_op + right_op;
        case o_minus:
            return left_op - right_op;
        case o_eq:
            return left_op == right_op;
        case o_neq:
            return left_op != right_op;
        case o_lt:
            return left_op < right_op;
        case o_gt:
            return left_op > right_op;
        case o_le:
            return left_op <= right_op;
        case o_ge:
            return left_op >= right_op;
        default:
            utils::error("Error: NOT RECOGNIZED BINARY OPERATION.");
        }
    }
    int ASTEvaluator::visit(const Sequence& seqExpr)
    {
        int value;
        const auto exprs = seqExpr.get_exprs();
        if (exprs.cbegin() == exprs.cend())
        {
            utils::error("Error: EMPTY SEQUENCE CANNOT BE EVALUATED.");
        }
        for (auto expr = exprs.cbegin(); expr != exprs.cend(); expr++)
        {
            value = (*expr)->accept(*this);
        }
        return value;
    }

    int ASTEvaluator::visit(const Let& let)
    {
        utils::error("Error: NOT RECOGNIZED LET.");
    }
    int ASTEvaluator::visit(const Identifier& id)
    {
        utils::error("Error: NOT RECOGNIZED IDENTIFIED.");
    }

    int ASTEvaluator::visit(const IfThenElse& ite)
    {
        int cond = ite.get_condition().accept(*this);
        int then_part = ite.get_then_part().accept(*this);
        int else_part = ite.get_else_part().accept(*this);
        if (cond)
        {
            return then_part;
        }
        else
        {
            return else_part;
        }
    }
    int ASTEvaluator::visit(const VarDecl& decl)
    {
        utils::error("Error: VARIABLE DECLARATION NOT RECOGNIZED.");
    }
    int ASTEvaluator::visit(const FunDecl& decl)
    {
        utils::error("Error : FUNCTION DECLARATION NOT RECOGNIZED.");
    }
    int ASTEvaluator::visit(const FunCall& call)
    {
        utils::error("Error : FUNCTION CALLING NOT RECOGNIZED.");
    }
    int ASTEvaluator::visit(const Break& brk)
    {
        utils::error("Error: BREAK OPERATOR NOT RECOGNIZED.");
    }
    int ASTEvaluator::visit(const Assign& assign)
    {
        utils::error("Error : ASSIGN OPERATOR NOT RECOGNIZED.");
    }
    int ASTEvaluator::visit(const WhileLoop& loop)
    {
        utils::error("Error: WHILE LOOP NOT RECOGNIZED.");
    }
    int ASTEvaluator::visit(const ForLoop& loop)
    {
        utils::error("Error: FOR LOOP NOT RECOGNIZED.");
    }
    int ASTEvaluator::visit(const IntegerLiteral& literal)
    {
        return literal.value;
    }
    int ASTEvaluator::visit(const StringLiteral& literal)
    {
        utils::error("Error: NODE STRING LITERAL NOT RECOGNIZED");
    }

} // namespace ast