#include "my_tire.h"

#include <map>
#include <string>
#include <utility>

namespace qy {

class Node {
 public:
  Node();
  ~Node();

  void Subscribe(const uint8_t *data, size_t size);
  bool UnSubscribe(const uint8_t *data, size_t size);
  bool Match(const uint8_t *data, size_t size) const;

  Node(const Node &) = delete;
  Node &operator=(const Node &) = delete;

 private:
  void SplitWith(const uint8_t *data, size_t size);
  void TryToComat();
  void swap(Node &node);

  size_t ref_count_;
  std::string prefix_;
  std::map<uint8_t, Node *> childrens_;
};

Node::Node() { ref_count_ = 0; }

Node::~Node() {
  if (!childrens_.empty()) {
    for (auto i = childrens_.begin(); i != childrens_.end(); ++i) {
      delete i->second;
    }
    childrens_.clear();
  }

  prefix_.clear();
  ref_count_ = 0;
}

void Node::swap(Node &node) {
  std::swap(this->ref_count_, node.ref_count_);
  std::swap(this->prefix_, node.prefix_);
  std::swap(this->childrens_, node.childrens_);
}

void Node::SplitWith(const uint8_t *data, size_t size) {
  uint8_t ch = prefix_[size];
  auto children = new Node();
  children->swap(*this);
  children->prefix_ = children->prefix_.substr(size + 1);
  this->prefix_.assign((const char *)data, size);
  this->childrens_[ch] = children;
}

void Node::Subscribe(const uint8_t *data, size_t size) {
  size_t pos = 0;
  for (; pos < prefix_.size() && pos < size; ++pos) {
    if (data[pos] != prefix_[pos]) {
      break;
    }
  }
  bool this_has_left = prefix_.size() > pos;
  bool data_has_left = size > pos;

  if (!this_has_left && !data_has_left) {
    ref_count_++;
  } else if (this_has_left && !data_has_left) {
    this->SplitWith(data, size);
    ref_count_++;
  } else if (!this_has_left && data_has_left) {
    if (prefix_.size() == 0 && ref_count_ == 0 && childrens_.empty()) {
      this->prefix_.assign(reinterpret_cast<const char *>(data), size);
      ref_count_++;
    } else {
      size -= pos;
      data += pos;

      uint8_t ch = data[0];
      Node *children = NULL;
      if (childrens_.find(ch) == childrens_.end()) {
        children = new Node();
        childrens_[ch] = children;
      } else {
        children = childrens_.find(ch)->second;
      }
      children->Subscribe(data + 1, size - 1);
    }
  } else if (this_has_left && data_has_left) {
    this->SplitWith(data, pos);

    size -= pos;
    data += pos;

    uint8_t ch = data[0];
    Node *children = NULL;
    if (childrens_.find(ch) == childrens_.end()) {
      children = new Node();
      childrens_[ch] = children;
    } else {
      children = childrens_.find(ch)->second;
    }
    children->Subscribe(data + 1, size - 1);
  }
}

bool Node::UnSubscribe(const uint8_t *data, size_t size) {
  size_t pos = 0;
  for (; pos < prefix_.size() && pos < size; ++pos) {
    if (data[pos] != prefix_[pos]) {
      break;
    }
  }
  bool this_has_left = prefix_.size() > pos;
  bool data_has_left = size > pos;

  // 并没订阅，直接返回
  if (this_has_left) {
    return false;
  }
  if (!data_has_left) {
    ref_count_--;
  } else {
    if (childrens_.empty()) {
      return false;
    }
    size -= pos;
    data += pos;

    uint8_t ch = data[0];
    Node *children = NULL;
    auto it = childrens_.find(ch);
    if (it != childrens_.end()) {
      if (it->second->UnSubscribe(data + 1, size - 1)) {
        delete it->second;
        childrens_.erase(it);
      }
    }
  }
  TryToComat();
  return childrens_.size() == 0 && ref_count_ == 0;
}

void Node::TryToComat() {
  if (0 == ref_count_ && childrens_.size() == 1) {
    Node *child = childrens_.begin()->second;
    std::string new_prefix = prefix_ +
                             static_cast<char>(childrens_.begin()->first) +
                             childrens_.begin()->second->prefix_;
    this->childrens_.clear();
    this->swap(*child);
    this->prefix_ = new_prefix;
    delete child;
  }
}

bool Node::Match(const uint8_t *data, size_t size) const {
  size_t pos = 0;
  for (; pos < prefix_.size() && pos < size; ++pos) {
    if (data[pos] != prefix_[pos]) {
      break;
    }
  }
  bool this_has_left = prefix_.size() > pos;
  bool data_has_left = size > pos;

  if (this_has_left) {
    return false;
  } else {
    if (0 != ref_count_) {
      return true;
    }
    if (!data_has_left) {
      return false;
    }
    if (childrens_.empty()) {
      return false;
    }
    data += pos;
    size -= pos;
    auto it = childrens_.find(data[0]);
    if (it != childrens_.end()) {
      return it->second->Match(data + 1, size - 1);
    }
    return false;
  }
}

Tire::Tire() : root_(NULL) {}

Tire::~Tire() {
  if (!root_) {
    delete root_;
    root_ = NULL;
  }
}

void Tire::Subscribe(const uint8_t *data, size_t size) {
  if (!root_) {
    root_ = new Node();
  }
  root_->Subscribe(data, size);
}

void Tire::UnSubscribe(const uint8_t *data, size_t size) {
  if (root_) {
    if (root_->UnSubscribe(data, size)) {
      delete root_;
      root_ = NULL;
    }
  }
}

bool Tire::Match(const uint8_t *data, size_t size) {
  if (!root_) return false;
  return root_->Match(data, size);
}

}  // namespace qy
