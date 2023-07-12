#pragma once

#include <Python3.10/Python.h>
#include <pybind11/pybind11.h>

namespace imtools {

class IScript {
public:
    virtual ~IScript() = default;
    virtual void load() = 0;
    virtual void unload() = 0;
};

class ScriptPython : public IScript {
public:
    ScriptPython(const std::string& scriptName);
    ~ScriptPython();

    // 实现 IScript
    void load() override;
    void unload() override;

private:
    pybind11::object m_scriptLoad;
    pybind11::object m_scriptUnload;
};

} // imtools