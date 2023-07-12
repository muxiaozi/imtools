#include "script_python.h"

namespace imtools {

namespace py = pybind11;

ScriptPython::ScriptPython(const std::string& scriptName) {
    py::module_ plugin = py::module_::import(scriptName.data());

    // TODO: 如果plugin被释放，方法还有效吗？
    m_scriptLoad = plugin.attr("script_load");
    m_scriptUnload = plugin.attr("script_unload");
}

ScriptPython::~ScriptPython() {
}

void ScriptPython::load()
{
    
}

void ScriptPython::unload()
{
    
}


} // namespace imtools