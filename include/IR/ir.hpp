#pragma once

#include <string>
#include <vector>

namespace IR {

// The supported types that can be converted
enum class Type {
	Char,
	Double,
	Float,
	Int,
	Long,
	String,
};

enum class Qualifier {
	Const,
};

struct Variable {
	// Name that should be used to access the variable
	std::string m_name;
	// Type of the variable, int, double, ...
	Type m_type;

	// Could be const, ...
	std::vector<Qualifier> m_qualifiers;

	// The numbers of pointers on this variable.
	// Ex:
	//      int* a;
	//        => m_numPointers = 1
	//      int*** a;
	//        => m_numPointers = 3
	int m_numPointers;
};

struct Function {
	// Name that should be used to access the function
	std::string m_name;
	// Return type of the function, int, double, ...
	Type m_returnType;

	std::vector<Variable> m_arguments;
};

struct Struct {
	// NOTE: Structs are interpreted the same as classes
	std::string m_name;

	// NOTE: Might need to add public/protected/private
	std::vector<Function> m_functions;
	std::vector<Variable> m_memberVariables;
};

struct Namespace {
	// NOTE: The name might be "" if it is the global namespace
	std::string m_name;
	std::string m_parent;

	std::vector<Struct> m_structs;
	std::vector<Function> m_functions;
	std::vector<Variable> m_constants;
};
}
