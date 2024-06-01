//
// Created by icelake on 24-5-29.
//

#ifndef ROBIN_SEMA_H
#define ROBIN_SEMA_H

#include "stmtspace.h"
#include "exprspace.h"
#include "../common.h"
#include "../ast/production.h"
#include "../ast/symboltable.h"


namespace sema {
    class Sema {
    public:

        SharedPtr<production::Production> program;
        List<String> irCode;
        ast::SymTab top;
        Stack<StmtSpace> codeStmtSpace;
        Stack<ExprSpace> codeExprSpace;

        explicit Sema(SharedPtr<production::Production> program);

        static String genT();

        List<String> generateIRCODE();

    };
}

#endif //ROBIN_SEMA_H
