#pragma once

#include "FlexScanner.hpp"
#include "Token.hpp"

namespace utec {
namespace compilers {

// Grammar:
// S -> AB
// A -> aA | a
// B -> bB | b

class Parser {
 public:
  Parser(std::istream& arg_yyin, std::ostream& arg_yyout) : scanner(arg_yyin, arg_yyout) {}
  
  bool A() {
    auto token = scanner.query_token();
    if( token._atributo == Categoria::A ){
        scanner.get_token();
    } else {
        return false; //error
    }

    while( 1 ){
        token = scanner.query_token();

        if(token._atributo == Categoria::A){
            scanner.get_token();
        } else if(token._atributo == Categoria::B){
            return true;
        } else {
            return false; //error
        }
    }
  }

  bool B() {
    auto token = scanner.get_token();
    if( token._atributo == Categoria::B ){
        return B();
    }
    else if( token._atributo == Categoria::END ){
        return true;
    }
    else {
        return false; //error
    }
  }

  bool S(){
    return A() && B();
  }

  bool parse() {
    return S();
  }

 private:
  FlexScanner scanner;
};

}  // namespace compilers
}  // namespace utec