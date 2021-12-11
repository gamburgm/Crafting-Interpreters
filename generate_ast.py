from sys import argv, exit
import os

def write_constructor(write, type_name, fields):
    params = []
    init_list = []

    for field in fields:
        f = field.strip()
        split_field = field.strip().split(' ')
        field_type, field_name = split_field[0].strip(), split_field[1].strip()

        if f[0].isupper():
            params.append(f'{field_type}& _{field_name}')
        else:
            params.append(f'{field_type} _{field_name}')
        init_list.append(f'{field_name}(_{field_name})')

    param_str = ', '.join(params)
    init_str = ', '.join(init_list)

    write(f'  {type_name}({param_str}) : {init_str} {{}}')


def write_type(write, base_name, type_name, field_str):
    # TODO should I make the class static?
    write(f'struct {type_name} : {base_name} ' + '{')

    fields = field_str.split(',')
    for field in fields:
        f = field.strip()
        if f[0].isupper():
            field_type, field_name = f.split(' ')
            write(f'  {field_type.strip()}& {field_name.strip()};')
        else:
            write(f'  {f};')

    write('')
    write_constructor(write, type_name, fields)
    write('')
    write('  protected:')
    write('    virtual void do_accept(VisitorBase& visitor);')

    write('};')

def write_visitor(write, base_name, types):
    # first, write visitor base class
    write('class VisitorBase {')
    for t in types:
        type_name = t.split(':')[0].strip()
        # no reason to make this an abstract base class
        write(f'  virtual void visit{type_name}{base_name}({type_name} {base_name.lower()});')
    write('};')

    write('')

    # next, write the concrete class we'll be using that also returns result information
    write('template <typename R>')
    write('class Visitor : VisitorBase {')
    write('  R result();')
    write('};')

def write_ast(write, base_name, types):
    write(f'struct {base_name} ' + '{')
    write('  template <typename R>')
    write('  R accept(Visitor<R>& visitor);')
    write('  protected:')
    write('    virtual void do_accept(VisitorBase& visitor) = 0;')
    write('};')

    for t in types:
        name_part, fields_part = t.split(':')
        type_name = name_part.strip()
        fields = fields_part.strip()
        write('')
        write_type(write, base_name, type_name, fields)

def write_header(write):
    write('#include <vector>')
    write('')
    write('#include "token.h"')
    write('')
    write('template <typename R>')
    write('class Visitor;')
    write('')
    write('class VisitorBase;')

def write_file(output_dir, base_name, types):
    path = output_dir + '/' + base_name.lower() + '.h'

    with open(path, 'w') as ast_file:
        def write(s): print(s, file=ast_file)
        write_header(write)
        write('')
        write_ast(write, base_name, types)
        write('')
        write_visitor(write, base_name, types)

if __name__ == '__main__':
    if len(argv) != 2:
        print('Usage: generate_ast <output directory>')
        exit(64)

    write_file(argv[1], 'Expr', [
        'Binary   : Expr left, Token op, Expr right',
        'Grouping : Expr expression',
        'Literal  : literal_t value',
        'Unary    : Token op, Expr right',
    ])


