# coding: utf-8

# ------------------------------------------------------------------------------
# The script generates a file with unambiguous lemmatizations
# of the words from the frequency list of OpenCorpora (http://opencorpora.org/)
#
# The lemmatizations are written in descending order of word frequency
# in the following format:
#
# word1 lemma1
# word2 lemma2
# ...
# wordN lemmaN
#
# Requires pymorphy2 (https://pymorphy2.readthedocs.io/en/latest/).
# ------------------------------------------------------------------------------

OUTPUT_FILE_NAME = "unambiguos_lemmatizations_from_freq_list.txt"
FREQ_LIST_URL = "http://opencorpora.org/files/export/ngrams/unigrams.cyr.lc.bz2"
FREQ_LIST_FILE_NAME = "freq_list.txt"

import os
import os.path
import pymorphy2
import urllib.request
import bz2

if not os.path.isfile(OUTPUT_FILE_NAME):
    # Obtain the frequency list
    if not os.path.isfile(FREQ_LIST_FILE_NAME):
        compressed_file_name, _ = urllib.request.urlretrieve(FREQ_LIST_URL)
        with bz2.open(compressed_file_name, "r") as compressed_file, \
                 open(FREQ_LIST_FILE_NAME, "wb") as decompressed_file:
            portion_size = 100 * 1024
            for data in iter(lambda: compressed_file.read(portion_size), b""):
                decompressed_file.write(data)
        os.remove(compressed_file_name)


    morph = pymorphy2.MorphAnalyzer()
    
    with open(FREQ_LIST_FILE_NAME, "r") as freq_list_file, \
            open(OUTPUT_FILE_NAME, "w") as output_file:
        for line in freq_list_file:
            word = line.split()[0]
            normal_forms = morph.normal_forms(word)
            if len(normal_forms) == 1:
                print(word, normal_forms[0], file=output_file)
        