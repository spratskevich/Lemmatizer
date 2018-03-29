#include "Lemmatization.h"

namespace lemmatizer {

    class LemmatizationImpl {
    public:
        LemmatizationImpl(std::istream &input_stream);

        const std::string &last_lemma() const;
        const std::string *next_lemma();
        bool is_complete() const;
    
    private:        
        std::istream &input_stream_;
        std::string last_lemma_;
        bool is_complete_;
    };
}
