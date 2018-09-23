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
		const std::string get_stem() const;

        LemmaIter begin();
        LemmaIter end() const;

    private:
        std::shared_ptr<LemmatizationImpl> pimpl_;
    };
}
