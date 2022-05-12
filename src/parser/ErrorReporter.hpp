// This file is part of the lizard quantum chemistry software.
// Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file at the root of the lizard source
// tree or at <https://github.com/Krzmbrzl/lizard/blob/main/LICENSE>.

#ifndef LIZARD_PARSER_ERRORREPORTER_HPP_
#define LIZARD_PARSER_ERRORREPORTER_HPP_

#include <BaseErrorListener.h>

#include <string>
#include <string_view>
#include <exception>
#include <iosfwd>

namespace antlr4 {
	class Recognizer;
	class Token;
}

namespace lizard::parser {

/**
 * A class used for error reporting in ANTLR-based parsers. Instead of printing the error message to std:cerr,
 * this implementation will throw a ParseException as soon as the first error is encountered. Thus, using this
 * class has a similar effect than using a BailErrorStrategy, but with the distinction that the parser will
 * still attempt to recover from errors, during which case it'll produce actually helpful error messages, which
 * will be passed to the thrown exception (BailErrorStrategy usually doesn't provide an error message at all).
 */
class ErrorReporter : public antlr4::BaseErrorListener {
public:
	ErrorReporter(std::string_view fileName = "");
	~ErrorReporter() = default;

	virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, std::size_t line,
							 std::size_t column, const std::string &msg, std::exception_ptr e) override;

protected:
	std::string m_fileName;
};

} // namespace lizard::parser

#endif // LIZARD_PARSER_ERRORREPORTER_HPP_
