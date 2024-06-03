//
// Created by icelake on 24-5-29.
//

#ifndef ROBIN_SEMA_H
#define ROBIN_SEMA_H

#include "../common.h"
#include "../ast/symboltable.h"

//前向定义
namespace production{
    class Production;
}

namespace sema {
    class Sema {
    public:

        SharedPtr<production::Production> program;
        List<String> irCode;
        ast::SymTab *top;

        explicit Sema(SharedPtr<production::Production> program);

        static String genT();

        List<String> generateIRCODE();

    };

    String stringMul(String left, String right, Sema *semaAna);

    String stringPlus(String left, String right, Sema *semaAna);
}

#endif //ROBIN_SEMA_H
