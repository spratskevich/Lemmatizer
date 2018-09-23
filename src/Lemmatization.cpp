#include "Lemmatization.h"

#include "LemmatizationImpl.h"
#include "LemmaIter.h"

namespace lemmatizer {
    
    Lemmatization::Lemmatization(std::istream &input_stream)
        : pimpl_(std::make_shared<LemmatizationImpl>(input_stream)) {}
    
    const std::string &Lemmatization::last_lemma() const {
        return pimpl_->last_lemma();
    }

    const std::string *Lemmatization::next_lemma() {
        return pimpl_->next_lemma();
    }
	const std::string Lemmatization::get_stem() const{
		return pimpl_->get_stem();
	}

    LemmaIter Lemmatization::begin() {
        return LemmaIter(*this);
    }

    LemmaIter Lemmatization::end() const {
        return LemmaIter();
    }
}