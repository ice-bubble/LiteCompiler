#ifndef ROBIN_SEMA_H
#define ROBIN_SEMA_H

#include "../common.h"
#include "../ast/symboltable.h"

//前向定义
namespace production {
    class Production;
}

namespace sema {
    class Sema {
    public:

        SharedPtr<production::Production> program;    ///< 源程序语法树的树根结点
        List<String> irCode;                          ///< 存储中间代码的列表
        ast::SymTab *top;                             ///< 源程序的全局符号表

        explicit Sema(SharedPtr<production::Production> program);

        ~Sema();

        static String genT();

        /**
         * @brief 生成中间代码
         * @return 中间代码列表，每一项都是一行代码
         */
        List<String> generateIRCODE();

    };

    /**
     * @param left 变量1
     * @param right 变量2
     * @param semaAna 当前的语义分析器
     * @brief 对于输入的两个变量进行乘法运算
     * @return 运行的结果
     */
    String stringMul(String left, String right, Sema *semaAna);

    /**
     * @param left 变量1
     * @param right 变量2
     * @param semaAna 当前的语义分析器
     * @brief 对于输入的两个变量进行加法运算
     * @return 运行的结果
     */
    String stringPlus(String left, String right, Sema *semaAna);
}

#endif //ROBIN_SEMA_H
