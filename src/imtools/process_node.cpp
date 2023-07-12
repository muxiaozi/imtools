#include "process_node.h"

#include <spdlog/spdlog.h>

namespace imtools {

ProcessNode::ProcessNode(std::string command) {
}

ProcessNode::~ProcessNode() {
    // onStop();
}

void ProcessNode::onInit() {
    m_stdoutPin = addOutputPin(Pin::Type::String);
    m_stderrPin = addOutputPin(Pin::Type::String);
}

void ProcessNode::onStart() {
    onStop();
    m_process = std::make_unique<TinyProcessLib::Process>(std::vector<std::string>{"adb", "logcat"}, "",
                                                          std::bind(&ProcessNode::onProcessStdout, this, std::placeholders::_1, std::placeholders::_2),
                                                          std::bind(&ProcessNode::onProcessStderr, this, std::placeholders::_1, std::placeholders::_2));
}

void ProcessNode::onStop() {
    if (m_process) {
        SPDLOG_WARN("killing process");
        m_process->kill();
        m_process.reset();
    }
}

void ProcessNode::onInput(PinPtr pin, const NodeData &data) {
}

void ProcessNode::onProcessStdout(const char *bytes, size_t n) {
    SPDLOG_INFO("output: {}", std::string(bytes, n - 1));
    output(m_stdoutPin, std::string(bytes, n - 1));
}

void ProcessNode::onProcessStderr(const char *bytes, size_t n) {
    SPDLOG_INFO("error: {}", std::string(bytes, n - 1));
}

}  // namespace imtools