#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "types.h"

namespace imtools {

class Pin;
class Node;
class Link;

using NodeId = int;
using PinId = int;
using PinPtr = std::shared_ptr<Pin>;
using NodePtr = std::shared_ptr<Node>;
using NodeWeakPtr = std::weak_ptr<Node>;
using LinkPtr = std::shared_ptr<Link>;
using NodeData = std::variant<int, std::string, Pose>;

class Link : public std::enable_shared_from_this<Link> {
public:
    Link(PinPtr srcPin, PinPtr dstPin);
    ~Link();

    PinPtr srcPin();
    PinPtr dstPin();

private:
    PinPtr m_srcPin;
    PinPtr m_dstPin;
};

class Pin : public std::enable_shared_from_this<Pin> {
public:
    enum class Type {
        Int,
        String,
        Pose,
    };

    enum class Kind {
        In,
        Out,
    };

public:
    Pin() = default;
    Pin(Kind kind, Type type, PinId pinId, NodeWeakPtr node);

    ~Pin() = default;

    NodePtr tryGetHost();

    bool hasLink() const;

    std::vector<std::weak_ptr<Link>> links();

private:
    PinId m_pinId;
    Type m_type;
    Kind m_kind;
    std::weak_ptr<Node> m_hostNode;
    std::vector<std::weak_ptr<Link>> m_links;
};

class Node : public std::enable_shared_from_this<Node> {
public:
    Node() = default;
    ~Node() = default;

    void output(PinPtr pin, const NodeData &data);

    PinPtr addInputPin(Pin::Type type);
    PinPtr addOutputPin(Pin::Type type);

public:
    virtual void onInit() = 0;
    virtual void onStart() = 0;
    virtual void onStop() = 0;
    virtual void onInput(PinPtr pin, const NodeData &data) = 0;

private:
    std::unordered_map<PinId, PinPtr> m_inputPins;
    std::unordered_map<PinId, PinPtr> m_outputPins;
};

}  // namespace imtools