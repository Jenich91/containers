#ifndef SRC_NODE_H_
#define SRC_NODE_H_
namespace sfleta_ {
template <typename T>
class Node {
 public:
  T data_;
  Node *pNext_;
  Node *pPrev_;
  Node(): data_(), pNext_(nullptr), pPrev_(nullptr) {}
  explicit Node(const T &data) : Node() {data_ = data;}
};
}  // namespace sfleta_
#endif  // SRC_NODE_H_
