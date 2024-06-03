//
// Created by icelake on 24-5-29.
//

#ifndef ROBIN_EXPRSPACE_H
#define ROBIN_EXPRSPACE_H

#include "../common.h"

namespace sema {
    class ExprSpace {
    public:
        int right = -1;
        List<size_t> rightSentences;
        List<String> *irCode;

        explicit ExprSpace(List<String> *irCode) : irCode(irCode) {}

        void backpatch() {
            for (auto i: rightSentences) {
                (*irCode)[i] = fmt::format((*irCode)[i], right);
            }

        }
    };

}

#endif //ROBIN_EXPRSPACE_H
