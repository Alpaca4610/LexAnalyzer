#include <iostream>

//定义switch中使用的枚举类型
enum WordType {
    unknown = 0, keyWord = 1, symbol = 2, number = 3, letter = 4, blank = 5, nl = 6, eof = 7
};

bool isEOF(std::string);

bool isNum(std::string);

bool isBlank(std::string);

bool isLetter(std::string);

int isSymbol(std::string);

int isKeyWord(std::string);

bool isNewLine(std::string);

bool isPrefix(std::string);

bool isSemicolon(std::string);

int isBound(std::string);

WordType JudgeWordType(std::string);

void errorRecover(int *, std::string[]);

int isMultiSym(std::string);

//std::string identifierConnect(std::string, std::string);