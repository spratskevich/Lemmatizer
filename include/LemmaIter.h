#pragma once

#include <iterator>
#include <string>

namespace lemmatizer {

    class Lemmatization;

    class LemmaIter {
    public:
        // std::iterator_traits support
        using iterator_category = std::input_iterator_tag;
        using value_type = std::string;
        using reference = const value_type &;
        using pointer = const value_type *;
        using difference_type = std::ptrdiff_t;

        LemmaIter();
        LemmaIter(Lemmatization &lemmatizationPtr);

        bool operator==(LemmaIter rhs) const;
        bool operator!=(LemmaIter rhs) const;

        reference operator*() const;
        pointer operator->() const;

        LemmaIter operator++();
        LemmaIter operator++(int);

    private:

        Lemmatization *lemmatization_ptr_;
    };
}
