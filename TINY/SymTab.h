//
// Created by abc84 on 2016/6/8.
//

#ifndef TINY_SYMTAB_H
#define TINY_SYMTAB_H

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

struct Entry {
    //符号表中的链表,包含键值对,和指向下一个条目的指针
    Entry *next;
    Entry *pre;
    //下一个条目
    const string name;
    vector<int> linenos;
    //所在程序的行数
    int memloc;

    //tab里第几个加进来的元素
    Entry(const string &n, int loc) : name(n), linenos(0), memloc(loc),next(nullptr),pre(nullptr) { }
};

typedef Entry *List;
#define MAX_BUCKET_SIZE 11
/*
 * 符号表
 */
#define SHIFT 4

inline int hash_(const string &s) {//计算哈希值
    int val = 0;
    for (const char &c : s) {
        val = ((val << SHIFT) + c) % MAX_BUCKET_SIZE;
    }
    return val;
}

class SymTab {
public:
    SymTab() {
        for (int i = 0; i < MAX_BUCKET_SIZE; ++i) {
            bucket[i] = nullptr;
        }
    }
    void insert(const string &, int lineno);//插入

    pair<int, Entry *> lookup(const string &); //查询

    void printTab() {
        cout << "name    " << "count    " << "lineno         " << endl;
        for (int i = 0; i < MAX_BUCKET_SIZE; ++i) {
            List l = bucket[i];
            while (l) {
                printf("%-8s%-12d", const_cast<char*>(l->name.c_str()), l->memloc);
                //cout << l->name << "        " << l->memloc<<"         ";
                for (int i : l->linenos) {
                    cout << i << " ";
                }
                cout << endl;
                l = l->next;
            }
        }
    }

    void remove(const string &);

    void clear();

    virtual ~SymTab() {
        clear();
    }

private:
    static int count;
    List bucket[MAX_BUCKET_SIZE];
};

int SymTab::count = 0;

inline void SymTab::insert(const string &s, int lineno) {
    int hashval = hash_(s);
    List l = bucket[hashval];
    if (lookup(s).second) {//若有该name
        lookup(s).second->linenos.push_back(lineno);
        return;
    }
    /*
     * 没有添加过的情况
     */
    if (l) {
        Entry *newEntry = new Entry(s, count++);
        newEntry->linenos.push_back(lineno);
        newEntry->next = l;
        l->pre = newEntry;
        newEntry->pre = nullptr;
        bucket[hashval] = newEntry;
    }
    else {
        Entry *newEntry = new Entry(s, count++);
        newEntry->linenos.push_back(lineno);
        newEntry->next = l;
        newEntry->pre = nullptr;
        bucket[hashval] = newEntry;
    }
}

inline pair<int, Entry *> SymTab::lookup(const string &s) {
    int hashval = hash_(s);
    List l = bucket[hashval];
    Entry *temp = l;//头结点
    while (temp) {
        if (s == temp->name) {
            return {temp->memloc, temp};
        }
        temp = temp->next;
    }
    return {-1, nullptr};
}

inline void SymTab::clear() {//清空hashtable
    for (int i = 0; i < MAX_BUCKET_SIZE; ++i) {
        List l = bucket[i];
        while (l != nullptr) {
            Entry *tem = l->next;
            delete l;
            l = tem;
        }
        bucket[i] = nullptr;//必须加这一句
    }
}

inline void SymTab::remove(const string &s) {//删除s对应的节点
    Entry *node = lookup(s).second;
    if (!node)//没找到
        return;;
    Entry *preNode = node->pre;
    if (preNode && node->next) {//非首尾节点
        preNode->next = node->next;
        node->next->pre = preNode;
        delete node;
        node = nullptr;
    }
    else if (preNode == nullptr) {//首节点
        Entry *temp = node;
        bucket[hash_(s)] = node->next;
        delete temp;
        temp = nullptr;
    }
    else if (node->next == nullptr) {//尾节点
        preNode->next = node->next;
        delete node;
        node = nullptr;
    }
}


void testSytb() {
    SymTab st;
    st.insert("sb",7);
    st.insert("sb",8);
    st.remove("sb");
    //st.insert("sb",1);
    st.insert("sc",2);
    st.insert("dact",12);
    st.insert("sd",3);
    st.insert("sc",7);
    cout << st.lookup("dact").first <<endl;
    st.printTab();
}


#endif //TINY_SYMTAB_H
