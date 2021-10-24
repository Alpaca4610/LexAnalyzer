#include "functions.h"

//定义数据结构存储词语以及对应的记号
class mark {
private:
    std::string keyword;
    int no;
public:
    mark(std::string kw, int no_) {
        keyword = kw;
        no = no_;
    }

    std::string GetKeyword() {
        return keyword;
    }

    int GetMark() {
        return no;
    }
};

//C语言保留字列表
static mark KeyWordMark[30] = {
        mark("int", 1), mark("float", 2),
        mark("double", 3), mark("long", 4),
        mark("char", 5), mark("void", 6),
        mark("short", 7), mark("unsigned", 8),
        mark("signed", 9), mark("bool", 10),
        mark("main", 11), mark("if", 12),
        mark("else", 13), mark("for", 14),
        mark("while", 15), mark("do", 16),
        mark("break", 17), mark("return", 18),
        mark("switch", 19), mark("default", 20),
        mark("case", 21), mark("printf", 22),
        mark("struct", 23), mark("enum", 24),
        mark("typedef", 25), mark("const", 26),
        mark("sizeof", 27), mark("static", 28),
        mark("false", 29), mark("true", 30)
};

//C语言分隔符列表
static mark BoundaryMark[11] = {
        mark(",", 31), mark(";", 32),
        mark("(", 33), mark(")", 34),
        mark("{", 35), mark("}", 36),
        mark("[", 37), mark("]", 38),
        mark("\"", 39), mark("\'", 40),
        mark(".", 41)
};

//C语言运算符列表
static mark SymbolMark[10] = {
        mark("<", 42), mark(">", 43),
        mark("+", 44), mark("-", 45),
        mark("*", 46), mark("/", 47),
        mark("=", 48), mark("!", 49),
        mark(".", 50), mark("%", 51)
};

//C语言复合运算符列表
static mark DoubleSymbolMark[12] = {
        mark("!=", 51), mark(">=", 52),
        mark("<=", 53), mark("==", 54),
        mark("++", 55), mark("--", 56),
        mark("*=", 57), mark("/=", 58),
        mark("==", 59), mark("+=", 60),
        mark("-=", 61), mark("%=", 62)
};

//判断词法分析是否应当结束
bool isEOF(std::string data) {
    if (data == "EOF")
        return true;
    else
        return false;
}

//判断当前读入字符是否为0～9的数字
bool isNum(std::string data) {
    if (data >= "0" && data <= "9")
        return true;
    else
        return false;
}

//判断当前读入字符是否为空格
bool isBlank(std::string data) {
    if (data == " " || data == "\t")
        return true;
    else
        return false;
}

//判断当前读入字符是否为英文字母
bool isLetter(std::string data) {
    if ((data >= "a" && data <= "z") || (data >= "A" && data <= "Z"))
        return true;
    else
        return false;
}

//判断当前读入字符是否为运算符
int isSymbol(std::string data) {
    for (auto i: SymbolMark) {
        if (data == i.GetKeyword())
            return i.GetMark();
    }
    for (auto i: BoundaryMark) {
        if (data == i.GetKeyword())
            return i.GetMark();
    }
    return 0;
}

//判断当前读入字符是否为双目运算符的前缀
bool isPrefix(std::string data) {
    if (data == "<" || data == ">" || data == "+" || data == "-" || data == "=" || data == "*" || data == "!" ||
        data == "/" || data == "%")
        return true;
    else
        return false;
}

//判断当前缓冲区字符是否为C语言保留关键字
int isKeyWord(std::string data) {
    for (auto i: KeyWordMark) {
        if (data == i.GetKeyword())
            return i.GetMark();
    }
    return 0;
}

//判断当前读入字符是否为分隔符
int isBound(std::string data) {
    for (auto i: BoundaryMark) {
        if (data == i.GetKeyword())
            return i.GetMark();
    }
    return 0;
}

//判断当前读入字符是否为换行符
bool isNewLine(std::string data) {
    if (data == "\n")
        return true;
    else
        return false;
}

//判断当前读入字符是否为分号
bool isSemicolon(std::string data) {
    if (data == ";")
        return true;
    else
        return false;
}

//判断当前读入字符的类型
WordType JudgeWordType(std::string data) {
    if (isEOF(data)) {
        return eof;
    }
    if (isNum(data)) {
        return number;
    }
    if (isLetter(data)) {
        return letter;
    }
    if (isBlank(data)) {
        return blank;
    }
    if (isSymbol(data)) {
        return symbol;
    }
    if (isNewLine(data)) {
        return nl;
    } else
        return unknown;
}

//错误恢复处理，处理方法为跳到错误所在行的下一行继续进行词法分析
void errorRecover(int *position, std::string code[]) {
    while (!(code[*position] == "\n")) {
        (*position)++;
    }
    return;
}

//判断当前缓冲区符号是否为双目运算符
int isMultiSym(std::string data) {
    for (auto i: DoubleSymbolMark) {
        if (data == i.GetKeyword())
            return i.GetMark();
    }
    return 0;
}
