# coding: utf-8

# ------------------------------------------------------------------------------
# The script generates a file with all unambiguous lemmatizations
# known to the morphological dictionary of OpenCorpora (http://opencorpora.org/).
#
# The lemmatizations are written in the following format:
#
# word1 lemma1
# word2 lemma2
# ...
# wordN lemmaN
#
# Requires pymorphy2 (https://pymorphy2.readthedocs.io/en/latest/).
# ------------------------------------------------------------------------------

OUTPUT_FILE_NAME = "unambiguos_lemmatizations.txt"

import itertools
import operator
import os.path
import pymorphy2

if not os.path.isfile(OUTPUT_FILE_NAME):
    morph = pymorphy2.MorphAnalyzer()
    
    with open(OUTPUT_FILE_NAME, "w") as output_file:
        for word, parses in itertools.groupby(morph.iter_known_word_parses(), operator.attrgetter("word")):
            normal_forms = {parse.normal_form for parse in parses}
            if len(normal_forms) == 1:
                print(word, normal_forms.pop(), file=output_file)