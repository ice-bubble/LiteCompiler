//
// Created by icelake on 24-5-29.
//

#include "sema.h"
#include "../error/error.h"

namespace sema {

    Sema::Sema(SharedPtr<production::Production> program) : program(std::move(program)) { top = new ast::SymTab; }

    Sema::~Sema() { delete top; }

    String Sema::genT() {
        static int Tindex = 0;
        return fmt::format("T{}", Tindex++);
    }

    List<String> Sema::generateIRCODE() {
        program->visit(this);
        fmt::print("\nvisit all productions\n");
        return irCode;
    }

    String stringMul(String left, String right, Sema *semaAna) {
        long intLeft;
        bool signLeft = false;
        try {
            intLeft = std::stol(left);
            signLeft = true;
        }
        catch (const std::invalid_argument &e) {
        }
        catch (const std::out_of_range &e) {
            reportSemanticError(0, "a integer variable is out of range");
        }
        long intRight;
        bool signRight = false;
        try {
            intRight = std::stol(right);
            signRight = true;
        }
        catch (const std::invalid_argument &e) {
        }
        catch (const std::out_of_range &e) {
            reportSemanticError(0, "a integer variable is out of range");
        }
        if (signLeft && signRight) return std::to_string(intLeft * intRight);
        String tmpT = Sema::genT();
        semaAna->irCode.emplace_back(fmt::format("{}={}*{}", tmpT, left, right));
        return tmpT;
    }

    String stringPlus(String left, String right, Sema *semaAna) {
        long intLeft;
        bool signLeft = false;
        try {
            intLeft = std::stol(left);
            signLeft = true;
        }
        catch (const std::invalid_argument &e) {
        }
        catch (const std::out_of_range &e) {
            reportSemanticError(0, "a integer variable is out of range");
        }
        long intRight;
        bool signRight = false;
        try {
            intRight = std::stol(right);
            signRight = true;
        }
        catch (const std::invalid_argument &e) {
        }
        catch (const std::out_of_range &e) {
            reportSemanticError(0, "a integer variable is out of range");
        }
        if (signLeft && signRight) return std::to_string(intLeft + intRight);
        String tmpT = Sema::genT();
        semaAna->irCode.emplace_back(fmt::format("{}={}+{}", tmpT, left, right));
        return tmpT;

    }
}
