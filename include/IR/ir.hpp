#pragma once

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace IR {

struct Struct;

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
	Allocator,
	Array,
	Equal_to,
	Greater,
	Hash,
	Less,
	Map,
	Pair,
	Set,
	Tuple,
	Unordered_map,
	Unordered_set,
	Vector,
};

enum class AccessModifier {
	Public,
	Private,
	Protected,
};

struct Enum {
	std::string m_name;
	// Fully qualified name
	std::string m_representation;
	// Unscoped values
	std::vector<std::string> m_values;
	// True if it was declared as 'enum class'
	bool m_isScoped;
};

struct Type {
	struct Container {
		ContainerType m_container;
		std::vector<Type> m_containedTypes;
	};

	struct Value {
		BaseType m_base;
	};

	struct UserDefined {
		// Fully qualified name of the struct
		std::string m_representation;
	};

	// Either it is a value with some type,
	// or it is a container ultimately containing a value type
	std::variant<Value, Container, UserDefined> m_type;

	// This is what the user wrote, removing any using's
	std::string m_representation;

	// Qualifiers
	bool m_isConst;

	// The numbers of pointers on this variable.
	// Ex:
	//      int* a;
	//        => m_numPointers = 1
	//      int*** a;
	//        => m_numPointers = 3
	int m_numPointers = 0;

	// Ex true for:
	//     std::string& someoneElsesString;
	bool m_isReference;
};

struct Variable {
	// Name that should be used to access the variable
	std::string m_name;

	Type m_type;
};

struct Function {
	// Name that should be used to access the function
	std::string m_name;

	// This is the full name of the function
	// E.g. MyNamespace::myFunction
	std::string m_representation;

	Type m_returnType;

	std::vector<Variable> m_arguments;
};

struct Struct {
	// NOTE: Structs are interpreted the same as classes
	std::string m_name;

	// This is the full name of the struct/class
	// E.g. MyNamespace::MyClass
	std::string m_representation;

	std::vector<std::pair<AccessModifier, Function>> m_functions;
	std::vector<std::pair<AccessModifier, Variable>> m_memberVariables;
	std::vector<std::pair<AccessModifier, Enum>> m_enums;
	std::vector<Struct> m_structs;

	bool m_hasImplicitDefaultConstructor;
};

struct Namespace {
	// NOTE: The name might be "" if it is the global namespace
	std::string m_name;

	// This is the full name of the namespace
	// E.g. SomeNamespace::OtherNamespace::ThisNamespace
	std::string m_representation;

	std::vector<Namespace> m_namespaces;
	std::vector<Struct> m_structs;
	std::vector<Function> m_functions;
	std::vector<Enum> m_enums;
};
}
