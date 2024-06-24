#include "type.h"
#include "../error/error.h"

namespace ast {
    Type::Type(const SharedPtr<Type> &varType, String width, String length)
            : varType(varType), width(width), length(length) { selfType = ARRAY_; }

    Type::Type(IdentifierType selfT) : selfType(selfT) {
        switch (selfType) {
            case BASE_:
                break;
            case BOOL_:
            case CHAR_:
                width = "1";
                length = "1";
                break;
            case INT_:
            case REAL_:
            case VAR_:
            case FUNC_:
            case STRING_:
            case NIL_:
                width = "8";
                length = "1";
                break;
            case ARRAY_:
                width = "8";
                length = "1";
                varType = std::make_shared<Type>(VAR_);
                break;
        }
    }

    String Type::toString() {
        switch (selfType) {
            case BASE_:
                return "BASE_";
            case VAR_:
                return "VAR_";
            case ARRAY_:
                return fmt::format("ARRAY_({},{})", length, varType->toString());
            case FUNC_:
                return "FUNC_";
            case STRING_:
                return "STRING_";
            case NIL_:
                return "NIL_";
            case BOOL_:
                return "BOOL_";
            case CHAR_:
                return "CHAR_";
            case INT_:
                return "INT_";
            case REAL_:
                return "REAL_";
        }
        return "";
    }

    Map<Pair<IdentifierType, IdentifierType>, IdentifierType> Type::typeTransform = {
            {{BASE_,   BASE_},   BASE_},
            {{BASE_,   VAR_},    BASE_},
            {{BASE_,   ARRAY_},  BASE_},
            {{BASE_,   FUNC_},   BASE_},
            {{BASE_,   STRING_}, BASE_},
            {{BASE_,   NIL_},    BASE_},
            {{BASE_,   BOOL_},   BASE_},
            {{BASE_,   CHAR_},   BASE_},
            {{BASE_,   INT_},    BASE_},
            {{BASE_,   REAL_},   BASE_},

            {{VAR_,    BASE_},   BASE_},
            {{VAR_,    VAR_},    VAR_},
            {{VAR_,    ARRAY_},  ARRAY_},
            {{VAR_,    FUNC_},   FUNC_},
            {{VAR_,    STRING_}, BASE_},
            {{VAR_,    NIL_},    BASE_},
            {{VAR_,    BOOL_},   BOOL_},
            {{VAR_,    CHAR_},   CHAR_},
            {{VAR_,    INT_},    INT_},
            {{VAR_,    REAL_},   REAL_},

            {{ARRAY_,  BASE_},   BASE_},
            {{ARRAY_,  VAR_},    ARRAY_},
            {{ARRAY_,  ARRAY_},  ARRAY_},
            {{ARRAY_,  FUNC_},   BASE_},
            {{ARRAY_,  STRING_}, BASE_},
            {{ARRAY_,  NIL_},    BASE_},
            {{ARRAY_,  BOOL_},   BASE_},
            {{ARRAY_,  CHAR_},   BASE_},
            {{ARRAY_,  INT_},    BASE_},
            {{ARRAY_,  REAL_},   BASE_},

            {{FUNC_,   BASE_},   BASE_},
            {{FUNC_,   VAR_},    FUNC_},
            {{FUNC_,   ARRAY_},  BASE_},
            {{FUNC_,   FUNC_},   FUNC_},
            {{FUNC_,   STRING_}, BASE_},
            {{FUNC_,   NIL_},    BASE_},
            {{FUNC_,   BOOL_},   BASE_},
            {{FUNC_,   CHAR_},   BASE_},
            {{FUNC_,   INT_},    BASE_},
            {{FUNC_,   REAL_},   BASE_},

            {{STRING_, BASE_},   BASE_},
            {{STRING_, VAR_},    STRING_},
            {{STRING_, ARRAY_},  BASE_},
            {{STRING_, FUNC_},   BASE_},
            {{STRING_, STRING_}, STRING_},
            {{STRING_, NIL_},    BASE_},
            {{STRING_, BOOL_},   BASE_},
            {{STRING_, CHAR_},   BASE_},
            {{STRING_, INT_},    BASE_},
            {{STRING_, REAL_},   BASE_},

            {{NIL_,    BASE_},   BASE_},
            {{NIL_,    VAR_},    NIL_},
            {{NIL_,    ARRAY_},  BASE_},
            {{NIL_,    FUNC_},   BASE_},
            {{BASE_,   STRING_}, BASE_},
            {{NIL_,    NIL_},    BASE_},
            {{NIL_,    BOOL_},   BOOL_},
            {{NIL_,    CHAR_},   CHAR_},
            {{NIL_,    INT_},    INT_},
            {{NIL_,    REAL_},   REAL_},

            {{BOOL_,   BASE_},   BASE_},
            {{BOOL_,   VAR_},    BOOL_},
            {{BOOL_,   ARRAY_},  BASE_},
            {{BOOL_,   FUNC_},   BASE_},
            {{BOOL_,   STRING_}, BASE_},
            {{BOOL_,   NIL_},    BASE_},
            {{BOOL_,   BOOL_},   BOOL_},
            {{BOOL_,   CHAR_},   CHAR_},
            {{BOOL_,   INT_},    INT_},
            {{BOOL_,   REAL_},   REAL_},

            {{CHAR_,   BASE_},   BASE_},
            {{CHAR_,   VAR_},    CHAR_},
            {{CHAR_,   ARRAY_},  BASE_},
            {{CHAR_,   FUNC_},   BASE_},
            {{CHAR_,   STRING_}, BASE_},
            {{CHAR_,   NIL_},    BASE_},
            {{CHAR_,   BOOL_},   CHAR_},
            {{CHAR_,   CHAR_},   CHAR_},
            {{CHAR_,   INT_},    INT_},
            {{CHAR_,   REAL_},   REAL_},

            {{INT_,    BASE_},   BASE_},
            {{INT_,    VAR_},    INT_},
            {{INT_,    ARRAY_},  BASE_},
            {{INT_,    FUNC_},   BASE_},
            {{INT_,    STRING_}, BASE_},
            {{INT_,    NIL_},    BASE_},
            {{INT_,    BOOL_},   INT_},
            {{INT_,    CHAR_},   INT_},
            {{INT_,    INT_},    INT_},
            {{INT_,    REAL_},   REAL_},

            {{REAL_,   BASE_},   BASE_},
            {{REAL_,   VAR_},    REAL_},
            {{REAL_,   ARRAY_},  BASE_},
            {{REAL_,   FUNC_},   BASE_},
            {{REAL_,   STRING_}, BASE_},
            {{REAL_,   NIL_},    BASE_},
            {{REAL_,   BOOL_},   REAL_},
            {{REAL_,   CHAR_},   REAL_},
            {{REAL_,   INT_},    REAL_},
            {{REAL_,   REAL_},   REAL_},
    };

