//
// Created by icelake on 24-6-4.
//

#ifndef ROBIN_CODESPACE_H
#define ROBIN_CODESPACE_H

#include "../common.h"

namespace ast {

    class CodeSpace {
    public:
        int compare = -1;
        int code1 = -1;
        int code2 = -1;
        int next = -1;
        int right = -1;
        List<size_t> compareSentences;
        List<size_t> code1Sentences;
        List<size_t> code2Sentences;
        List<size_t> nextSentences;
        List<size_t> rightSentences;
        List<String> *irCode;

        explicit CodeSpace(List<String> *irCode) : irCode(irCode) {}

        void backpatch() {
            for (auto i: compareSentences)
                (*irCode)[i] = fmt::format((*irCode)[i], compare);
            for (auto i: code1Sentences)
                (*irCode)[i] = fmt::format((*irCode)[i], code1);
            for (auto i: code2Sentences)
                (*irCode)[i] = fmt::format((*irCode)[i], code2);
            for (auto i: nextSentences)
                (*irCode)[i] = fmt::format((*irCode)[i], next);
            for (auto i: rightSentences) {
                (*irCode)[i] = fmt::format((*irCode)[i], right);
            }
        }
    };
}

#endif //ROBIN_CODESPACE_H
