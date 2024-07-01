// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <gtest/gtest.h>
#include <mountain_town/neural_network/nlp/basic.h>

#include <iostream>

vector<string> words;
string err = LoadPTBCorpus("tests/nlp/testdata/ptb.train.txt", words);

TEST(NLPBasicTests, LoadPTBCorpus) {
  ASSERT_EQ(err, "");
  ASSERT_EQ(words[0], "aer");
  ASSERT_EQ(words[9], "hydro-quebec");
  ASSERT_EQ(words[26], "<unk>");
}

TEST(NLPBasicTests, GenWordToID) {
  ASSERT_EQ(err, "");
  unordered_map<string, int> word_to_id;
  GenWordToID(words, word_to_id);
  ASSERT_EQ(word_to_id["aer"], 0);
  ASSERT_EQ(word_to_id["hydro-quebec"], 9);
  ASSERT_EQ(words.size(), 929589);
  ASSERT_EQ(word_to_id.size(), 10000);
}

TEST(NLPBasicTests, GenIDToWord) {
  ASSERT_EQ(err, "");
  unordered_map<int, string> id_to_word;
  GenIDToWord(words, id_to_word);
  ASSERT_EQ(id_to_word.size(), 10000);
  ASSERT_EQ(id_to_word[0], "aer");
  ASSERT_EQ(id_to_word[9], "hydro-quebec");
}

TEST(NLPBasicTests, GenCorpus) {
  ASSERT_EQ(err, "");
  int corpus[words.size()];
  GenCorpus(words, corpus);
  ASSERT_EQ(corpus[0], 0);
  ASSERT_EQ(corpus[39], 27);
}