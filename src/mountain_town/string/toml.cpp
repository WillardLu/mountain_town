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
  // 打开文件
  FILE *fp;
  fp = fopen(file.c_str(), "rb");
  if (fp == NULL) {
    return "Failed to open " + file + ".\n";
  }
  fseek(fp, 0, SEEK_END);
  size_t data_size = ftell(fp);
  rewind(fp);
  char *buffer = new char[data_size];
  if (buffer == NULL) {
    fclose(fp);
    return "Memory allocation failed.\n";
  }
  // 从文件读取数据
  size_t result = fread(buffer, 1, data_size, fp);
  if (result != data_size) {
    delete[] buffer;
    fputs("Reading error", stderr);
    fclose(fp);
    return "Failed to read data.\n";
  }
  fclose(fp);
  // 直接赋值会造成内存泄漏
  string ori = CharArrConvertToString(buffer, data_size, data_size);
  delete[] buffer;

  string table_name;
  string key;
  string value;
  string table_left_tag = "<<table-left>>";
  string table_right_tag = "<<table-right>>";
  // 1. 去掉注释、空行和每行左右的空格，在表头前后加上标记，把多行数组换成一行。
  vector<string> lines = SplitStr(ori, "\n");
  ori = "";
  for (size_t i = 0; i < lines.size(); i++) {
    // 从lines中读取一行文本，并把末尾的回车去掉
    string per_line = RTrim(lines[i], "\x0d");
    if (per_line[0] == '#') continue;
    if (per_line[0] == '[') {
      per_line = table_left_tag + per_line + table_right_tag;
    }
    int end = per_line.size() - 1;
    string ender = per_line[end] == '[' || per_line[end] == ',' ? "" : "\n";
    ori += Trim(per_line, " ") + ender;
  }
  // 2. 按照标记拆分字符串，分离出各个表
  vector<string> tables = SplitStr(ori, table_left_tag);
  if (tables.size() == 0) {
    return "There is no content in the configuration file.\n";
  }  
  for (auto &table : tables) {
    string table1 = Trim(table, " ");
    if (table1.empty()) continue;  // 忽略空内容
    // 3. 按照标记把表头与内容分离
    vector<string> content = SplitStr(table1, table_right_tag);
    // 获得表头名称
    table_name = RTrim(LTrim(content[0], "["), "]");
    // 4. 按照“\n”拆分字符串，分出逐条内容
    vector<string> items = SplitStr(content[1], "\n");
    for (auto &item : items) {
      if (item.empty()) continue;  // 忽略空内容
      // 5. 按照“=”拆分字符串，分出键名与键值
      vector<string> key_value = SplitStr(item, "=");
      if (key_value[0].empty()) continue;   // 忽略空键名
      if (key_value.size() != 2) continue;  // 键名与键值不成对的忽略
      key = Trim(key_value[0], " ");
      // 去掉左右的空格与双引号。对于字符串数组，最右边的双引号也会被去掉。
      value = Trim(Trim(key_value[1], " "), "\"");
      // 特别针对数组，去掉左右两边的中括号、空格与逗号，进一步的处理交给其他函数。
      value = LTrim(value, "[");
      value = RTrim(value, "]");
      value = Trim(value, " ");
      value = Trim(value, ",");
      config[table_name + "." + key] = value;
    }
  }
  return "";
}

/// @brief 读取从TOML文件中获取的数组
/// @param str 源数组字符串
/// @param arr 数组
void ReadSTOMLArr(string str, vector<string> &arr) {
  // 按照逗号拆分
  arr = SplitStr(str, ",");
  for (auto substr1 = arr.begin(); substr1 != arr.end(); ++substr1) {
    // 去掉两边的空格与双引号
    *substr1 = Trim(*substr1, " ");
    *substr1 = Trim(*substr1, "\"");
  }
}