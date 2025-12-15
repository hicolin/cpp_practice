//
// Created by 81168 on 2025/12/12.
//


#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <windows.h> // 引入 SetConsoleOutputCP 和 CP_UTF8 的定义
#endif

class INode {
public:
    virtual ~INode() = default;

    virtual int64_t GetId() = 0;

    virtual int64_t GetPid() = 0;

    virtual std::string GetName() = 0;
};

template<typename T>
// requires std::is_base_of_v<INode, T>
class Node {
public:
    int64_t Id;
    int64_t Pid;
    std::string Name;
    T Data;
    std::vector<std::shared_ptr<Node<T> > > Children;

    explicit Node(T &item) : Id(item.GetId()), Pid(item.GetPid()), Name(item.GetName()), Data(item) {
    }
};

template<typename T>
std::vector<std::shared_ptr<Node<T> > > Tree(std::vector<T> &list) {
    if (list.empty()) {
        return {};
    }

    std::unordered_map<int16_t, std::shared_ptr<Node<T> > > nodeMap;
    std::vector<std::shared_ptr<Node<T> > > rootNodes;

    for (auto &item: list) {
        auto node = std::make_shared<Node<T> >(item);
        nodeMap[item.GetId()] = node;
    }

    for (auto &item: list) {
        int64_t id = item.GetId();
        int16_t pid = item.GetPid();

        // Node<T>* node = nodeMap[id].get();

        if (pid == 0) {
            rootNodes.push_back(nodeMap[id]);
        } else {
            auto parentIt = nodeMap.find(pid);
            if (parentIt != nodeMap.end()) {
                parentIt->second->Children.push_back(nodeMap[id]);
            }
        }
    }

    return rootNodes;
}

class MyNode : public INode {
public:
    int64_t Id;
    int64_t Pid;
    std::string Name;

    explicit MyNode(const int64_t id, const int64_t pid, std::string name) : Id(id), Pid(pid), Name(std::move(name)) {
    }

    int64_t GetId() override {
        return Id;
    }

    int64_t GetPid() override {
        return Pid;
    }

    std::string GetName() override {
        return Name;
    }

    void Print() const {
        std::cout << "Id: " << Id << ", Pid: " << Pid << ", Name: " << Name << std::endl;
    }
};

template<typename T>
void PrintTree(Node<T> *node, const int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }

    std::cout << node->Name << "(id: " << node->Id << ")" << std::endl;

    for (const auto &child: node->Children) {
        PrintTree(child.get(), depth + 1);
    }
}

int main() {
    // system("chcp 65001");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::vector<MyNode> nodes = {
        MyNode(1, 0, "根节点1"),
        MyNode(2, 0, "根节点2"),
        MyNode(3, 1, "子节点1-1"),
        MyNode(4, 3, "子节点1-1-1"),
        MyNode(5, 2, "子节点2-1"),
    };

    auto treeRoots = Tree(nodes);

    std::cout << "树结构:" << std::endl;
    for (const auto &root: treeRoots) {
        PrintTree(root.get());
    }
}
