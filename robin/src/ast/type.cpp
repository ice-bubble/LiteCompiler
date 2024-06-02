//
// Created by icelake on 24-5-19.
//

#include "type.h"
#include "presema.h"
#include "../error/error.h"

namespace ast {
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
    Map<IdentifierType, String> Type::typeToString = {
            {BASE_,   "base"},
            {VAR_,    "var"},
            {ARRAY_,  "array"},
            {FUNC_,   "func"},
            {STRING_, "string"},
            {NIL_,    "nil"},
            {BOOL_,   "bool"},
            {CHAR_,   "char"},
            {INT_,    "int"},
            {REAL_,   "double"},
    };

    SharedPtr<Type> Type::makeTypeInstance(IdentifierType requestedType) {
        switch (requestedType) {
            case BASE_:
                return std::make_shared<BASE_Type>();
            case VAR_:
                return std::make_shared<VAR_Type>();
            case ARRAY_:
                return std::make_shared<ARRAY_Type>();
            case FUNC_:
                return std::make_shared<FUNC_Type>();
            case STRING_:
                return std::make_shared<STRING_Type>();
            case NIL_:
                return std::make_shared<NIL_Type>();
            case BOOL_:
                return std::make_shared<BOOL_Type>();
            case CHAR_:
                return std::make_shared<CHAR_Type>();
            case INT_:
                return std::make_shared<INT_Type>();
            case REAL_:
                return std::make_shared<REAL_Type>();
        }
        return std::make_shared<NIL_Type>();
    }

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
                fmt::print(stderr, "T1:{} ,T2:{}\n", (int) T1, (int) T2);
                reportSemanticError(line, "this function has more then a type of return");
            }
            return t1;
        }
    }
}