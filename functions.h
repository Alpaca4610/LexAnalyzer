//
// Created by Alpaca on 2021/10/4.
//

#ifndef LEXANALYZER_FUNCTIONS_H
#define LEXANALYZER_FUNCTIONS_H

#endif //LEXANALYZER_FUNCTIONS_H

//
// Created by Alpaca on 2021/10/4.
//
#include <iostream>

enum WordType{unknown=0,keyWord = 1,symbol=2,number=3,letter=4,blank=5,nl=6};


bool isNum(std::string);

bool isBlank(std::string);

bool isLetter(std::string);

int isSymbol(std::string);

int isKeyWord(std::string);

bool isNewLine(std::string);

bool isComment(std::string);

bool isPrefix(std::string);

bool isSemicolon(std::string);

bool isBrackets(std::string);

WordType JudgeWordType(std::string);

void errorRecover(int*,std::string[]);

int isMultiSym(std::string);

std::string identifierConnect(std::string, std::string);