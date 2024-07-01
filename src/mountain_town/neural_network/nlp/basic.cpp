// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include "basic.h"

/// @brief 载入PTB语料库（Load the PTB corpus）
/// @param filename PTB语料库文件名（PTB corpus filename）
/// @param words 拆分为单词形式的PTB语料库（PTB corpus in word form）
/// @return 错误信息（error message）
string LoadPTBCorpus(string filename, vector<string>& words) {
  // 1. 打开PTB语料库文件（Open the PTB corpus file）
  ifstream fp(filename, ios::in | ios::binary | ios::ate);
  if (fp.is_open() == false) {
    return "Failed to open " + filename + ".\n";
  }
  // 2. 读入文件内容（Read file content）
  size_t size = (int)fp.tellg();
  char* buffer = new char[size];
  if (buffer == nullptr) {
    fp.close();
    return "Memory allocation failed.\n";
  }
  fp.seekg(0);
  if (!fp.read(buffer, size)) {
    delete[] buffer;
    fp.close();
    return "Failed to read data.\n";
  }
  fp.close();
  // 直接赋值会造成内存泄漏（Direct assignment can cause memory leaks）
  string ori = CharArrConvertToString(buffer, size, size);
  delete[] buffer;
  // 3. 处理文本（Process text）
  StrReplace(ori, "\n", "<eos>");
  ori = TrimWhitespace(ori);
  // 4. 按照whitespace拆分文本（Split text by whitespace）
  words = SplitStrRegex(ori, "[\\s\x20]+");
  return "";
}

/// @brief 生成单词与标识对应关系的字典（Generate a dictionary of
/// word-to-identifier correspondences）
/// @param words 单词列表（word list）
/// @param word_to_id 单词到标识的字典（dictionary from words to identifiers）
void GenWordToID(vector<string> words, unordered_map<string, int>& word_to_id) {
  for (size_t i = 0; i < words.size(); ++i) {
    auto it = word_to_id.find(words[i]);
    if (it == word_to_id.end()) {
      word_to_id.emplace(words[i], word_to_id.size());
    }
    words[i] = word_to_id[words[i]];
  }
}

/// @brief 生成标识到单词对应关系的字典（Generate a dictionary of
/// identifier-to-word correspondences）
/// @param words 单词列表（word list）
/// @param id_to_word 标识到单词的字典（dictionary from identifiers to words）
void GenIDToWord(vector<string> words, unordered_map<int, string>& id_to_word) {
  unordered_map<string, int> word_to_id;
  for (size_t i = 0; i < words.size(); ++i) {
    auto it = word_to_id.find(words[i]);
    if (it == word_to_id.end()) {
      word_to_id.emplace(words[i], word_to_id.size());
      id_to_word.emplace(id_to_word.size(), words[i]);
    }
    words[i] = word_to_id[words[i]];
  }
}

/// @brief 把单词列表转化为标识列表（
/// Convert a list of words to a list of identifiers）
/// @param words 单词列表（word list）
/// @param corpus 单词ID列表（list of word identifiers）
void GenCorpus(vector<string> words, int* corpus) {
  unordered_map<string, int> word_to_id;
  GenWordToID(words, word_to_id);
  for (size_t i = 0; i < words.size(); ++i) {
    corpus[i] = word_to_id[words[i]];
  }
}