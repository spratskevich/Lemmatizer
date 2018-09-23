// This stub implementation returns each input word unchanged and
// does no input errors handling

#include "LemmatizationImpl.h"

using namespace std;

namespace lemmatizer {

	static const string vowels("аеиоуыэю€");
	static const string consonants("бвгджзклмнпрстхцчшщ");
	static const regex perfectgerund = regex("(.*)(ившись|ывшись|авшись|€вшись|авши|€вши|ивши|ывши|ав|€в|ыв|ив)$");
	static const regex perfectgerund1M = regex("(.*)(авшись|€вшись|авши|€вши|ав|€в)$");
	static const regex perfectgerund1 = regex("(вшись|вши|в)$");
	static const regex perfectgerund2 = regex("(ившись|ывшись|ивши|ывши|ыв|ив)$");
	static const regex reflexive = regex("(с€|сь)$");
	static const regex reflexiveM = regex("(.*)(с€|сь)$");
	static const regex adjective = regex("(ими|ыми|его|ого|ему|ому|ее|ие|ые|ое|ей|ий|ый|ой|ем|им|ым|ом|их|ых|ую|юю|а€|€€|ою|ею)$");
	static const regex adjectiveM = regex("(.*)(ими|ыми|его|ого|ему|ому|ее|ие|ые|ое|ей|ий|ый|ой|ем|им|ым|ом|их|ых|ую|юю|а€|€€|ою|ею)$");
	static const regex participle = regex("(.*)(ивш|ывш|ующаем|анн|авш|ающ|ащ|€ем|€нн|€вш|€ющ|€щ)$");
	static const regex participle1M = regex("(.*)(аем|анн|авш|ающ|ащ|€ем|€нн|€вш|€ющ|€щ)$");
	static const regex participle1 = regex("(ем|нн|вш|ющ|щ)$");
	static const regex participle2 = regex("(ивш|ывш|ующ)$");
	static const regex verb = regex("(.*)(аете|айте|аешь|анно|ала|ана|али|аем|ало|ано|ает|ают|аны|ать|ай|ал|ан|€ете|€йте|€ешь|€нно|€ла|\
€на|€ли|€ем|€ло|€но|€ет|€ют|€ны|€ть|€й|€л|€н|ейте|уйте|ила|ыла|ена|ите|или|ыли|ило|ыло|ено|ует|уют|ены|ить|ыть|ишь|ей|уй|ил|ыл|им|\
ым|ен|€т|ит|ыт|ую|ю)$");
	static const regex verb1M = regex("(.*)(аете|айте|аешь|анно|ала|ана|али|аем|ало|ано|ает|ают|аны|ать|ай|ал|ан|€ете|€йте|€ешь|€нно|\
€ла|€на|€ли|€ем|€ло|€но|€ет|€ют|€ны|€ть|€й|€л|€н)$");
	static const regex verb1 = regex("(ете|йте|ешь|нно|ла|на|ли|ем|ло|но|ет|ют|ны|ть|й|л|н)$");
	static const regex verb2 = regex("(ейте|уйте|ила|ыла|ена|ите|или|ыли|ило|ыло|ено|ует|уют|ены|ить|ыть|ишь|ей|уй|ил|ыл|им|ым|ен|€т|\
ит|ыт|ую|ю)$");
	static const regex nounM = regex("(.*)(и€ми|€ми|ами|ией|и€м|ием|и€х|ев|ов|ие|ье|еи|ии|ей|ой|ий|€м|ем|ам|ом|ах|€х|ию|ью|и€|ь€|€|а|\
е|и|й|о|у|ы|ь|ю)$");
	static const regex noun = regex("(и€ми|€ми|ами|ией|и€м|ием|и€х|ев|ов|ие|ье|еи|ии|ей|ой|ий|€м|ем|ам|ом|ах|€х|ию|ью|и€|ь€|€|а|е|и|й|\
о|у|ы|ь|ю)$");
	static const regex i = regex("и$");
	static const regex iM = regex("(.*)(и)$");
	static const regex pM = regex("(.*)ь$");
	static const regex p = regex("ь$");
	static const regex nnM = regex("(.*)(нн)$");
	static const regex nn = regex("(н)$");
	static const regex derivationalM = regex("(.*)(ость|ост)$");
	static const regex derivational = regex("(ость|ост)$");
	static const regex superlativeM = regex("(.*)(ейше|ейш)$");
	static const regex superlative = regex("(ейше|ейш)$");
	
	LemmatizationImpl::LemmatizationImpl(std::istream &input_stream)
        : input_stream_(input_stream), last_lemma_() {}

    const std::string &LemmatizationImpl::last_lemma() const {
        return last_lemma_;
    }

    const std::string *LemmatizationImpl::next_lemma() {
        std::string input_str;
        if (input_stream_ >> input_str) {
			findStem(input_str);
            last_lemma_ = input_str;
            return &last_lemma_;
        } else {
            return nullptr;
        }
    }

