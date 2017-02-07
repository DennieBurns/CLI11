#pragma once

// Distributed under the LGPL version 3.0 license.  See accompanying
// file LICENSE or https://github.com/henryiii/CLI11 for details.

#include <string>
#include <exception>
#include <stdexcept>

namespace CLI {

// Error definitions

/// All errors derive from this one
struct Error : public std::runtime_error {
    int exit_code;
    bool print_help;
    Error(std::string parent, std::string name, int exit_code=255, bool print_help=true) : runtime_error(parent + ": " + name), exit_code(exit_code), print_help(print_help) {}
};

/// This is a successful completion on parsing, supposed to exit
struct Success : public Error {
    Success() : Error("Success", "Successfully completed, should be caught and quit", 0, false) {}
};

/// -h or --help on command line
struct CallForHelp : public Error {
    CallForHelp() : Error("CallForHelp", "This should be caught in your main function, see examples", 0) {}
};

// Construction errors (not in parsing)

struct ConstructionError : public Error {
    using Error::Error;
};

/// Thrown when an option is set to conflicting values (non-vector and multi args, for example)
struct IncorrectConstruction : public ConstructionError {
    IncorrectConstruction(std::string name) : ConstructionError("ConstructionError", name, 8) {}
};

/// Thrown on construction of a bad name
struct BadNameString : public ConstructionError {
    BadNameString(std::string name) : ConstructionError("BadNameString", name, 1) {}
};

/// Thrown when an option already exists
struct OptionAlreadyAdded : public ConstructionError {
    OptionAlreadyAdded(std::string name) : ConstructionError("OptionAlreadyAdded", name, 3) {}
};

// Parsing errors

struct ParseError : public Error {
    using Error::Error;
};

/// Thrown when conversion call back fails, such as when an int fails to coerse to a string
struct ConversionError : public ParseError {
    ConversionError(std::string name) : ParseError("ConversionError", name, 2) {}
};

/// Thrown when a required option is missing
struct RequiredError : public ParseError {
    RequiredError(std::string name) : ParseError("RequiredError", name, 5) {}
};

/// Thrown when too many positionals are found
struct PositionalError : public ParseError {
    PositionalError(std::string name) : ParseError("PositionalError", name, 6) {}
};

/// This is just a safety check to verify selection and parsing match
struct HorribleError : public ParseError {
    HorribleError(std::string name) : ParseError("HorribleError", "(You should never see this error) " + name, 7) {}
};

/// Thrown when counting a non-existent option
struct OptionNotFound : public Error {
    OptionNotFound(std::string name) : Error("OptionNotFound", name, 4) {}
};


}
