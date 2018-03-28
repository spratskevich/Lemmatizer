#pragma once

#include "LemmaIter.h"

#include <istream>
#include <memory>

namespace lemmatizer {

    class LemmatizationImpl;

    class Lemmatization {
    public:
        Lemmatization(std::istream &input_stream);

        const std::string &last_lemma() const;
        const std::string *next_lemma();
        bool is_complete() const;

        LemmaIter begin();
        LemmaIter end() const;

    private:
        std::shared_ptr<LemmatizationImpl> pimpl_;
    };
}
