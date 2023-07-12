#include "node.h"

namespace imtools {

Link::Link(PinPtr srcPin, PinPtr dstPin) : m_srcPin(std::move(srcPin)), m_dstPin(std::move(dstPin)) {
}

Link::~Link() {
}

PinPtr Link::srcPin() {
    return m_srcPin;
}

PinPtr Link::dstPin() {
    return m_dstPin;
}

Pin::Pin(Kind kind, Type type, PinId pinId, NodeWeakPtr node) : m_kind(kind), m_type(type), m_pinId(pinId), m_hostNode(node) {
}

NodePtr Pin::tryGetHost() {
    return m_hostNode.lock();
}

bool Pin::hasLink() const {
    return !m_links.empty();
}

std::vector<std::weak_ptr<Link>> Pin::links() {
    return m_links;
}

void Node::output(PinPtr pin, const NodeData &data) {
    for (auto &l : pin->links()) {
        auto link = l.lock();
        if (!link) {
            continue;
        }
        auto dstPin = link->dstPin();
        if (!dstPin) {
            continue;
        }
        auto dstNode = dstPin->tryGetHost();
        if (!dstNode) {
            continue;
        }
        dstNode->onInput(dstPin, data);
    }
}

PinPtr Node::addInputPin(Pin::Type type) {
    PinId pinId = 0;
    auto pin = std::make_shared<Pin>(Pin::Kind::In, type, pinId, weak_from_this());
    m_inputPins[pinId] = pin;
    return pin;
}

PinPtr Node::addOutputPin(Pin::Type type) {
    PinId pinId = 0;
    auto pin = std::make_shared<Pin>(Pin::Kind::Out, type, pinId, weak_from_this());
    m_outputPins[pinId] = pin;
    return pin;
}

}  // namespace imtools