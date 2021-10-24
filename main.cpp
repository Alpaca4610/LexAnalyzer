#include <fstream>
#include "functions.h"

int main() {
    std::string code[5000] = {};
    char tempch;
    int i = 0;
    int NumOfLines_ = 1;
    int NumOfLines = 0;
    int NumOfChars = 0;
    int length = 0;
    int numOfNum = 0;
    int numOfKeyword = 0;
    int numOfIdentifiers = 0;
    int numOfOperator = 0;
    int numOfBound_word = 0;

    //将代码读入程序中
    std::ifstream codeFile("/Users/alpaca/Desktop/test.c");
    if (!codeFile.is_open()) {
        std::cout << "代码文件打开失败！" << std::endl;
    }

    //逐个读取源文件的字符存入数组中等待分析
    while (codeFile.peek() != EOF) {
        codeFile.get(tempch);
        code[i] = tempch;
        if (code[i] == "\n")
            NumOfLines_++;
        i++;
        length++;
    }
    codeFile.close();
    code[i] = "EOF";

    //开始词法分析
    for (i = 0; i < length + 1; i++) {
        std::string temp = "";
        switch (JudgeWordType(code[i])) {
            //若读入字符为数字
            case number: {
                bool dotFlag = true;
                bool EFlag = true;

                //常数有小数型和科学计数法型，下面的代码可以识别
                while (isNum(code[i]) || (code[i] == "." && dotFlag) || (code[i] == "E" && EFlag)) {
                    if (code[i] == ".") {
                        dotFlag = false;
                        numOfBound_word++;
                    }
                    if (code[i] == "E") {
                        EFlag = false;
                        if (code[i + 1] == "+" || code[i + 1] == "-" || isNum(code[i + 1])) {
                            temp += "E";
                            i++;
                        } else {
                            break;
                        }
                    }
                    temp += code[i];
                    i++;
                }

                //常数格式不正确，输出错误信息并跳过错误
                if (!(isBlank(code[i]) || isSemicolon(code[i]) || isNewLine(code[i]) || isSymbol(code[i]))) {
                    std::cout << "发现错误，位置在第" << NumOfLines + 1 << "行,常数格式错误" << std::endl;
                    errorRecover(&i, code);
                    i--;
                    break;
                }

                //输出常数信息
                std::cout << "(" << temp << ",64)" << std::endl;
                numOfNum++;
                i--;
                break;
            }

                //若读入字符为英文字母
            case letter: {
                int tmp;
                //标识符拼接
                while (isLetter(code[i]) || isNum(code[i])) {
                    NumOfChars++;
                    temp += code[i];
                    i++;
                }

                //判断拼接完成的标识符是否为C语言关键字
                if (tmp = isKeyWord(temp)) {
                    std::cout << "(" << temp << "," << tmp << ")" << std::endl;
                    numOfKeyword++;
                }
                    //若不是，当作变量处理
                else {
                    std::cout << "(" << temp << ",63)" << std::endl;
                    numOfIdentifiers++;
                }
                i--;
                break;
            }

                //若当前读入的字符为Symbol类型（分隔符与运算符）
            case symbol: {
                int tmp;
                temp += code[i];

                //对于symbol类型可能会出现有两个操作符组成的复合操作符，一次提前读入两个字符，然后做出相应判断
                if (i + 1 < length - 1 && isSymbol(code[i]) && isSymbol(code[i + 1])) {
                    temp += code[i + 1];
                    //注释处理逻辑
                    if (temp == "//") {
                        while ((code[i++] != "\n") && i < length) {}
                        i--;
                        break;
                    }
                    if (temp == "/*") {
                        i += 2;
                        while (!(code[i] == "*" && code[i + 1] == "/") && !isNewLine(code[i + 1]) && i < length) {
                            i++;
                        }
                        i++;
                        break;
                    }

                    //判断第一个字符是否为复合运算符的前缀
                    if (isPrefix(code[i])) {
                        //复合运算符处理逻辑
                        if (tmp = isMultiSym(temp)) {
                            std::cout << "(" << temp << "," << tmp << ")" << std::endl;
                            numOfOperator++;
                            i++;
                            break;
                        }
                    }

                        //若不为双目运算符，则当成普通symbol处理
                    else {
                        //处理分隔符
                        if (tmp = isBound(code[i])) {
                            std::cout << "(" << code[i] << "," << tmp << ")" << std::endl;
                            numOfBound_word++;
                        }
                            //处理运算符
                        else {
                            std::cout << "(" << code[i] << "," << isSymbol(code[i]) << ")" << std::endl;
                            numOfOperator++;
                        }
                        break;
                    }
                } else {
                    //处理分隔符
                    if (tmp = isBound(code[i])) {
                        std::cout << "(" << code[i] << "," << tmp << ")" << std::endl;
                        numOfBound_word++;
                    }
                        //处理单目运算符
                    else {
                        std::cout << "(" << code[i] << "," << isSymbol(code[i]) << ")" << std::endl;
                        numOfOperator++;
                    }
                    break;
                }
            }
                //若读入的字符为空格，则跳过
            case blank:
                break;
                //若读入的字符为换行符，给行数+1，注：该行数变量用于指出错误发生的行数
            case nl:
                NumOfLines++;
                break;
                //若词法分析进行到代码末尾，则结束循环
            case eof:
                NumOfLines++;
                break;
                //若读入字符为未知字符，则跳过该字符并报错
            default:
                std::cout << "发现错误，位置在第" << NumOfLines + 1 << "行,未知字符" << code[i] << std::endl;
        }
    }

    std::cout << "分析完毕，一共有" << NumOfLines_ << "行。\n有" << length << "个字符（包含空格和换行符）";
    std::cout << "有" << numOfOperator << "个操作符" << "," << numOfBound_word << "个分隔符" << "," << numOfIdentifiers
              << "个id" << "," << numOfKeyword << "个关键字" << "," << numOfNum << "个常量";

    return 0;
}
