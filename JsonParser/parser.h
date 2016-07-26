//
// Created by Administrator on 2016/7/25.
//

#ifndef JSONPARSER_PARSER_H
#define JSONPARSER_PARSER_H

#include "json.h"
#include "lex.h"

/*
 * 文法：
 * jobj -> {datalist}
 *      -> number
 *      -> str
 * datalist -> data opt
 * opt -> ,data opt | epsilon
 * data->str : jobj
 *     ->str : jlist
 *     ->str : num
 *     ->str : str
 *     ->str : true
 *     ->str : false
 *     ->str : null
 *jlist -> [jobj, jobj, jobj....]
 */
class Parser {
    Lex lex;
    Token current;
    Token prev;

    Json_Array *jsonList_aux(Json_Array *pArray);

    Json_Object *jsonObj_aux(Json_Object *object);

    Json_Array *jsonList();


public:
    Parser(const string &s) : lex(s) { current = lex.nextToken(); }

    void match(TYPE type);

    Json_Object* json();

    Json_Object *jsonObj();


};


#endif //JSONPARSER_PARSER_H
