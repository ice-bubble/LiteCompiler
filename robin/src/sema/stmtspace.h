//
// Created by icelake on 24-5-29.
//

#ifndef ROBIN_STMTSPACE_H
#define ROBIN_STMTSPACE_H

#include "../common.h"

namespace sema {

    class StmtSpace {
    public:
        int compare = -1;
        int code1 = -1;
        int code2 = -1;
        int next = -1;
        List<size_t> compareSentences;
        List<size_t> code1Sentences;
        List<size_t> code2Sentences;
        List<size_t> nextSentences;
        List<String> *irCode;

        explicit StmtSpace(List<String> *irCode) : irCode(irCode) {}

        void backpatch() {
            for (auto i: compareSentences)
                (*irCode)[i] = fmt::format((*irCode)[i], compare);
            for (auto i: code1Sentences)
                (*irCode)[i] = fmt::format((*irCode)[i], code1);
            for (auto i: code2Sentences)
                (*irCode)[i] = fmt::format((*irCode)[i], code2);
            for (auto i: nextSentences)
                (*irCode)[i] = fmt::format((*irCode)[i], next);
        }
    };
}

#endif //ROBIN_STMTSPACE_H
