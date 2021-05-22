#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Entry{
public:
    string name;
    string type;
    int offset;
    bool is_func = false;
    Entry(string name,string type,int offset):name(name),type(type),offset(offset){}
};

class FuncEntry: public Entry{
public:
    vector<string> arguments;
    FuncEntry(string name,string type,int offset, vector<string> arguments)
            :Entry(name,type,offset),arguments(arguments){}
};

typedef vector<Entry> Table;

class symbolTable{
    vector<Table> symbolTable;
    public:
        void insertEntry(Table& table, string name, string type, int offset){
            table.push_back(Entry(name, type, offset));

        }
        void insertFuncEntry(Table& table, string name, string type, vector<string> args){
            table.push_back(FuncEntry(name, type, 0 , args));

        }
        bool findSymbolInScope(Table& table,string name){
            for (int i =0 ; i<table.size();i++){
                if(table[i].name.compare(name) == 0)
                    return false;
            }
            return true;
        }

};








