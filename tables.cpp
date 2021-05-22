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
        Table global;
        global.push_back(Entry("print", "VOID",vector<string>(1, "STRING")));
        global.push_back(Entry("printi", "VOID",vector<string>(1, "INT")));
        tables.push_back(global);
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

    bool findSymbol(string name,Entry& entry){
        for(unsigned int j =0;j<tables.size();j++) {
            Table curr = tables[j];
            for (unsigned int i = 0; i < curr.size(); i++) {
                if (curr[i].name.compare(name) == 0){
                    entry = curr[i];
                    return true;
                }
            }
        }
        return false;
    }

    string getSymbolType(string symbol){
        for(unsigned int j =0;j<tables.size();j++) {
            Table curr = tables[j];
            for (unsigned int i = 0; i < curr.size(); i++) {
                if (curr[i].name.compare(symbol) == 0)
                    return curr[i].type;
            }
        }
        return "";
    }

    vector<string> getFuncArgs(string func){
        for(unsigned int j =0;j<tables.size();j++) {
            Table curr = tables[j];
            for (unsigned int i = 0; i < curr.size(); i++) {
                if (curr[i].name.compare(func) == 0)
                    return curr[i].args_types;
            }
        }
        return vector<string>();
    }
/*
    bool isValidMain(){

        for(unsigned int i= 0; i<tables[0].size();i++){
            if (tables[0][i].name.compare("main"){
                if(!tables[0][i].type.compare("VOID") || !tables[0][i].args_types.empty())
                    return false;
                return true;
            }
        }
        return false;
    }
    */

    void closeScope(){
        endScope();
        Table table = tables.back();
        for(unsigned int i=0; i< table.size(); i++){
            string name = table[i].name;
            string types =  table[i].type;

            if(table[i].is_func){
                vector<string> args = getFuncArgs(name);
                types =makeFunctionType(types, args);
            }

            printID(name , table[i].offset, types);
        }
        offsets.pop_back();
        tables.pop_back();
    }
};
