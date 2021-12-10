from sys import argv, exit
import os

def write_type(write, base_name, type_name, field_str):
    # TODO should I make the class static?
    write(f"struct {type_name} : {base_name} " + "{")

    fields = field_str.split(",")
    for field in fields:
        write(f"  {field.strip()};")

    write("};")

def write_visitor(write, base_name, types):
    write("template <typename R>")
    write("class Visitor {")

    for t in types:
        type_name = t.split(":")[0].strip()
        write(f"  virtual void visit{type_name}{base_name}({type_name} {base_name.lower()}) = 0;")

    write(f"  R result();")

    write("};")

def write_ast(write, base_name, types):
    write(f"struct {base_name} " + "{")
    write("  template <typename R>")
    write("  R accept(Visitor<R>& visitor);")
    write("  protected:")
    write("    virtual void do_accept(Visitor<R>& visitor) = 0;")
    write("};")

    for t in types:
        name_part, fields_part = t.split(":")
        type_name = name_part.strip()
        fields = fields_part.strip()
        write("")
        write_type(write, base_name, type_name, fields)

def write_header(write):
    write("#include <vector>")
    write("")
    write("#include \"token.h\"")
    write("")
    write("class Visitor;")

def write_file(output_dir, base_name, types):
    path = output_dir + '/' + base_name.lower() + ".h"

    with open(path, "w") as ast_file:
        def write(s): print(s, file=ast_file)
        write_header(write)
        write("")
        write_ast(write, base_name, types)
        write("")
        write_visitor(write, base_name, types)

if __name__ == "__main__":
    if len(argv) != 2:
        print("Usage: generate_ast <output directory>")
        exit(64)

    write_file(argv[1], "Expr", [
        "Binary   : Expr left, Token op, Expr right",
        "Grouping : Expr expression",
        "Literal  : literal_t value",
        "Unary    : Token op, Expr right",
    ])


