#pragma once

#include <memory>
#include <process.hpp>

#include "node.h"

namespace imtools {

class ProcessNode : public Node {
public:
    ProcessNode(std::string command);
    ~ProcessNode();

    void onInit() override;
    void onStart() override;
    void onStop() override;
    void onInput(PinPtr pin, const NodeData &data) override;

private:
    void onProcessStdout(const char *bytes, size_t n);
    void onProcessStderr(const char *bytes, size_t n);

private:
    std::unique_ptr<TinyProcessLib::Process> m_process;
    PinPtr m_stdoutPin;
    PinPtr m_stderrPin;
};

}  // namespace imtools
