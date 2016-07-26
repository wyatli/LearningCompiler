//
// Created by Administrator on 2016/7/25.
//

#ifndef JSONPARSER_JSON_H
#define JSONPARSER_JSON_H

#include <memory>
#include <vector>
#include <algorithm>
#include <map>

class Json_String;

class Json_Value;

class Json_Object;

class Json_Array;

using namespace std;
typedef enum {
    JSON_STRING, JSON_ARRAY, JSON_OBJECT
} JSON_TYPE;

class Json_Value {
protected:
    JSON_TYPE m_type;
    //标记属于哪种值
    union {
        double m_num;
        bool m_bool;
        bool null;
    };
public:
    Json_Value(JSON_TYPE type) : m_type(type) { }

    Json_Value() { }

    /*
     * 根据标签转为某个实例
     */

    virtual Json_String* getJsonString();

    virtual Json_Array* getJsonArray();

    virtual Json_Object* getJsonObject();

    void setBool(bool val) {
        m_bool = val;
    }

    void setNull(bool null) {
        this->null = null;
    }

    bool getNull() {
        return null;
    }

    double getNum() {
        return m_num;
    }

    bool getBool() {
        return m_bool;
    }

    void setNum(double num) {
        m_num = num;
    }
};

class Json_Array : public Json_Value {//json_list
protected:
    vector<Json_Object*> m_list;//

public:

    Json_Object* operator[](int id) {
        return m_list[id];
    }
    void add_Obj(Json_Object *object) {
        m_list.push_back(object);
    }

    virtual Json_Array* getJsonArray();


    Json_Array() : Json_Value(JSON_ARRAY) { }

};

class Json_String : public Json_Value {
private:
    string m_str;

public:
    Json_String(const string &s);

    string toString() {
        return m_str;
    }

    virtual Json_String* getJsonString();
};

class Json_Object : public Json_Value {
private:

    map<string, Json_Value*> jmap;

public:
    Json_Object();

    void put(const string &, Json_Value *);

    Json_Array* getArray(const string &);

    string getString(const string &);

    double getNum(const string &);

    virtual Json_Object* getJsonObject();
};

#endif //JSONPARSER_JSON_H
