#include "tree.h"

#include <queue>

class NodeComparator {
public:
    bool operator()(std::shared_ptr<HuffmanNode> a,
                    std::shared_ptr<HuffmanNode> b) const {
        if (a->frequency == b->frequency) {
            return a->symbol > b->symbol;
        }
        return a->frequency > b->frequency;
    }
};

HuffmanNode::HuffmanNode(std::size_t frequency, char symbol) :
    frequency(frequency), symbol(symbol),
    left(nullptr), right(nullptr) {}

HuffmanNode::HuffmanNode(std::shared_ptr<HuffmanNode> left,
                         std::shared_ptr<HuffmanNode> right) :
    frequency(left->frequency + right->frequency), symbol(0),
    left(left), right(right) {}

bool HuffmanNode::is_list() const {
    return left == nullptr;
}

void HuffmanNode::get_codes(CodeArray &codes, std::vector<char> &current_code) const {
    if (is_list()) {
        codes[symbol] = current_code;
    } else {
        current_code.push_back(0);
        left->get_codes(codes, current_code);
        current_code.pop_back();

        current_code.push_back(1);
        right->get_codes(codes, current_code);
        current_code.pop_back();
    }
}

HuffmanTree::HuffmanTree(FreqArray const &frequencies) {
    build(frequencies);
}

void HuffmanTree::build(FreqArray const &frequencies) {
    std::priority_queue<std::shared_ptr<HuffmanNode>,
                        std::vector<std::shared_ptr<HuffmanNode>>,
                        NodeComparator> sorted_nodes;
    for (std::size_t i = 0; i < frequencies.size(); i++) {
        if (frequencies[i] > 0) {
            sorted_nodes.push(std::make_shared<HuffmanNode>(frequencies[i], i));
        }
    }
    if (sorted_nodes.empty()) {
        root = std::make_shared<HuffmanNode>(0, 0);
        return;
    }

    while (sorted_nodes.size() > 1) {
        auto first = sorted_nodes.top();
        sorted_nodes.pop();
        auto second = sorted_nodes.top();
        sorted_nodes.pop();
        sorted_nodes.push(std::make_shared<HuffmanNode>(first, second));
    }
    root = sorted_nodes.top();
}

void HuffmanTree::get_codes(CodeArray &codes) const {
    std::vector<char> tmp;
    root->get_codes(codes, tmp);
}

void HuffmanTree::decode(std::size_t count, InBitStream &bit_is, std::ostream &os) const {
    auto current = root;
    while (count > 0) {
        if (current->is_list()) {
            os.put(current->symbol);
            count--;
            current = root;
            continue;
        }
        bool side;
        bit_is >> side;
        if (side == 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
}
