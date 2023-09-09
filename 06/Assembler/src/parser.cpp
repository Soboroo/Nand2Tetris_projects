#include "../include/parser.h"
#include <fstream>
#include <iostream>

asmbl::Parser::Parser(const std::string &filename)
    : m_filename(filename) {
  m_input.open(m_filename);
	if (!m_input.is_open()) {
    throw "File could not be opened.";
  }
}

asmbl::Parser::~Parser() { m_input.close(); }

bool asmbl::Parser::hasMoreCommands() {
	if (m_nextCommand != "") {
		return true;
	}
	std::string line;
	if (std::getline(m_input, line)) {
		m_nextCommand = line;
		return true;
	}
	return false;
}

void asmbl::Parser::advance() {
  if (m_nextCommand != "") {
    m_currentCommand = m_nextCommand;
    m_nextCommand = "";
  } else {
    std::string line;
    if (std::getline(m_input, line)) {
      m_currentCommand = line;
    }
  }
}

void asmbl::Parser::reset() {
	m_input.clear();
	m_input.seekg(0, std::ios::beg);
	m_currentCommand = "";
	m_nextCommand = "";
	m_commandType = CommandType::A_COMMAND;
	m_symbol = "";
	m_dest = "";
	m_comp = "";
	m_jump = "";
}

std::string asmbl::Parser::commandType() {
	if (m_currentCommand[0] == '@') {
		m_commandType = CommandType::A_COMMAND;
	} else if (m_currentCommand[0] == '(') {
		m_commandType = CommandType::L_COMMAND;
	} else {
		m_commandType = CommandType::C_COMMAND;
	}
	return m_currentCommand;
}

std::string asmbl::Parser::symbol() {
	if (m_commandType == CommandType::A_COMMAND) {
		m_symbol = m_currentCommand.substr(1);
	} else if (m_commandType == CommandType::L_COMMAND) {
		m_symbol = m_currentCommand.substr(1, m_currentCommand.size() - 2);
	}
	return m_symbol;
}

std::string asmbl::Parser::dest() {
	if (m_commandType == CommandType::C_COMMAND) {
		size_t pos = m_currentCommand.find('=');
		if (pos != std::string::npos) {
			m_dest = m_currentCommand.substr(0, pos);
		}
	}
	return m_dest;
}

std::string asmbl::Parser::comp() {
	if (m_commandType == CommandType::C_COMMAND) {
		size_t pos = m_currentCommand.find('=');
		if (pos != std::string::npos) {
			m_comp = m_currentCommand.substr(pos + 1);
		} else {
			pos = m_currentCommand.find(';');
			if (pos != std::string::npos) {
				m_comp = m_currentCommand.substr(0, pos);
			}
		}
	}
	return m_comp;
}

std::string asmbl::Parser::jump() {
	if (m_commandType == CommandType::C_COMMAND) {
		size_t pos = m_currentCommand.find(';');
		if (pos != std::string::npos) {
			m_jump = m_currentCommand.substr(pos + 1);
		}
	}
	return m_jump;
}