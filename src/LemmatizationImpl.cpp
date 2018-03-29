// This implementation is a stupid stub returning each input word unchanged and
// does no input errors handling

#include "LemmatizationImpl.h"

namespace lemmatizer {

    LemmatizationImpl::LemmatizationImpl(std::istream &input_stream)
        : input_stream_(input_stream), last_lemma_(), is_complete_() {}

    const std::string &LemmatizationImpl::last_lemma() const {
        return last_lemma_;
    }

    const std::string *LemmatizationImpl::next_lemma() {
        std::string input_str;
        if (input_stream_ >> input_str) {
            last_lemma_ = input_str;
            return &last_lemma_;
        } else {
            is_complete_ = true;
            return nullptr;
        }
    }

    bool LemmatizationImpl::is_complete() const {
        return is_complete_;
    }
}
