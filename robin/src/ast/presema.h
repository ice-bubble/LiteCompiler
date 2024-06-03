//
// Created by icelake on 24-6-2.
//

#ifndef ROBIN_PRESEMA_H
#define ROBIN_PRESEMA_H

#include "../common.h"

namespace sema {
    class Sema;

    class StmtSpace;

    class ExprSpace;

    String stringMul(String left, String right, Sema *semaAna);

    String stringPlus(String left, String right, Sema *semaAna);
}

#endif //ROBIN_PRESEMA_H



