#include <vector>
#include <memory>

#include "token.h"

template<typename R>
class Visitor;

class VisitorBase;

struct Expr {
  template <typename R>
  R accept(Visitor<R>& visitor);
  protected:
    virtual void do_accept(VisitorBase& visitor) = 0;
};

struct Binary : Expr {
  shared_ptr<Expr> left;
  shared_ptr<Token> op;
  shared_ptr<Expr> right;
};

struct Grouping : Expr {
  shared_ptr<Expr> expression;
};

struct Literal : Expr {
  literal_t value;
};

struct Unary : Expr {
  shared_ptr<Token> op;
  shared_ptr<Expr> right;
};

class VisitorBase {
  virtual void visitBinaryExpr(Binary expr) = 0;
  virtual void visitGroupingExpr(Grouping expr) = 0;
  virtual void visitLiteralExpr(Literal expr) = 0;
  virtual void visitUnaryExpr(Unary expr) = 0;
};

template <typename R>
class Visitor : VisitorBase {
  R result();
};
