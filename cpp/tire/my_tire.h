#ifndef MY_TIRE_H__
#define MY_TIRE_H__

#include <cstdint>
#include <map>
#include <string>

namespace qy {

class Node;

class Tire {
 public:
  Tire();
  ~Tire();
  void Subscribe(const uint8_t *data, size_t size);
  void UnSubscribe(const uint8_t *data, size_t size);
  bool Match(const uint8_t *data, size_t size);

 private:
  Tire(const Tire &) = delete;
  Tire &operator=(const Tire &) = delete;
  Node *root_;
};

}  // namespace qy

#endif  // MY_TIRE_H__