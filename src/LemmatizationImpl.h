#include "Lemmatization.h"
#include <regex>

namespace lemmatizer {

    class LemmatizationImpl {
    public:
        LemmatizationImpl(std::istream &input_stream);

        const std::string &last_lemma() const;
        const std::string *next_lemma();
		void findStem(std::string);
		const std::string get_stem() const;
    
    private:
		std::string findRV(std::string);
		std::string findR1(std::string);
		std::string findR2(std::string);
		void cutEnding(std::string &, std::string&, std::string&, std::string&, const std::regex);
        
		std::istream &input_stream_;
        std::string last_lemma_;
		std::string stem_;
		std::string endings_[4] = { std::string(),std::string(),std::string(),std::string() };
    };
}
