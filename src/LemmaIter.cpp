#include "LemmaIter.h"

#include "Lemmatization.h"

namespace lemmatizer {

    LemmaIter::LemmaIter()
        : lemmatization_ptr_() {}

    LemmaIter::LemmaIter(Lemmatization &lemmatization)
        : lemmatization_ptr_(&lemmatization) {}

    bool LemmaIter::operator==(LemmaIter rhs) const {
        return lemmatization_ptr_ == rhs.lemmatization_ptr_;
    }

    bool LemmaIter::operator!=(LemmaIter rhs) const {
        return !(*this == rhs);
    }

    // TODO: add end-iterator dereferencing exception hadling in debug build

    LemmaIter::reference LemmaIter::operator*() const {
        return lemmatization_ptr_->last_lemma();
    }

    LemmaIter::pointer LemmaIter::operator->() const {
        return &lemmatization_ptr_->last_lemma();
    }

    LemmaIter LemmaIter::operator++() {
        if (!lemmatization_ptr_->next_lemma())
            lemmatization_ptr_ = nullptr;
        return *this;
    }

    LemmaIter LemmaIter::operator++(int) {
        return ++*this;
    }
}
