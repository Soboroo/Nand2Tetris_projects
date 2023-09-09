#pragma once
#include <string>

namespace asmbl {
enum class CommandType { A_COMMAND, C_COMMAND, L_COMMAND };
class Parser {
public:
  Parser(const std::string &filename);
  ~Parser();

  bool hasMoreCommands();
  void advance();
  void reset();

  std::string commandType();
  std::string symbol();
  std::string dest();
  std::string comp();
  std::string jump();

private:
  std::ifstream m_input = std::ifstream();
  std::string m_filename = "";
  std::string m_currentCommand = "";
  std::string m_nextCommand = "";
  CommandType m_commandType;
  std::string m_symbol = "";
  std::string m_dest = "";
  std::string m_comp = "";
  std::string m_jump = "";
};
} // namespace asmbl