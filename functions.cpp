//
// Created by Alpaca on 2021/10/4.
//

#include "functions.h"

////关键字列表
//std::string KeyWord[20] = {"int","float","double","long","char","void","main","if","else","for","while","do","break","return","switch","default","case","printf","",""};
////符号列表
//std::string Symbol[17] = {"<",">",",",";","(",")","{","}","+","-","*","/","="};
//std::string DoubleSymbol[] = {"!=",">=","<=","=="};

class mark{
private:
    std::string keyword;
    int no;
public:
    mark(std::string kw,int no_){
        keyword = kw;
        no = no_;
    }
    std::string GetKeyword(){
        return keyword;
    }
    int GetMark(){
        return no;
    }
};

    static mark KeyWordMark[20] =  {
            mark("int",1),mark("float",2),
            mark("double",3),mark("long",4),
            mark("char",5),mark("void",6),
            mark("main",7),mark("if",8),
            mark("else",9),mark("for",8),
            mark("while",9),mark("do",10),
            mark("break",11),mark("return",12),
            mark("switch",13),mark("default",14),
            mark("case",15),mark("printf",16),
            mark("",2),mark("",2)};

    static mark SymbolMark[20] = {
            mark("<",17),mark(">",18),
            mark(",",19),mark(";",20),
            mark("(",21),mark(")",22),
            mark("{",23),mark("}",24),
            mark("+",25),mark("-",26),
            mark("*",27),mark("/",28),
            mark("=",29),mark("!",30),
            mark("\"",31),mark("",2),
            mark("",2),mark("",2),
            mark("",2),mark("",2)};

    static mark DoubleSymbolMark[20] = {
            mark("!=",32),mark(">=",33),
            mark("<=",34),mark("==",35),
            mark("++",36),mark("--",37),
            mark("*=",38),mark("/=",39),
            mark("==",40),mark("",2),
            mark("",2),mark("",2),
            mark("",2),mark("",2),
            mark("",2),mark("",2),
            mark("",2),mark("",2),
            mark("",2),mark("",2)};


bool isNum(std::string data){
    if(data >= "0" && data <= "9")
        return true;
    else
        return false;
}

bool isBlank(std::string data){
    if(data == " ")
        return true;
    else
        return false;
}

bool isLetter(std::string data){
    if((data >= "a" && data <= "z") || (data >= "A" && data <= "Z"))
        return true;
    else
        return false;
}

int isSymbol(std::string data){
    for(auto i : SymbolMark){
        if(data == i.GetKeyword())
            return i.GetMark();
    }
    return 0;
}
bool isPrefix(std::string data){
    if(data == "<" || data == ">" || data == "+" || data == "-" || data == "=" || data == "*" || data == "!" || data == "/")
        return true;
    else
        return false;
}

int isKeyWord(std::string data){
    for(auto i : KeyWordMark){
        if(data == i.GetKeyword())
            return i.GetMark();
    }
    return 0;
}


bool isNewLine(std::string data){
    if(data == "\n")
        return true;
    else
        return false;
}

bool isSemicolon(std::string data){
    if(data == ";")
        return true;
    else
        return false;
}

WordType JudgeWordType(std::string data){
    if(isNum(data)){
        return number;
    }
    if(isLetter(data)){
        return letter;
    }
    if(isBlank(data)){
        return blank;
    }
    if(isSymbol(data)){
        return symbol;
    }
    if(isNewLine(data)){
        return nl;
    }
    else
        return unknown;
}

void errorRecover(int* position,std::string code[]){
    while(!isSemicolon(code[*position]) && !(code[*position] == "\n") && !isBlank(code[*position])){
        (*position)++;
    }
        return;
}

int isMultiSym(std::string data){
    for(auto i : DoubleSymbolMark){
        if(data == i.GetKeyword())
            return i.GetMark();
    }
    return 0;
}
bool isBrackets(std::string data){
    if(data == "(" || data == ")"|| data == "{"|| data == "}"|| data == "["|| data == "]"|| data == "\"")
        return true;
    else
        return false;
}

std::string identifierConnect(std::string mainString, std::string charToConnect){
    mainString+=charToConnect;
    return mainString;
}