//
// Created by icelake on 24-5-30.
//

#include "production.h"
#include "codespace.h"
#include "../error/error.h"
#include "../debug/debug.h"

namespace production {

    void S::visit(sema::Sema *semaAna) {
        program->visit(semaAna);
    }

    void Program::visit(sema::Sema *semaAna) {
        declarations->visit(semaAna);
    }

    void Declarations::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Declarations1::visit(sema::Sema *semaAna) {
        declaration->code1Jmp = code1Jmp;
        declaration->nextJmp = nextJmp;
        declarations->code1Jmp = code1Jmp;
        declarations->nextJmp = nextJmp;
        declaration->visit(semaAna);
        declarations->visit(semaAna);
        returnType = ast::Type::chooseReturnType(declaration->returnType, declarations->returnType, line);
    }

    void Declarations2::visit(sema::Sema *semaAna) {
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::BASE_);
    }

    void Declaration::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Declaration1::visit(sema::Sema *semaAna) {
        funDecl->visit(semaAna);
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::BASE_);
    }

    void Declaration2::visit(sema::Sema *semaAna) {
        varDecl->visit(semaAna);
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::BASE_);
    }

    void Declaration3::visit(sema::Sema *semaAna) {
        statement->code1Jmp = code1Jmp;
        statement->nextJmp = nextJmp;
        statement->visit(semaAna);
        returnType = statement->returnType;
    }

    void Statement::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Statement1::visit(sema::Sema *semaAna) {
        breakStmt->nextJmp = nextJmp;
        breakStmt->visit(semaAna);
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::BASE_);
    }

    void Statement2::visit(sema::Sema *semaAna) {
        continueStmt->code1Jmp = code1Jmp;
        continueStmt->visit(semaAna);
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::BASE_);
    }

    void Statement3::visit(sema::Sema *semaAna) {
        returnStmt->visit(semaAna);
        returnType = returnStmt->returnType;
    }

    void Statement4::visit(sema::Sema *semaAna) {
        exprStmt->visit(semaAna);
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::BASE_);
    }

    void Statement5::visit(sema::Sema *semaAna) {
        ifStmt->code1Jmp = code1Jmp;
        ifStmt->nextJmp = nextJmp;
        ifStmt->visit(semaAna);
        returnType = ifStmt->returnType;
    }

    void Statement6::visit(sema::Sema *semaAna) {
        whileStmt->visit(semaAna);
        returnType = whileStmt->returnType;
    }

    void Statement7::visit(sema::Sema *semaAna) {
        repeatStmt->visit(semaAna);
        returnType = repeatStmt->returnType;
    }

    void Statement8::visit(sema::Sema *semaAna) {
        block->code1Jmp = code1Jmp;
        block->nextJmp = nextJmp;
        block->visit(semaAna);
        returnType = block->returnType;
    }

    void Statement9::visit(sema::Sema *semaAna) {
        forStmt->visit(semaAna);
        returnType = forStmt->returnType;
    }

    void BreakStmt::visit(sema::Sema *semaAna) {
        if (nextJmp == nullptr) return reportSemanticError(line, "the breakStmt is not in a loop");
        semaAna->irCode.emplace_back("goto {}");
        nextJmp->push_back(semaAna->irCode.size() - 1);
    }

    void ContinueStmt::visit(sema::Sema *semaAna) {
        if (code1Jmp == nullptr) return reportSemanticError(line, "the continueStmt is not in a loop");
        semaAna->irCode.emplace_back("goto {}");
        code1Jmp->push_back(semaAna->irCode.size() - 1);
    }

    void ReturnStmt::visit(sema::Sema *semaAna) {
        exprStmt->visit(semaAna);
        semaAna->irCode.emplace_back(fmt::format("return {}", exprStmt->val));
        returnType = exprStmt->returnType;
    }

    void FunDecl::visit(sema::Sema *semaAna) {
        id = token_IDENTIFIER->toString();
        semaAna->irCode.emplace_back(fmt::format("{}:", id));
        SharedPtr<ast::Type> thisType = std::make_shared<ast::Type>(ast::IdentifierType::FUNC_);
        if (!semaAna->top->insert(id, thisType, thisType->width)) {
            reportSemanticError(line, fmt::format("the variable '{}' is exist in symbol table", id));
        }

        thisFun = semaAna->top->lookup(id);
        if (thisFun == nullptr) return reportSemanticError(line, "the fun can't find itself in the symbol table");
        paramList->thisFun = thisFun;

        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");

        paramList->visit(semaAna);
        block->visit(semaAna);
        returnType = block->returnType;
        if (returnType->selfType == ast::IdentifierType::BASE_)
            returnType = std::make_shared<ast::Type>(ast::IdentifierType::NIL_);
        if (returnType->selfType == ast::IdentifierType::VAR_)
            reportSemanticError(line, "invalid return type for the function");
        if (!semaAna->top->changeReturnType(id, returnType)) {
            reportSemanticError(line, "invalid function definition");
        }
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        semaAna->irCode.push_back(fmt::format("{} end", id));
    }

    void VarDecl::visit(sema::Sema *semaAna) {
        type->visit(semaAna);

        varDef->type = type->type;
        varDef->width = type->width;
        varDef->visit(semaAna);

        varDefs->type = type->type;
        varDefs->width = type->width;
        varDefs->visit(semaAna);
    }

    void VarDef::visit(sema::Sema *semaAna) {
        var->usage = Usage::define;
        var->t = type;
        var->w = width;
        var->visit(semaAna);
        varInit->visit(semaAna);
        if (!varInit->val.empty()) {
            String tmpT = autoConversion(varInit->val, varInit->type->selfType,
                                         var->type->selfType, line, semaAna);
            semaAna->irCode.emplace_back(fmt::format("{}={}", var->id, tmpT));
            if (var->type->selfType == ast::IdentifierType::VAR_) {
                var->type = std::make_shared<ast::Type>(varInit->type->selfType);
            }
        }
    }

    void VarDefs::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void VarDefs1::visit(sema::Sema *semaAna) {
        varDef->type = type;
        varDef->width = width;
        varDef->visit(semaAna);
        varDefs->type = type;
        varDefs->width = width;
        varDefs->visit(semaAna);
    }

    void VarDefs2::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void VarInit::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void VarInit1::visit(sema::Sema *semaAna) {
        expression->visit(semaAna);
        val = expression->val;
        type = expression->type;
    }

    void VarInit2::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Type::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Type1::visit(sema::Sema *semaAna) {
        type = std::make_shared<ast::Type>(ast::IdentifierType::INT_);
        width = type->width;
    }

    void Type2::visit(sema::Sema *semaAna) {
        type = std::make_shared<ast::Type>(ast::IdentifierType::REAL_);
        width = type->width;
    }

    void Type3::visit(sema::Sema *semaAna) {
        type = std::make_shared<ast::Type>(ast::IdentifierType::STRING_);
        width = type->width;
    }

    void Type4::visit(sema::Sema *semaAna) {
        type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
        width = type->width;
    }

    void Type5::visit(sema::Sema *semaAna) {
        type = std::make_shared<ast::Type>(ast::IdentifierType::CHAR_);
        width = type->width;
    }

    void Type6::visit(sema::Sema *semaAna) {
        type = std::make_shared<ast::Type>(ast::IdentifierType::VAR_);
        width = type->width;
    }

    void ExprStmt::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void ExprStmt1::visit(sema::Sema *semaAna) {

        expression->jmp = jmp;
        expression->trueJmp = trueJmp;
        expression->falseJmp = falseJmp;
        expression->visit(semaAna);
        val = expression->val;
        type = expression->type;
        returnType = expression->type;
    }

    void ExprStmt2::visit(sema::Sema *semaAna) {
        if (jmp) {
            semaAna->irCode.emplace_back("goto {}");
            trueJmp->push_back(semaAna->irCode.size() - 1);
        }
        val = "true";
        type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::NIL_);
    }

    void IfStmt::visit(sema::Sema *semaAna) {
        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        ast::CodeSpace thisSpace(&(semaAna->irCode));
        expression->jmp = true;
        expression->trueJmp = &(thisSpace.code1Sentences);
        expression->falseJmp = &(thisSpace.code2Sentences);

        expression->visit(semaAna);

        thisSpace.code1 = static_cast<int>(semaAna->irCode.size());
        statement->code1Jmp = code1Jmp;
        statement->nextJmp = nextJmp;

        statement->visit(semaAna);

        semaAna->irCode.emplace_back("goto {}");
        thisSpace.nextSentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.code2 = static_cast<int>(semaAna->irCode.size());
        elseBranch->code1Jmp = code1Jmp;
        elseBranch->nextJmp = nextJmp;

        elseBranch->visit(semaAna);

        returnType = ast::Type::chooseReturnType(statement->returnType, elseBranch->returnType, line);
        if (elseBranch->ifExist) {
            semaAna->irCode.emplace_back("goto {}");
            thisSpace.nextSentences.push_back(semaAna->irCode.size() - 1);
        }
        thisSpace.next = static_cast<int>(semaAna->irCode.size());
        thisSpace.backpatch();
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
    }

    void ElseBranch::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void ElseBranch1::visit(sema::Sema *semaAna) {
        ifExist = true;
        statement->code1Jmp = code1Jmp;
        statement->nextJmp = nextJmp;

        statement->visit(semaAna);

        returnType = statement->returnType;
    }

    void ElseBranch2::visit(sema::Sema *semaAna) {
        returnType = std::make_shared<ast::Type>(ast::IdentifierType::BASE_);
    }

    void WhileStmt::visit(sema::Sema *semaAna) {
        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        ast::CodeSpace thisSpace(&(semaAna->irCode));
        thisSpace.compare = static_cast<int>(semaAna->irCode.size());
        thisSpace.code1 = static_cast<int>(semaAna->irCode.size());
        expression->jmp = true;
        expression->trueJmp = &(thisSpace.code2Sentences);
        expression->falseJmp = &(thisSpace.nextSentences);

        expression->visit(semaAna);

        thisSpace.code2 = static_cast<int>(semaAna->irCode.size());
        statement->code1Jmp = &(thisSpace.code1Sentences);
        statement->nextJmp = &(thisSpace.nextSentences);

        statement->visit(semaAna);

        returnType = statement->returnType;
        semaAna->irCode.emplace_back("goto {}");
        thisSpace.compareSentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.next = static_cast<int>(semaAna->irCode.size());
        thisSpace.backpatch();
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
    }

    void ForStmt::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void ForStmt1::visit(sema::Sema *semaAna) {
        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        ast::CodeSpace thisSpace(&(semaAna->irCode));

        varDecl->visit(semaAna);

        thisSpace.compare = static_cast<int>(semaAna->irCode.size());
        thisSpace.code1 = static_cast<int>(semaAna->irCode.size());
        exprStmt->jmp = true;
        exprStmt->trueJmp = &(thisSpace.code2Sentences);
        exprStmt->falseJmp = &(thisSpace.nextSentences);

        exprStmt->visit(semaAna);

        thisSpace.code2 = static_cast<int>(semaAna->irCode.size());
        statement->code1Jmp = &(thisSpace.code1Sentences);
        statement->nextJmp = &(thisSpace.nextSentences);

        statement->visit(semaAna);

        returnType = statement->returnType;
        semaAna->irCode.emplace_back("goto {}");
        thisSpace.code1Sentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.next = static_cast<int>(semaAna->irCode.size());
        thisSpace.backpatch();
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
    }

    void ForStmt2::visit(sema::Sema *semaAna) {
        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        ast::CodeSpace thisSpace(&(semaAna->irCode));

        varDecl->visit(semaAna);

        thisSpace.compare = static_cast<int>(semaAna->irCode.size());
        exprStmt->jmp = true;
        exprStmt->trueJmp = &(thisSpace.code2Sentences);
        exprStmt->falseJmp = &(thisSpace.nextSentences);

        exprStmt->visit(semaAna);

        thisSpace.code1 = static_cast<int>(semaAna->irCode.size());

        expression->visit(semaAna);

        semaAna->irCode.emplace_back("goto {}");
        thisSpace.compareSentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.code2 = static_cast<int>(semaAna->irCode.size());
        statement->code1Jmp = &(thisSpace.code1Sentences);
        statement->nextJmp = &(thisSpace.nextSentences);

        statement->visit(semaAna);

        returnType = statement->returnType;
        semaAna->irCode.emplace_back("goto {}");
        thisSpace.code1Sentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.next = static_cast<int>(semaAna->irCode.size());
        thisSpace.backpatch();
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
    }

    void ForStmt3::visit(sema::Sema *semaAna) {
        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        ast::CodeSpace thisSpace(&(semaAna->irCode));

        exprStmt1->visit(semaAna);

        thisSpace.compare = static_cast<int>(semaAna->irCode.size());
        thisSpace.code1 = static_cast<int>(semaAna->irCode.size());
        exprStmt2->jmp = true;
        exprStmt2->trueJmp = &(thisSpace.code2Sentences);
        exprStmt2->falseJmp = &(thisSpace.nextSentences);

        exprStmt2->visit(semaAna);

        thisSpace.code2 = static_cast<int>(semaAna->irCode.size());
        statement->code1Jmp = &(thisSpace.code1Sentences);
        statement->nextJmp = &(thisSpace.nextSentences);

        statement->visit(semaAna);

        returnType = statement->returnType;
        semaAna->irCode.emplace_back("goto {}");
        thisSpace.code1Sentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.next = static_cast<int>(semaAna->irCode.size());
        thisSpace.backpatch();
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
    }

    void ForStmt4::visit(sema::Sema *semaAna) {
        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        ast::CodeSpace thisSpace(&(semaAna->irCode));

        exprStmt1->visit(semaAna);

        thisSpace.compare = static_cast<int>(semaAna->irCode.size());
        exprStmt2->jmp = true;
        exprStmt2->trueJmp = &(thisSpace.code2Sentences);
        exprStmt2->falseJmp = &(thisSpace.nextSentences);

        exprStmt2->visit(semaAna);

        thisSpace.code1 = static_cast<int>(semaAna->irCode.size());

        expression->visit(semaAna);

        semaAna->irCode.emplace_back("goto {}");
        thisSpace.compareSentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.code2 = static_cast<int>(semaAna->irCode.size());
        statement->code1Jmp = &(thisSpace.code1Sentences);
        statement->nextJmp = &(thisSpace.nextSentences);

        statement->visit(semaAna);

        returnType = statement->returnType;
        semaAna->irCode.emplace_back("goto {}");
        thisSpace.code1Sentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.next = static_cast<int>(semaAna->irCode.size());
        thisSpace.backpatch();
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
    }

    void Block::visit(sema::Sema *semaAna) {
        declarations->code1Jmp = code1Jmp;
        declarations->nextJmp = nextJmp;
        declarations->visit(semaAna);
        returnType = declarations->returnType;
    }

    void RepeatStmt::visit(sema::Sema *semaAna) {
        semaAna->top = ast::SymTab::genNewSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
        ast::CodeSpace thisSpace(&(semaAna->irCode));
        thisSpace.code2 = static_cast<int>(semaAna->irCode.size());
        statement->code1Jmp = &(thisSpace.code1Sentences);
        statement->nextJmp = &(thisSpace.nextSentences);

        statement->visit(semaAna);

        returnType = statement->returnType;
        semaAna->irCode.emplace_back("goto {}");
        thisSpace.compareSentences.push_back(semaAna->irCode.size() - 1);
        thisSpace.compare = static_cast<int>(semaAna->irCode.size());
        thisSpace.code1 = static_cast<int>(semaAna->irCode.size());
        expression->jmp = true;
        expression->trueJmp = &(thisSpace.nextSentences);
        expression->falseJmp = &(thisSpace.code2Sentences);

        expression->visit(semaAna);

        thisSpace.next = static_cast<int>(semaAna->irCode.size());
        thisSpace.backpatch();
        semaAna->top = ast::SymTab::throwThisSymTab(semaAna->top);
        if (semaAna->top == nullptr) reportSemanticError(line, "invalid symbol table");
    }

    void ParamList::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void ParamList1::visit(sema::Sema *semaAna) {
        parameter->thisFun = thisFun;
        parameters->thisFun = thisFun;
        parameter->visit(semaAna);
        parameters->visit(semaAna);
    }

    void ParamList2::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Parameters::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Parameters1::visit(sema::Sema *semaAna) {
        parameter->thisFun = thisFun;
        parameters->thisFun = thisFun;
        parameter->visit(semaAna);
        parameters->visit(semaAna);
    }

    void Parameters2::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Parameter::visit(sema::Sema *semaAna) {
        type->visit(semaAna);

        var->usage = Usage::define;
        var->t = type->type;
        var->w = type->width;
        thisFun->paramCount += 1;

        var->visit(semaAna);

        thisFun->params.push_back(var->type);
    }

    void Expression::visit(sema::Sema *semaAna) {
        assignment->jmp = jmp;
        assignment->trueJmp = trueJmp;
        assignment->falseJmp = falseJmp;

        assignment->visit(semaAna);

        val = assignment->val;
        type = assignment->type;
    }

    void Assignment::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Assignment1::visit(sema::Sema *semaAna) {
        var->visit(semaAna);
        assignment->visit(semaAna);

        String tmpT = autoConversion(assignment->val, assignment->type->selfType,
                                     var->type->selfType, line, semaAna);
        semaAna->irCode.emplace_back(fmt::format("{}={}", var->val, tmpT));
        val = var->val;
        type = var->type;
        if (jmp) {
            semaAna->irCode.emplace_back("if " + var->val + " goto {}");
            trueJmp->push_back(semaAna->irCode.size() - 1);
            semaAna->irCode.emplace_back("goto {}");
            falseJmp->push_back(semaAna->irCode.size() - 1);
        }
    }

    void Assignment2::visit(sema::Sema *semaAna) {
        logic_or->jmp = jmp;
        logic_or->trueJmp = trueJmp;
        logic_or->falseJmp = falseJmp;

        logic_or->visit(semaAna);

        val = logic_or->val;
        type = logic_or->type;
    }

    void Logic_or::visit(sema::Sema *semaAna) {
        ast::CodeSpace thisSpace(&(semaAna->irCode));
        logic_and->jmp = jmp;
        logic_and->trueJmp = trueJmp;
        logic_and->falseJmp = &(thisSpace.rightSentences);
        logic_or_prime->jmp = jmp;
        logic_or_prime->trueJmp = trueJmp;
        logic_or_prime->falseJmp = falseJmp;

        logic_and->visit(semaAna);

        thisSpace.right = static_cast<int>(semaAna->irCode.size());

        logic_or_prime->visit(semaAna);

        if (logic_or_prime->op == "||") {
            if (jmp) {
                val = "true";
            } else {
                auto resultPair = autoConversion(logic_and->val, logic_and->type->selfType,
                                                 logic_or_prime->val, logic_or_prime->type->selfType,
                                                 logic_or_prime->op, line, semaAna);
                val = resultPair.first;
            }
            type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
        } else {
            val = logic_and->val;
            type = logic_and->type;
            if (jmp) {
                mergeUniqueIntoA(falseJmp, &(thisSpace.rightSentences));
                thisSpace.rightSentences.clear();
            }
        }

        thisSpace.backpatch();
    }

    void Logic_or_prime::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Logic_or_prime1::visit(sema::Sema *semaAna) {
        logic_or->jmp = jmp;
        logic_or->trueJmp = trueJmp;
        logic_or->falseJmp = falseJmp;

        logic_or->visit(semaAna);

        op = "||";
        val = logic_or->val;
        type = logic_or->type;
    }

    void Logic_or_prime2::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Logic_and::visit(sema::Sema *semaAna) {
        ast::CodeSpace thisSpace(&(semaAna->irCode));
        logic_and_prime->jmp = jmp;
        logic_and_prime->trueJmp = trueJmp;
        logic_and_prime->falseJmp = falseJmp;

        equality->visit(semaAna);

        if (jmp) {
            semaAna->irCode.emplace_back("if " + equality->val + " goto {}");
            thisSpace.rightSentences.push_back(semaAna->irCode.size() - 1);
            semaAna->irCode.emplace_back("goto {}");
            falseJmp->push_back(semaAna->irCode.size() - 1);
        }
        thisSpace.right = static_cast<int>(semaAna->irCode.size());

        logic_and_prime->visit(semaAna);

        if (logic_and_prime->op == "&&") {
            if (jmp) {
                val = "true";
            } else {
                auto resultPair = autoConversion(equality->val, equality->type->selfType,
                                                 logic_and_prime->val, logic_and_prime->type->selfType,
                                                 logic_and_prime->op, line, semaAna);
                val = resultPair.first;
            }
            type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
        } else {
            val = equality->val;
            type = equality->type;
            if (jmp) {
                mergeUniqueIntoA(trueJmp, &(thisSpace.rightSentences));
                thisSpace.rightSentences.clear();
            }
        }
        thisSpace.backpatch();
    }

    void Logic_and_prime::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Logic_and_prime1::visit(sema::Sema *semaAna) {
        logic_and->jmp = jmp;
        logic_and->trueJmp = trueJmp;
        logic_and->falseJmp = falseJmp;

        logic_and->visit(semaAna);

        op = "&&";
        val = logic_and->val;
        type = logic_and->type;
    }

    void Logic_and_prime2::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Equality::visit(sema::Sema *semaAna) {
        comparison->visit(semaAna);

        equality_prime->visit(semaAna);

        if (equality_prime->op == "!=" || equality_prime->op == "==") {
            auto resultPair = autoConversion(comparison->val, comparison->type->selfType,
                                             equality_prime->val, equality_prime->type->selfType,
                                             equality_prime->op, line, semaAna);
            val = resultPair.first;
            type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
        } else {
            val = comparison->val;
            type = comparison->type;
        }
    }

    void Equality_prime::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Equality_prime1::visit(sema::Sema *semaAna) {
        equality->visit(semaAna);

        op = "!=";
        val = equality->val;
        type = equality->type;
    }

    void Equality_prime2::visit(sema::Sema *semaAna) {
        equality->visit(semaAna);

        op = "==";
        val = equality->val;
        type = equality->type;
    }

    void Equality_prime3::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Comparison::visit(sema::Sema *semaAna) {
        term->visit(semaAna);

        comparison_prime->visit(semaAna);

        if (comparison_prime->op == ">" || comparison_prime->op == ">=" || comparison_prime->op == "<" ||
            comparison_prime->op == "<=") {
            auto resultPair = autoConversion(term->val, term->type->selfType,
                                             comparison_prime->val, comparison_prime->type->selfType,
                                             comparison_prime->op, line, semaAna);
            val = resultPair.first;
            type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
        } else {
            val = term->val;
            type = term->type;
        }
    }

    void Comparison_prime::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Comparison_prime1::visit(sema::Sema *semaAna) {
        comparison->visit(semaAna);

        op = ">";
        val = comparison->val;
        type = comparison->type;
    }

    void Comparison_prime2::visit(sema::Sema *semaAna) {
        comparison->visit(semaAna);

        op = ">=";
        val = comparison->val;
        type = comparison->type;
    }

    void Comparison_prime3::visit(sema::Sema *semaAna) {
        comparison->visit(semaAna);

        op = "<";
        val = comparison->val;
        type = comparison->type;
    }

    void Comparison_prime4::visit(sema::Sema *semaAna) {
        comparison->visit(semaAna);

        op = "<=";
        val = comparison->val;
        type = comparison->type;
    }

    void Comparison_prime5::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Term::visit(sema::Sema *semaAna) {
        factor->visit(semaAna);

        term_prime->visit(semaAna);

        if (term_prime->op == "+" || term_prime->op == "-") {
            auto resultPair = autoConversion(factor->val, factor->type->selfType,
                                             term_prime->val, term_prime->type->selfType,
                                             term_prime->op, line, semaAna);
            val = resultPair.first;
            type = std::make_shared<ast::Type>(resultPair.second);
        } else {
            val = factor->val;
            type = factor->type;
        }
    }

    void Term_prime::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Term_prime1::visit(sema::Sema *semaAna) {
        term->visit(semaAna);

        op = "-";
        val = term->val;
        type = term->type;
    }

    void Term_prime2::visit(sema::Sema *semaAna) {
        term->visit(semaAna);

        op = "+";
        val = term->val;
        type = term->type;
    }

    void Term_prime3::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Factor::visit(sema::Sema *semaAna) {
        incr_exp->visit(semaAna);

        factor_prime->visit(semaAna);

        if (factor_prime->op == "/" || factor_prime->op == "*" || factor_prime->op == "%") {
            auto resultPair = autoConversion(incr_exp->val, incr_exp->type->selfType,
                                             factor_prime->val, factor_prime->type->selfType,
                                             factor_prime->op, line, semaAna);
            val = resultPair.first;
            type = std::make_shared<ast::Type>(resultPair.second);
        } else {
            val = incr_exp->val;
            type = incr_exp->type;
        }
    }

    void Factor_prime::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Factor_prime1::visit(sema::Sema *semaAna) {
        factor->visit(semaAna);

        op = "/";
        val = factor->val;
        type = factor->type;
    }

    void Factor_prime2::visit(sema::Sema *semaAna) {
        factor->visit(semaAna);

        op = "*";
        val = factor->val;
        type = factor->type;
    }

    void Factor_prime3::visit(sema::Sema *semaAna) {
        factor->visit(semaAna);

        op = "%";
        val = factor->val;
        type = factor->type;
    }

    void Factor_prime4::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void Incr_exp::visit(sema::Sema *semaAna) {
        unary->visit(semaAna);

        incr_op->visit(semaAna);

        if (!incr_op->ifUsed) {
            val = unary->val;
            type = unary->type;
        } else {
            String op = incr_op->val > 0 ? "+" : "-";
            String numStr = std::to_string(incr_op->val > 0 ? incr_op->val : -incr_op->val);
            auto resultPair = autoConversion(unary->val, unary->type->selfType,
                                             numStr, ast::IdentifierType::INT_, op, line, semaAna);
            val = unary->val;
            type = unary->type;
            if (val != resultPair.first) {
                if (type->selfType == ast::IdentifierType::INT_)
                    semaAna->irCode.emplace_back(fmt::format("{}={}", val, resultPair.first));
                else
                    semaAna->irCode.emplace_back(fmt::format("{}=({}){}",
                                                             val, ast::Type::typeToString[type->selfType],
                                                             resultPair.first));
            }

        }
    }

    void Incr_op::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Incr_op1::visit(sema::Sema *semaAna) {
        ifUsed = true;
        val = incr_op->val + 1;
    }

    void Incr_op2::visit(sema::Sema *semaAna) {
        ifUsed = true;
        val = incr_op->val - 1;
    }

    void Incr_op3::visit(sema::Sema *semaAna) {
        ifUsed = false;
    }

    void Unary::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Unary1::visit(sema::Sema *semaAna) {
        unary->visit(semaAna);

        String tmpT1 = autoConversion(unary->val, unary->type->selfType,
                                      ast::IdentifierType::BOOL_, line, semaAna);
        String tmpT2 = sema::Sema::genT();
        semaAna->irCode.emplace_back(fmt::format("{}=!{}", tmpT2, tmpT1));
        val = tmpT2;
        type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
    }

    void Unary2::visit(sema::Sema *semaAna) {
        unary->visit(semaAna);

        if (unary->type->selfType < ast::IdentifierType::INT_) {
            String tmpT1 = sema::Sema::genT();
            semaAna->irCode.emplace_back(fmt::format("{}=(integer){}", tmpT1, unary->val));
            String tmpT2 = sema::Sema::genT();
            semaAna->irCode.emplace_back(fmt::format("{}=-{}", tmpT2, tmpT1));
            val = tmpT2;
            type = std::make_shared<ast::Type>(ast::IdentifierType::INT_);
        } else {
            String tmpT1 = sema::Sema::genT();
            semaAna->irCode.emplace_back(fmt::format("{}=-{}", tmpT1, unary->val));
            val = tmpT1;
            type = unary->type;
        }
    }

    void Unary3::visit(sema::Sema *semaAna) {
        call->visit(semaAna);

        val = call->val;
        type = call->type;
    }

    void Call::visit(sema::Sema *semaAna) {
        primary->visit(semaAna);

        call_suffix->callee = primary->val;

        call_suffix->visit(semaAna);

        if (call_suffix->isExist) {
            val = call_suffix->val;
            type = call_suffix->type;
        } else {
            val = primary->val;
            type = primary->type;
        }
    }

    void Call_suffix::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Call_suffix1::visit(sema::Sema *semaAna) {
        auto calleeInTop = semaAna->top->lookup(callee);
        if (calleeInTop == nullptr) {
            return reportSemanticError(line, fmt::format("function '{}' is not define in symbol table", callee));
        }
        argList->calleeFun = calleeInTop;

        argList->visit(semaAna);

        if (argList->sum != calleeInTop->paramCount) {
            return reportSemanticError(line, fmt::format("the function '{}' expect {} params but get {} params",
                                                         callee, calleeInTop->paramCount, argList->sum));
        }
        String tmpT1 = sema::Sema::genT();
        semaAna->irCode.emplace_back(fmt::format("{}=call {},{}",
                                                 tmpT1, callee, std::to_string(argList->sum)));
        call_suffix->callee = tmpT1;

        call_suffix->visit(semaAna);

        isExist = true;
        type = std::make_shared<ast::Type>(calleeInTop->returnType);
        if (call_suffix->isExist) {
            val = call_suffix->val;
            type = call_suffix->type;
        } else {
            val = tmpT1;
        }
    }

    void Call_suffix2::visit(sema::Sema *semaAna) {
        //产生式右部为空，不执行操作
    }

    void ArgList::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void ArgList1::visit(sema::Sema *semaAna) {
        expression->visit(semaAna);

        if (calleeFun->params.size() <= argOffset)
            return reportSemanticError(line, fmt::format("the function '{}' expect {} params but get too much params",
                                                         calleeFun->name, calleeFun->paramCount));
        auto expectT = calleeFun->params[argOffset]->selfType;
        String tmpT = autoConversion(expression->val, expression->type->selfType,
                                     expectT, line, semaAna);
        semaAna->irCode.emplace_back(fmt::format("param {}", tmpT));
        arguments->calleeFun = calleeFun;
        arguments->argOffset = argOffset + 1;

        arguments->visit(semaAna);

        sum = arguments->sum + 1;
    }

    void ArgList2::visit(sema::Sema *semaAna) {
        sum = 0;
    }

    void Arguments::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Arguments1::visit(sema::Sema *semaAna) {
        expression->visit(semaAna);

        if (calleeFun->params.size() <= argOffset)
            return reportSemanticError(line, fmt::format("the function '{}' expect {} params but get too much params",
                                                         calleeFun->name, calleeFun->paramCount));
        auto expectT = calleeFun->params[argOffset]->selfType;
        String tmpT = autoConversion(expression->val, expression->type->selfType,
                                     expectT, line, semaAna);
        semaAna->irCode.emplace_back(fmt::format("param {}", tmpT));
        arguments->calleeFun = calleeFun;
        arguments->argOffset = argOffset + 1;

        arguments->visit(semaAna);

        sum = arguments->sum + 1;
    }

    void Arguments2::visit(sema::Sema *semaAna) {
        sum = 0;
    }

    void Primary::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void Primary1::visit(sema::Sema *semaAna) {
        constVal->visit(semaAna);

        val = constVal->val;
        type = constVal->type;
    }

    void Primary2::visit(sema::Sema *semaAna) {
        expression->visit(semaAna);

        val = expression->val;
        type = expression->type;
    }

    void Primary3::visit(sema::Sema *semaAna) {
        var->usage = Usage::reference;

        var->visit(semaAna);

        val = var->val;
        type = var->type;
    }

    void ConstVal::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void ConstVal1::visit(sema::Sema *semaAna) {
        val = token_TRUE->toString();
        type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
    }

    void ConstVal2::visit(sema::Sema *semaAna) {
        val = token_FALSE->toString();
        type = std::make_shared<ast::Type>(ast::IdentifierType::BOOL_);
    }

    void ConstVal3::visit(sema::Sema *semaAna) {
        val = token_NIL->toString();
        type = std::make_shared<ast::Type>(ast::IdentifierType::NIL_);
    }

    void ConstVal4::visit(sema::Sema *semaAna) {
        val = token_INT_->toString();
        type = std::make_shared<ast::Type>(ast::IdentifierType::INT_);
    }

    void ConstVal5::visit(sema::Sema *semaAna) {
        val = token_REAL_->toString();
        type = std::make_shared<ast::Type>(ast::IdentifierType::REAL_);
    }

    void ConstVal6::visit(sema::Sema *semaAna) {
        val = token_STRING_->toString();
        type = std::make_shared<ast::Type>(ast::IdentifierType::STRING_);
    }

    void Var::visit(sema::Sema *semaAna) {
        if (usage == define) {
            id = token_IDENTIFIER->toString();
            varSuffix->usage = usage;
            varSuffix->t = t;
            varSuffix->w = w;
        } else {
            id = token_IDENTIFIER->toString();
            auto thisVarInTop = semaAna->top->lookup(id);
            if (thisVarInTop != nullptr) {
                type = thisVarInTop->varType;
            } else {
                reportSemanticError(line, fmt::format("undefined variable: {}", id));
                type = std::make_shared<ast::Type>(ast::IdentifierType::NIL_);
            }
            varSuffix->usage = usage;
            varSuffix->type = type;
            varSuffix->length = varSuffix->type->length;
        }

        varSuffix->visit(semaAna);

        if (usage == define) {
            type = varSuffix->type;
            width = sema::stringMul(varSuffix->width, varSuffix->length, semaAna);
            if (!semaAna->top->insert(id, type, width)) {
                reportSemanticError(line, fmt::format("the variable '{}' is exist in symbol table", id));
            }
            semaAna->irCode.emplace_back(fmt::format("define {} {}", id, type->toString()));
        } else {
            offset = varSuffix->offset;
            type = varSuffix->returnType;
            if (offset == "0") {
                val = id;
            } else {
                String tmpT1 = sema::Sema::genT();
                semaAna->irCode.emplace_back(fmt::format("{}={}+{}", tmpT1, id, offset));
                val = tmpT1;
            }
        }
    }

    void VarSuffix::visit(sema::Sema *semaAna) {
        //父类虚函数，不执行操作
    }

    void VarSuffix1::visit(sema::Sema *semaAna) {
        expression->visit(semaAna);

        if (usage == define) {
            varSuffix->usage = usage;
            varSuffix->t = t;
            varSuffix->w = w;
        } else {
            len = expression->val;
            varSuffix->usage = usage;
            if (type->varType == nullptr) {
                reportSemanticError(line, "Trying to index a variable that is not an array");
            }
            varSuffix->type = type->varType;
            varSuffix->length = varSuffix->type->length;
        }

        varSuffix->visit(semaAna);

        if (usage == define) {
            length = expression->val;
            width = sema::stringMul(varSuffix->width, varSuffix->length, semaAna);
            String tmpT1 = sema::Sema::genT();
            tmpT1 = sema::stringMul(length, width, semaAna);
            type = std::make_shared<ast::Type>(varSuffix->type, tmpT1, length);

        } else {
            String tmpT1 = sema::stringMul(len, varSuffix->width, semaAna);
            offset = sema::stringPlus(varSuffix->offset, tmpT1, semaAna);
            width = sema::stringMul(width, length, semaAna);
            returnType = varSuffix->returnType;
        }
    }

    void VarSuffix2::visit(sema::Sema *semaAna) {
        if (usage == define) {
            length = t->length;
            type = t;
            width = w;
        } else {
            width = type->width;
            returnType = type;
        }
    }

    void Token::visit(sema::Sema *semaAna) {
        //无操作
    }
}