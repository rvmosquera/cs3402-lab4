#pragma once

#include <vector>
#include "FlexScanner.hpp"
#include "Token.hpp"

namespace utec {
namespace compilers {

// Grammar:
// exp    -> exp opsuma term | term       ===> term {opsuma exp}
// opsuma -> - | +
// term   -> term opmult factor | factor  ===> factor {opmult term}
// opmult -> *
// factor -> (exp) | numero

class Parser {
 public:
  Parser(std::istream& arg_yyin, std::ostream& arg_yyout) : scanner(arg_yyin, arg_yyout) {}
  
  int expect(Categoria cat_expected){
    auto token = scanner.query_token();
    //std::cout << token._atributo <<" " << cat_expected << std::endl;
    if (token._atributo == cat_expected){
      scanner.get_token();
      
      int res = 0;

      if ( token._atributo == Categoria::NUMERO) {
        res = std::stoi(token._lexema);
        return res;
      } else{
        return res;        
      }        

    } else{
      errors.push_back("caracter " + token._lexema + " unexpected");
    }
  }

  int term() {
    int tmp=0;
    //std::cout << "enter term " << std::endl;
    tmp=factor();
    while(scanner.query_token()._atributo == Categoria::OPMULT) {
      expect(Categoria::OPMULT);
      auto res = factor();
      tmp *= res;
    } 

    return tmp;
  }

  int exp() {
    int tmp;
    tmp=term();
    //std::cout << "in exp term=" << tmp << std::endl;
    while(scanner.query_token()._atributo == Categoria::OPSUMA 
          || scanner.query_token()._atributo == Categoria::OPREST ) {
      
      switch (scanner.query_token()._atributo) {
        case Categoria::OPSUMA:
          {
          expect(Categoria::OPSUMA);
          auto res = term();
          tmp += res;
          }
          break;          
        case Categoria::OPREST:
          {
          expect(Categoria::OPREST);
          auto res = term();
          tmp -= res;
          }
          break;          
        default:
        break;
      }
    }

    return tmp;
  }

  int factor(){
    int tmp=0;
    auto tkn_tmp = scanner.query_token();
    //std::cout << "enter factor " << tkn_tmp._atributo << std::endl;    
    switch (tkn_tmp._atributo) {
    case Categoria::PAREN_L:
      {
        expect(Categoria::PAREN_L);
        tmp=exp();
        expect(Categoria::PAREN_R);
      }
      break;
    case Categoria::NUMERO:
      {
        tmp=expect(Categoria::NUMERO);
      }
      break;

    default:
      break;
    }

    return tmp;
  }

  std::vector<std::string> parse() {
    //S();
    std::vector<std::string> tmp;

    auto res=exp();
    //std::cout << "result " << res << std::endl;
    expect(Categoria::END);
    tmp.push_back(std::to_string(res));

    if(errors.size() == 0)
      return tmp;

    return errors;

    // if( scanner.query_token()._atributo == Categoria::END 
    //   && errors.empty())
    //   return true;
    // return false;
  }

 private:
  std::vector<std::string> errors;
  FlexScanner scanner;
};

}  // namespace compilers
}  // namespace utec