//
// Created by Administrator on 2016/7/25.
//

#include "parser.h"
#include "lex.h"


void Parser::match(TYPE type) {
    if (!current.type == type) {
        cout << "token type " << type << " mismatch" <<  " str:" << current.a.rep << prev.a.rep <<"at line:" <<current.lineno << endl;
    }
    prev = current;
    current = lex.nextToken();//跳过当前
}

Json_Object *Parser::jsonObj_aux(Json_Object *object) {

    string key;
    Json_Value *value = nullptr;

    match(STR);
    key = prev.a.rep;
    match(COLON);
    if (current.type == NUM) {
        match(NUM);
        value = new Json_Value;
        value->setNum(prev.a.val);
    }
    else if (current.type == BOOL_) {
        match(BOOL_);
        value = new Json_Value;
        value->setBool(prev.a.boolean);

		cout << "sb" << endl;
    }
    else if (current.type == STR) {
        match(STR);
        value = new Json_String(prev.a.rep);
    }
    else if (current.type == NUL) {
        match(NUL);
        value = new Json_Value;
        value->setNull(true);
    }
    else if (current.type == LSB) {
        //match(LSB);
        value = jsonList();
    }
    else {
        cout << "value can not be type" << current.type << endl;
    }
    object->put(key, value);
    if (current.type == COMMA) {//递归调用
        match(COMMA);
        jsonObj_aux(object);
    }
    return object;
}

Json_Object *Parser::jsonObj() {
    match(LB);
    Json_Object *object = new Json_Object;
    Json_Object *ret = jsonObj_aux(object);
    match(RB);
    return ret;
}


Json_Array *Parser::jsonList_aux(Json_Array *pArray) {
    Json_Object *object = jsonObj();
    pArray->add_Obj(object);
    if (current.type == COMMA) {
        match(COMMA);
        jsonList_aux(pArray);//递归
    }
	return pArray;
}

Json_Array *Parser::jsonList() {
    match(LSB);
    Json_Array *array = new Json_Array;
    jsonList_aux(array);
    match(RSB);
    return array;
}

Json_Object* Parser::json() {
    return jsonObj();
}












