#pragma once

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace IR {

enum class BaseType {
	Char,
	Double,
	Float,
	Int,
	Long,
	String,
	Void,
};

enum class ContainerType {
	Array,
	Map,
	Set,
	Unordered_map,
	Unordered_set,
	Vector,
};

enum class Qualifier {
	Const,
};

struct Type {
	struct Container {
		ContainerType m_containerType;
		Type* m_containedType = nullptr;
	};

	struct Value {
		BaseType m_valueType;
		// Some containers have keys
		std::optional<BaseType> m_keyType;
	};
	// Either it is a value with some type,
	// or it is a container ultimately containing a value type
	std::variant<Value, Container> m_type;

	// Could be const, ...
	std::vector<Qualifier> m_qualifiers;

	// The numbers of pointers on this variable.
	// Ex:
	//      int* a;
	//        => m_numPointers = 1
	//      int*** a;
	//        => m_numPointers = 3
	int m_numPointers = 0;
};

struct Variable {
	// Name that should be used to access the variable
	std::string m_name;
	// Type of the variable, int, double, ...
	Type m_type;
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
	std::vector<Struct> m_structs;
};

struct Namespace {
	// NOTE: The name might be "" if it is the global namespace
	std::string m_name;
	std::string m_parent;

	std::vector<Namespace> m_namespaces;
	std::vector<Struct> m_structs;
	std::vector<Function> m_functions;
	std::vector<Variable> m_constants;
};
}
