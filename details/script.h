#pragma once
#include "../details/angelscript/angelscript.h"

#define SCRIPT_ADD_CLASS_PROPERTY(engine, cls, type, prop) engine->RegisterObjectProperty(#cls, #type " " #prop, asOFFSET(cls, prop))
#define SCRIPT_ADD_FUNC(engine, type, func, arg) engine->RegisterGlobalFunction(#type " " #arg, asFUNCTION(func), asCALL_CDECL);
#define SCRIPT_ADD_PROPERTY(engine, type, prop) engine->RegisterGlobalProperty(#type " " #prop, &prop);
#define SCRIPT_ADD_PROPERTY_PTR(engine, type, prop) engine->RegisterGlobalProperty(#type " @" #prop, &prop);

namespace dx_engine {
	using script_engine = asIScriptEngine;
	class script_manager {
	private:
		script_engine* _p_engine = nullptr;
	public:
		script_manager() {

		}
		script_manager(const std::string& path) {
			
		}
		script_engine* get() { return _p_engine; }
	};
}