	const string LemmatizationImpl::get_stem() const
	{
		return stem_;
	}

	void LemmatizationImpl::findStem(string inputWord)
	{
		transform(inputWord.begin(), inputWord.end(), inputWord.begin(), ::tolower);
		replace(inputWord.begin(), inputWord.end(), 'Є', 'е');

		string stem = inputWord;
		string RV = findRV(stem);
		string R1 = findR1(RV);
		string R2 = findR2(R1);
		string endings[4];

		if (regex_match(RV, perfectgerund))
		{
			if (regex_match(RV, perfectgerund1M))
				cutEnding(stem, RV, R2, endings[0], perfectgerund1);
			else
				cutEnding(stem, RV, R2, endings[0], perfectgerund2);
		}
		else
		{
			if (regex_match(RV, reflexiveM))
				cutEnding(stem, RV, R2, endings[0], reflexive);
			if (regex_match(RV, adjectiveM))
			{
				cutEnding(stem, RV, R2, endings[0], adjective);
				if (regex_match(RV, participle))
				{
					if (regex_match(RV, participle1M))
						cutEnding(stem, RV, R2, endings[0], participle1);
					else
						cutEnding(stem, RV, R2, endings[0], participle2);
				}
			}
			else if (regex_match(RV, participle))
			{
				if (regex_match(RV, participle1M))
					cutEnding(stem, RV, R2, endings[0], participle1);
				else
					cutEnding(stem, RV, R2, endings[0], participle2);
			}
			else if (regex_match(RV, verb))
			{
				if (regex_match(RV, verb1M))
					cutEnding(stem, RV, R2, endings[0], verb1);
				else
					cutEnding(stem, RV, R2, endings[0], verb2);
			}
			else if (regex_match(RV, nounM))
				cutEnding(stem, RV, R2, endings[0], noun);
			if (regex_match(RV, iM))
				cutEnding(stem, RV, R2, endings[1], i);
			if (regex_match(R2, derivationalM))
				cutEnding(stem, RV, R2, endings[2], derivational);
			if (regex_match(RV, nnM))
				cutEnding(stem, RV, R2, endings[3], nn);
			else if (regex_match(RV, superlativeM))
			{
				cutEnding(stem, RV, R2, endings[3], superlative);
				if (regex_match(RV, nnM))
					cutEnding(stem, RV, R2, endings[3], nn);
			}
			else if (regex_match(RV, pM))
				cutEnding(stem, RV, R2, endings[3], p);
		}
		stem_ = stem;
		for (int i = 0; i < 4; i++)
		{
			endings_[i] = endings[i];
		}
		return;
	}

	void LemmatizationImpl::cutEnding(string &stem, string &RV, string &R2, string &ending, const regex rgx)
	{
		string tempRV = RV;
		RV = regex_replace(RV, rgx, "");
		R2 = regex_replace(R2, rgx, "");
		ending = tempRV.substr(RV.length());
		stem = stem.substr(0, stem.length() - ending.length());
	}

	string LemmatizationImpl::findRV(string inputWord)
	{
		string RV;
		size_t firstVowelPosInWord = inputWord.find_first_of(vowels, 0);

		if (firstVowelPosInWord != string::npos)
		{
			RV = inputWord.substr(firstVowelPosInWord + 1);
		}
		return RV;
	}

	string LemmatizationImpl::findR1(string RV)
	{
		string R1 = RV;
		size_t firstVowelPosInR1;
		if (!RV.empty())
		{
			firstVowelPosInR1 = R1.find_first_of(vowels, 0);
			if (firstVowelPosInR1 != string::npos && firstVowelPosInR1 != 0)
			{
				R1 = R1.substr(1);
				return R1;
			}
		}
		return findR2(R1);
	}

	string LemmatizationImpl::findR2(string R1)
	{
		string R2 = R1;
		size_t firstVowelPosInR1;
		size_t firstConsonantsPosInR1;
		firstVowelPosInR1 = R2.find_first_of(vowels, 0);
		firstConsonantsPosInR1 = R2.find_first_of(consonants, 0);
		while (firstVowelPosInR1 != string::npos && firstConsonantsPosInR1 != string::npos && !R2.empty() && (firstConsonantsPosInR1 != firstVowelPosInR1 + 1))
		{
			if (firstConsonantsPosInR1 < firstVowelPosInR1)
			{
				R2 = R2.substr(firstConsonantsPosInR1 + 1);
			}
			else
			{
				R2 = R2.substr(firstVowelPosInR1 + 1);
			}
			firstVowelPosInR1 = R2.find_first_of(vowels, 0);
			firstConsonantsPosInR1 = R2.find_first_of(consonants, 0);
		}
		if (firstVowelPosInR1 == string::npos || firstConsonantsPosInR1 == string::npos || R2.empty())
		{
			return string();
		}
		else
		{
			return R2.substr(firstConsonantsPosInR1 + 1);
		}
		return R2;
	}
}
