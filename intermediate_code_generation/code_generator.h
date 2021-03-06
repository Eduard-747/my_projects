#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "parser.h"
#include "virtual_table.h"

typedef std::vector<std::pair<std::string,std::string>> strings_pairs ;

struct c_class 
{
    std::string class_name ;
    std::vector<std::tuple<char,std::string,std::string,std::string>> members ;   //  modif  ||  tipe ||  name
    std::vector<std::pair<char,std::vector<std::string>>> function ;
    std::vector<std::tuple<char,std::string,std::string,std::string>> static_members ;
    std::pair<char, std::string> inheritance ;
    std::vector<c_class> nested_class ;
    virtual_table v_table ;
} ;

class generator
{
public:
    generator() : pars("code.cpp") {
        pars.tokenizer() ;
    }
    void read() ;
    void generate_c(std::ofstream &,c_class &) ;
    void generate_user(std::vector<std::string> &) ;
    void generate_user_ctor(std::vector<std::string>::iterator,std::vector<std::string>::iterator,std::vector<std::string> &) ;
    bool is_type(const std::string&) const ;
    static bool obj_or_pointer (const std::string& str, const strings_pairs& class_obj_names, const strings_pairs& pointers) ;
private:
    std::vector<std::string> c_funtions ;
    void creat_function(std::vector<std::string>,c_class&,const char&) ;
    void creat_member(std::vector<std::string>,c_class&,const char&) ;
    c_class read_class(std::vector<std::string>) ;
    void generate_c_functions(std::ofstream &,c_class ) ;
    void generate_virtual_functions(std::ofstream & ,const c_class &) const;
    void generate_user_coll(std::vector<std::string> &,const strings_pairs&,const strings_pairs&) ;
    void generate_c_base_pointer(std::vector<std::string> &,const strings_pairs&,const strings_pairs&) ;
    parser pars ;
    std::vector<c_class> vec_c_class ;
    std::vector<std::string> tokens ;

} ;

#endif