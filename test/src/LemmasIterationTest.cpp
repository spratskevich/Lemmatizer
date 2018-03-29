#include "Lemmatization.h"

#include <QtTest/QtTest>
#include <sstream>
#include <iterator>

namespace lemmatizer {

    class LemmasIterationTest : public QObject {
        Q_OBJECT
    private slots:
        void empty_input();
        void words_free_input();
        void lemmas_quantity();
        void lemmas_non_emptiness();
    };

    void LemmasIterationTest::empty_input() {
        std::istringstream input_stream;
        Lemmatization lemmatization(input_stream);
        
        QCOMPARE(static_cast<const void *>(lemmatization.next_lemma()), static_cast<const void *>(nullptr));
        QVERIFY(lemmatization.begin() == lemmatization.end());
        if (lemmatization.begin() != lemmatization.end())
            QFAIL("Lemmatization::begin() is not idempotent");
    }

    void LemmasIterationTest::words_free_input() {
        std::istringstream input_stream(" \n\n     \r\n    \t");
        Lemmatization lemmatization(input_stream);

        QVERIFY(lemmatization.next_lemma() == nullptr);
        QVERIFY(lemmatization.begin() == lemmatization.end());
        if (lemmatization.begin() != lemmatization.end())
            QFAIL("Lemmatization::begin() is not idempotent");
    }

    void LemmasIterationTest::lemmas_quantity() {
        std::istringstream input_stream("word1 \n  \r word2  \r  word3 word4     word5");
        Lemmatization lemmatization(input_stream);

        QCOMPARE(std::distance(lemmatization.begin(), lemmatization.end()), 5);
    }

    void LemmasIterationTest::lemmas_non_emptiness() {
        std::istringstream input_stream("word1 \n  word2  \r\n  word3 word4   word5  \n word6");
        Lemmatization lemmatization(input_stream);

        for (auto &&lemma: lemmatization)
            QVERIFY(!lemma.empty());
    }

}

QTEST_MAIN(lemmatizer::LemmasIterationTest)
#include "LemmasIterationTest.moc"