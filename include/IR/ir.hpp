#include <string>
#include <vector>

namespace IR {
struct Variable {
	// Name that should be used to access the variable
	std::string m_name;
	// Type of the variable, int, double, ...
	std::string m_type;
};

struct Function {
	// Name that should be used to access the function
	std::string m_name;
	// Return type of the function, int, double, ...
	std::string m_returnType;

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

	std::vector<Struct> m_structs;
	std::vector<Function> m_functions;
	std::vector<Variable> m_constants;
};
}
