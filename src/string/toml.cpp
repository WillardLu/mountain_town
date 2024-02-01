// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include "toml.h"

/// @brief 读取简化版TOML配置文件中的所有配置
/// @param file TOML配置文件
/// @param config 存放读取到的配置内容
/// @return 错误信息
/// @remark 所有配置内容都当作字符串返回
string ReadSTOML(string file, std::unordered_map<string, string> &config) {
  std::ifstream fp(file, std::ios::in | std::ios::ate);
  // 打开文件
  if (fp.is_open() == false) {
    return "Failed to open " + file + ".\n";
  }
  int data_size = (int)fp.tellg();
  char *buffer = new char[data_size];
  if (buffer == nullptr) {
    fp.close();
    return "Memory allocation failed.\n";
  }
  // 从文件读取数据
  fp.seekg(0);  // 把文件指针调回开头
  if (!fp.read(buffer, data_size)) {
    delete[] buffer;
    fp.close();
    return "Failed to read data.\n";
  }
  fp.close();
  string ori = buffer;
  delete[] buffer;

  string table;
  string key;
  string value;
  // 1. 按照“[”拆分字符串，分出表
  vector<string> str1 = SplitStr(ori, "[");
  if (str1.size() <= 1) return "No content.";  // 没有内容
  for (auto substr1 = str1.begin() + 1; substr1 != str1.end(); ++substr1) {
    // 2. 按照“]”拆分字符串，分出表头与内容
    string str_temp1 = Trim(*substr1, " ");
    if (str_temp1.empty() == true) continue;  // 忽略空内容
    vector<string> str2 = SplitStr(str_temp1, "]");
    if (str1.size() <= 1) continue;  // 没有内容，跳过
    table = Trim(str2[0], " ");
    for (auto substr2 = str2.begin() + 1; substr2 != str2.end(); ++substr2) {
      // 3. 按照“\n”拆分字符串，分出逐条内容
      string str_temp2 = Trim(*substr2, " ");
      if (str_temp2.empty() == true) continue;  // 忽略空内容
      vector<string> str3 = SplitStr(str_temp2, "\n");
      for (auto substr3 = str3.begin(); substr3 != str3.end(); ++substr3) {
        // 4. 按照“=”拆分字符串，分出键名与键值
        string str_temp3 = Trim(*substr3, " ");
        if (str_temp3.empty() == true) continue;  // 忽略空内容
        vector<string> str4 = SplitStr(str_temp3, "=");
        if (str4[0].empty() == true) continue;  // 忽略空键名
        if (str4.size() != 2) continue;  // 键名与键值不成对的忽略
        key = Trim(str4[0], " ");
        value = Trim(Trim(str4[1], " "), "\"");
        config[table + "." + key] = value;
      }
    }
  }

  return "";
}