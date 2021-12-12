#include <string>
#include <sstream>
#include <memory>

#include "expr.h"

class AstPrinter : Visitor<string> {
  shared_ptr<stringstream> ss;
  string print(Expr& expr);
  string parenthesize(string name, Expr& expr...);

  public:
    // TODO note: you _could_ make `get_result` virtual pure because the template isn't on the method
    AstPrinter();
    void visitBinaryExpr(Binary& expr) override;
    void visitGroupingExpr(Grouping& expr) override;
    void visitLiteralExpr(Literal& expr) override;
    void visitUnaryExpr(Unary& expr) override;
};
