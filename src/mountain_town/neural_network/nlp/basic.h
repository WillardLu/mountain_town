// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#ifndef MOUNTAIN_TOWN_NEURAL_NETWORK_NLP_BASIC_H_
#define MOUNTAIN_TOWN_NEURAL_NETWORK_NLP_BASIC_H_

#include <mountain_town/string/basic.h>

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::ifstream;
using std::ios;
using std::string;
using std::unordered_map;
using std::vector;

string LoadPTBCorpus(string filename, vector<string>& words);
void GenWordToID(vector<string> words, unordered_map<string, int>& word_to_id);
void GenIDToWord(vector<string> words, unordered_map<int, string>& id_to_word);
void GenCorpus(vector<string> words, int *corpus);

#endif  // MOUNTAIN_TOWN_NLP_BASIC_H_