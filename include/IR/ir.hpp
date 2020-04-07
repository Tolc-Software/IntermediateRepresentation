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
	Array,
	Map,
	Set,
	Unordered_map,
	Unordered_set,
	Vector,
};

enum class AccessModifier {
	Public,
	Private,
	Protected,
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

	struct UserDefined {
		Struct const* m_struct;
	};

	// Either it is a value with some type,
	// or it is a container ultimately containing a value type
	std::variant<Value, Container, UserDefined> m_type;

	// This is what the user wrote
	std::string m_representaion;

	// Qualifiers
	bool m_isConst;

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

	Type m_type;
};

struct Function {
	// Name that should be used to access the function
	std::string m_name;

	// This is the full name of the function
	// E.g. MyNamespace::myFunction
	std::string m_representaion;

	Type m_returnType;

	std::vector<Variable> m_arguments;
};

struct Struct {
	// NOTE: Structs are interpreted the same as classes
	std::string m_name;

	// This is the full name of the struct/class
	// E.g. MyNamespace::MyClass
	std::string m_representaion;

	std::vector<std::pair<AccessModifier, Function>> m_functions;
	std::vector<std::pair<AccessModifier, Variable>> m_memberVariables;
	std::vector<Struct> m_structs;
};

struct Namespace {
	// NOTE: The name might be "" if it is the global namespace
	std::string m_name;
	// NOTE: All parents of namespaces are namespaces
	std::string m_parent;

	// This is the full name of the namespace
	// E.g. SomeNamespace::OtherNamespace::ThisNamespace
	std::string m_representaion;

	std::vector<Namespace> m_namespaces;
	std::vector<Struct> m_structs;
	std::vector<Function> m_functions;
};
}