    Map<Pair<IdentifierType, IdentifierType>, IdentifierType> Type::typeForceTransform = {
            {{BASE_,   BASE_},   BASE_},
            {{BASE_,   VAR_},    BASE_},
            {{BASE_,   ARRAY_},  BASE_},
            {{BASE_,   FUNC_},   BASE_},
            {{BASE_,   STRING_}, BASE_},
            {{BASE_,   NIL_},    BASE_},
            {{BASE_,   BOOL_},   BASE_},
            {{BASE_,   CHAR_},   BASE_},
            {{BASE_,   INT_},    BASE_},
            {{BASE_,   REAL_},   BASE_},

            {{VAR_,    BASE_},   BASE_},
            {{VAR_,    VAR_},    VAR_},
            {{VAR_,    ARRAY_},  ARRAY_},
            {{VAR_,    FUNC_},   FUNC_},
            {{VAR_,    STRING_}, BASE_},
            {{VAR_,    NIL_},    BASE_},
            {{VAR_,    BOOL_},   BOOL_},
            {{VAR_,    CHAR_},   CHAR_},
            {{VAR_,    INT_},    INT_},
            {{VAR_,    REAL_},   REAL_},

            {{ARRAY_,  BASE_},   BASE_},
            {{ARRAY_,  VAR_},    ARRAY_},
            {{ARRAY_,  ARRAY_},  ARRAY_},
            {{ARRAY_,  FUNC_},   BASE_},
            {{ARRAY_,  STRING_}, BASE_},
            {{ARRAY_,  NIL_},    BASE_},
            {{ARRAY_,  BOOL_},   BASE_},
            {{ARRAY_,  CHAR_},   BASE_},
            {{ARRAY_,  INT_},    BASE_},
            {{ARRAY_,  REAL_},   BASE_},

            {{FUNC_,   BASE_},   BASE_},
            {{FUNC_,   VAR_},    FUNC_},
            {{FUNC_,   ARRAY_},  BASE_},
            {{FUNC_,   FUNC_},   FUNC_},
            {{FUNC_,   STRING_}, BASE_},
            {{FUNC_,   NIL_},    BASE_},
            {{FUNC_,   BOOL_},   BASE_},
            {{FUNC_,   CHAR_},   BASE_},
            {{FUNC_,   INT_},    BASE_},
            {{FUNC_,   REAL_},   BASE_},

            {{STRING_, BASE_},   BASE_},
            {{STRING_, VAR_},    STRING_},
            {{STRING_, ARRAY_},  BASE_},
            {{STRING_, FUNC_},   BASE_},
            {{STRING_, STRING_}, STRING_},
            {{STRING_, NIL_},    BASE_},
            {{STRING_, BOOL_},   BASE_},
            {{STRING_, CHAR_},   BASE_},
            {{STRING_, INT_},    BASE_},
            {{STRING_, REAL_},   BASE_},

            {{NIL_,    BASE_},   BASE_},
            {{NIL_,    VAR_},    NIL_},
            {{NIL_,    ARRAY_},  BASE_},
            {{NIL_,    FUNC_},   BASE_},
            {{BASE_,   STRING_}, BASE_},
            {{NIL_,    NIL_},    BASE_},
            {{NIL_,    BOOL_},   BOOL_},
            {{NIL_,    CHAR_},   CHAR_},
            {{NIL_,    INT_},    INT_},
            {{NIL_,    REAL_},   REAL_},

            {{BOOL_,   BASE_},   BASE_},
            {{BOOL_,   VAR_},    BOOL_},
            {{BOOL_,   ARRAY_},  BASE_},
            {{BOOL_,   FUNC_},   BASE_},
            {{BOOL_,   STRING_}, BASE_},
            {{BOOL_,   NIL_},    BASE_},
            {{BOOL_,   BOOL_},   BOOL_},
            {{BOOL_,   CHAR_},   CHAR_},
            {{BOOL_,   INT_},    INT_},
            {{BOOL_,   REAL_},   REAL_},

            {{CHAR_,   BASE_},   BASE_},
            {{CHAR_,   VAR_},    CHAR_},
            {{CHAR_,   ARRAY_},  BASE_},
            {{CHAR_,   FUNC_},   BASE_},
            {{CHAR_,   STRING_}, BASE_},
            {{CHAR_,   NIL_},    BASE_},
            {{CHAR_,   BOOL_},   BOOL_},
            {{CHAR_,   CHAR_},   CHAR_},
            {{CHAR_,   INT_},    INT_},
            {{CHAR_,   REAL_},   REAL_},

            {{INT_,    BASE_},   BASE_},
            {{INT_,    VAR_},    INT_},
            {{INT_,    ARRAY_},  BASE_},
            {{INT_,    FUNC_},   BASE_},
            {{INT_,    STRING_}, BASE_},
            {{INT_,    NIL_},    BASE_},
            {{INT_,    BOOL_},   BOOL_},
            {{INT_,    CHAR_},   CHAR_},
            {{INT_,    INT_},    INT_},
            {{INT_,    REAL_},   REAL_},

            {{REAL_,   BASE_},   BASE_},
            {{REAL_,   VAR_},    REAL_},
            {{REAL_,   ARRAY_},  BASE_},
            {{REAL_,   FUNC_},   BASE_},
            {{REAL_,   STRING_}, BASE_},
            {{REAL_,   NIL_},    BASE_},
            {{REAL_,   BOOL_},   BOOL_},
            {{REAL_,   CHAR_},   CHAR_},
            {{REAL_,   INT_},    INT_},
            {{REAL_,   REAL_},   REAL_},
    };

