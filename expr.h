#include <vector>

#include "token.h"

template <typename R>
class Visitor;

class VisitorBase;

struct Expr {
  template <typename R>
  R accept(Visitor<R>& visitor);
  protected:
    virtual void do_accept(VisitorBase& visitor) = 0;
};

struct Binary : Expr {
  Expr& left;
  Token& op;
  Expr& right;

  Binary(Expr& _left, Token& _op, Expr& _right) : left(_left), op(_op), right(_right) {}

  protected:
    virtual void do_accept(VisitorBase& visitor) override;
};

struct Grouping : Expr {
  Expr& expression;

  Grouping(Expr& _expression) : expression(_expression) {}

  protected:
    virtual void do_accept(VisitorBase& visitor) override;
};

struct Literal : Expr {
  literal_t value;

  Literal(literal_t _value) : value(_value) {}

  protected:
    virtual void do_accept(VisitorBase& visitor) override;
};

struct Unary : Expr {
  Token& op;
  Expr& right;

  Unary(Token& _op, Expr& _right) : op(_op), right(_right) {}

  protected:
    virtual void do_accept(VisitorBase& visitor) override;
};

class VisitorBase {
  public:
    virtual void visitBinaryExpr(Binary& expr) = 0;
    virtual void visitGroupingExpr(Grouping& expr) = 0;
    virtual void visitLiteralExpr(Literal& expr) = 0;
    virtual void visitUnaryExpr(Unary& expr) = 0;
};

template <typename R>
class Visitor : VisitorBase {
  R result;

  public:
    R get_result();
};
