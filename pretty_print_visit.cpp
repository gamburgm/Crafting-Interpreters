#include <variant>

#include "pretty_print_visit.h"
#include "token.h"

using namespace std;

AstPrinter::AstPrinter() {
  ss = make_shared<stringstream>();
}

void AstPrinter::visitBinaryExpr(Binary& expr) {
  *ss << parenthesize(expr.op.lexeme, expr.left, expr.right);
}

void AstPrinter::visitGroupingExpr(Grouping& expr) {
  *ss << parenthesize(string("group"), expr.expression);
}

void AstPrinter::visitLiteralExpr(Literal& expr) {
  // FIXME is this absurd?
  if (holds_alternative<nullptr_t>(expr.value) && get<nullptr_t>(expr.value) == nullptr) {
    *ss << "nil";
  } else {
    // FIXME what is this supposed to be?
    *ss << expr.toString();
  }
}

void AstPrinter::visitUnaryExpr(Unary& expr) {
  *ss << parenthesize(expr.op.lexeme, expr.right);
}

// FIXME you have a stream, and then you call a function, that builds a separate stream,
//       converts that stream into a string, and then streams the result back in...wtf?
// FIXME this is a mess. Argument should probably be a vector for ease of iteration.
/* string AstPrinter::parenthesize(string name, Expr& expr...) { */
/*   stringstream ss; */

/*   ss << "(" << name; */
/*   for ( */

/*   return ss.str(); */
/* } */