    Map<IdentifierType, String> Type::typeToString = {
            {BASE_,   "base"},
            {VAR_,    "var"},
            {ARRAY_,  "array"},
            {FUNC_,   "func"},
            {STRING_, "string"},
            {NIL_,    "nil"},
            {BOOL_,   "bool"},
            {CHAR_,   "char"},
            {INT_,    "integer"},
            {REAL_,   "double"},
    };

    SharedPtr<Type> Type::chooseReturnType(SharedPtr<Type> t1, SharedPtr<Type> t2, size_t line) {
        auto T1 = t1->selfType;
        auto T2 = t2->selfType;
        if (T1 == IdentifierType::VAR_) {
            return t2;
        } else if (T1 == IdentifierType::BASE_) {
            if (T2 != IdentifierType::VAR_) return t2;
            return t1;
        } else {
            if (T2 == IdentifierType::VAR_)return t1;
            if (T2 == IdentifierType::BASE_)return t1;
            if (T1 != T2) {
                //fmt::print(stderr, "T1:{} ,T2:{}\n", (int) T1, (int) T2);
                reportSemanticError(line, "this function has more then a type of return");
            }
            return t1;
        }
    }

    bool Type::isSameType(SharedPtr<Type> t1, SharedPtr<Type> t2) {
        if (t1 == nullptr || t2 == nullptr) return false;
        if (t1->selfType != t2->selfType) return false;
        if (t1->selfType == IdentifierType::ARRAY_)
            return isSameType(t1->varType, t2->varType);
        return true;
    }
}