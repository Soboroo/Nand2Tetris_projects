#pragma once
#include <string>

namespace asmbl {
	class Code {
	public:
		static std::string dest(const std::string& mnemonic);
		static std::string comp(const std::string& mnemonic);
		static std::string jump(const std::string& mnemonic);
	};
} // namespace asmbl