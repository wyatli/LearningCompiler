//
// Created by Administrator on 2016/7/26.
//

#include "json.h"

Json_String* Json_Value::getJsonString() {
    return nullptr;
}

Json_Array* Json_Value::getJsonArray() {
    return nullptr;

}

Json_Object* Json_Value::getJsonObject() {
    return nullptr;
}


Json_String::Json_String(const string &s) : Json_Value(JSON_STRING), m_str(s) {
}

Json_Object::Json_Object() : Json_Value(JSON_OBJECT) {

}

void Json_Object::put(const string &s, Json_Value *val) {
    jmap[s] = val;
}

Json_String* Json_String::getJsonString() {
    return this;
}


Json_Object* Json_Object::getJsonObject() {
    return this;
}



Json_Array* Json_Array::getJsonArray() {
    return this;
}
Json_Array* Json_Object::getArray(const string& s) {
    return jmap[s]->getJsonArray();
}

string Json_Object::getString(const string& s) {
    return jmap[s]->getJsonString()->toString();
}

double Json_Object::getNum(const string& s) {
    return jmap[s]->getNum();
}




