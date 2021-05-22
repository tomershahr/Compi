//
// Created by tomer on 5/21/2021.
//

#ifndef HW3_NODES_HPP
#define HW3_NODES_HPP
#define YYSTYPE Node*
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node{
};

class Num : public Node{
public:
    int value;
    Num(char* val): Node(), value(stoi(val)){}
};

class NumB : public Num{
public:
    NumB(char* val): Num(val){}
};


class Id : public Node{
public:
    string name;
    Id(string in_name) : Node(), name(in_name){}
};


class Type : public Node{
public:
    string type;
    Type(string in_type):Node(), type(in_type){}
};


class String : public Node{
public:
    string value;
    String(char* value):Node(), value(value){}
};


class Binop : public Node{
public:
    char* operation;
    Binop(char* operation): Node(), operation(operation){}
};


class Relop : public Node{
public:
    char* relop_op;
    Relop(char* relop_op): Node(), relop_op(relop_op){}
};

class  Arguments: public Node{
public:

    vector<string> types;
    vector<string> names;
    Arguments(Node* n1,Node* n2): Node(),types(),names(){
        Type* type = (Type*)n1;
        Id* id = (Id*)n2;
        types.push_back(type->type);
        names.push_back(id->name);
    }

    Arguments* merge(Node * node){
        Arguments* a2 = (Arguments*)node;
        this->types.insert(this->types.end(), a2->types.begin(), a2->types.end());
        this->names.insert(this->names.end(), a2->names.begin(), a2->names.end());


        return this;
    }


};
typedef vector<Entry> Table

class Entry{
    public:
        string name;
        string type;
        int offset;
};

class FuncEntry: public Entry{
    vector<string> arguments;
};

bool insertEntry(Table& table, string name, string type, int offset){
    for (int i =0 ; i<table.size();i++){
        if(table[i].name.compare(name) == 0)
            return false;

    }
    table.push_back(Entry(name, type, offset));
    return true;

}
bool insertFuncEntry(Table& table, string name, string type, vector<string> args){

    for (int i =0 ; i<table.size();i++){
        if(table[i].name.compare(name) == 0)
            return false;

    }
    table.push_back(FuncEntry(name, type, 0 , args));
    return true;

}

#endif //HW3_NODES_HPP
