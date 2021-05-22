#include <string>
#include <vector>
#include <iostream>
#include "hw3_output.hpp"

using namespace std;
using namespace output;


class Entry{
public:
    string name;
    string type;
    int offset;
    vector<string> args_types;
    bool is_func;

    Entry(string _name,string _type,int _offset) : name(_name), type(_type), offset(_offset), args_types(vector<string>()),  is_func(false){} //for varible

    Entry(string _name,string _type, vector<string> args): name(_name), type(_type), offset(0), args_types(args), is_func(true){} //for func
};

/*
class FuncEntry: public Entry{
public:
    vector<string> args_types;
    FuncEntry(string name,string type, vector<string> a_types)
            :Entry(name,type,0),args_types(a_types){this->is_func= true;}
};
*/

typedef vector<Entry> Table;

class SymbolTables{
    int curr_offset;
    vector<Table> tables;
    vector<int> offsets;

public:
    SymbolTables(): curr_offset(0){
        tables.push_back(Table());
        offsets.push_back(0);
    }

    void insertEntry( string name, string type){
        int curr = offsets.back();
        tables[tables.size()-1].push_back(Entry(name, type, curr));
        offsets[offsets.size()-1]= curr+1;

    }

    void insertFuncArgEntry( string name, string type){
        tables[tables.size()-1].push_back(Entry(name, type, curr_offset--));
    }

    void insertFuncEntry(string name, string type, vector<string> args){
        tables[tables.size()-1].push_back(Entry(name, type, args));
        offsets.push_back(offsets.back());
        tables.push_back(Table());
        curr_offset =-1;
    }

    bool findSymbol(string name){
        for(unsigned int j =0;j<tables.size();j++) {
            Table curr = tables[j];
            for (unsigned int i = 0; i < curr.size(); i++) {
                if (curr[i].name.compare(name) == 0)
                    return true;
            }

        }
        return false;
    }

    void closeScope(){
        endScope();
        Table table = tables[1];
        for(unsigned int i=0; i< table.size(); i++){
            if(!table[i].is_func)
                printID(table[i].name, table[i].offset, table[i].type);
        }
        offsets.pop_back();
        tables.pop_back();
    }
};
