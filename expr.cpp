#include "expr.h"

template <typename R>
R Visitor<R>::get_result() {
  return result;
}

template <typename R>
R Expr::accept(Visitor<R>& visitor) {
  do_accept(visitor);
  return visitor.get_result();
}

void Binary::do_accept(VisitorBase& visitor) {
  visitor.visitBinaryExpr(*this);
}

void Grouping::do_accept(VisitorBase& visitor) {
  visitor.visitGroupingExpr(*this);
}

void Literal::do_accept(VisitorBase& visitor) {
  visitor.visitLiteralExpr(*this);
}

void Unary::do_accept(VisitorBase& visitor) {
  visitor.visitUnaryExpr(*this);
}
