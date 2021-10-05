//todo 行数统计 括号检测 不合法的字符是否需要统计

#include <fstream>
#include "functions.h"

int main() {
    std::string code[5000] = {};
    char tempch;
    int i = 0;
    int NumOfLines = 1;
    int NumOfChars = 0;
    int length = 0;
    std::string identifiers[1000];

    //将代码读入程序中
   std::ifstream codeFile("/Users/alpaca/Desktop/test.c");
   if(!codeFile.is_open()){
       std::cout << "代码文件打开失败！"<< std::endl;
   }

   while(codeFile.peek() != EOF){
       codeFile.get(tempch);
       code[i] = tempch;
       i++;
       length++;
   }
    codeFile.close();
    code[i] = '\0';

    for(i = 0;i<length;i++){
        std::string temp = "";
        switch (JudgeWordType(code[i])) {
            case number: {
                bool dotFlag = true;
                while (isNum(code[i]) || (code[i] == "." && dotFlag)) {
                    NumOfChars++;
                    if(code[i] == ".")
                        dotFlag = false;
                    temp += code[i];
                    i++;
                }

                if (!(isBlank(code[i]) || isSemicolon(code[i]) || isNewLine(code[i]))) {
                    std::cout << "发现错误，位置在第" << NumOfLines << "行,常数格式错误" << std::endl;
                    errorRecover(&i,code);
                    i--;
                    break;
                }
                std::cout << "(" << temp << ",常数)" <<std::endl;
                i--;
                break;
            }
            case letter:{
                int tmp;
                while(isLetter(code[i]) || isNum(code[i])){
                    NumOfChars++;
                    temp += code[i];
                    i++;
                }
                if(tmp = isKeyWord(temp)){
                    std::cout << "(" << temp << "," << tmp << ")" << std::endl;
                }
                else
                    std::cout << "(" << temp << ",变量)" <<std::endl;
                i--;
                break;
            }

            case symbol: {
                int tmp;
                NumOfChars++;
                temp += code[i];
                tmp = isSymbol(code[i]);

                if(i+1<length-1 && tmp &&  isSymbol(code[i+1])  && !isBrackets(code[i])){
                    temp += code[i+1];
                    NumOfChars++;
                    //注释处理逻辑
                    if(temp == "//"){
                        while((code[i++] != "\n") && i<length)
                            NumOfChars++;
                        i--;
                        break;
                    }

                    if(isPrefix(code[i])) {
                        if(tmp = isMultiSym(temp)){
                            std::cout << "(" << temp << "," << tmp << ")" << std::endl;
                            i++;
                            break;
                        }
                        else if(isBrackets(code[i+1]) || code[i+1] == "/"){
                            std::cout << "(" << code[i] << "," << isSymbol(code[i]) << ")" << std::endl;
                            break;
                        }
                        else {
                            std::cout << "分隔符：" << temp << "不合法" << std::endl;
                            errorRecover(&i,code);
                            break;
                        }
                    }
                    else if(isBrackets(code[i+1]) || isSemicolon(code[i+1]) || code[i+1] == "/"){
                        std::cout << "(" << code[i] << "," << isSymbol(code[i]) << ")" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "分隔符：" << temp << "不合法" << std::endl;
                        errorRecover(&i,code);
                        break;
                    }
                }
                else{
                    std::cout << "(" << temp << "," << tmp << ")" << std::endl;
                    break;
                }
            }

            case blank:
                break;
            case nl:
                NumOfLines++;
                break;
            default:
                if(code[i] == "\0")
                    break;
                else
                    std::cout << "发现错误，位置在第" << NumOfLines << "行,未知字符" << code[i] <<std::endl;
        }
    }

    std::cout << "分析完毕，一共有"<<NumOfLines<<"行。\n有"<<NumOfChars<<"个字符";

    return 0;
}



