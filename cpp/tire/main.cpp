#include "my_tire.h"

#include <cassert>
#include <iostream>

using namespace qy;

void test() {
  int rc;
	Tire *trie;

#define nn_trie_init(a) *a = new Tire()
#define nn_trie_match(tire, data, size) (((*tire)->Match(data, size)) ? 1 : 0)
#define nn_assert(expr) assert(expr)
#define nn_trie_term(tire) delete (*tire);

  // in fact , all sub return 1
#define nn_trie_subscribe(tire, data, size) ((*tire)->Subscribe(data, size), 1)
#define nn_trie_unsubscribe(tire, data, size)                                  \
  ((*tire)->UnSubscribe(data, size), 1)

  /*  Try matching with an empty trie. */
  nn_trie_init(&trie);
  rc = nn_trie_match(&trie, (const uint8_t *)"", 0);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"ABC", 3);
  nn_assert(rc == 0);
  nn_trie_term(&trie);

  /*  Try matching with "all" subscription. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"", 0);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"", 0);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"ABC", 3);
  nn_assert(rc == 1);
  nn_trie_term(&trie);

  /*  Try some simple matching. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"ABC", 3);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"DEF", 3);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"AB", 2);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"ABC", 3);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"ABCDE", 5);
  nn_assert(rc == 1);
  nn_trie_term(&trie);

  /*  Try a long subcsription. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(
      &trie, (const uint8_t *)"01234567890123456789012345678901234", 35);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"", 0);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"012456789", 10);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"012345678901234567", 18);
  nn_assert(rc == 0);
  rc = nn_trie_match(
      &trie, (const uint8_t *)"01234567890123456789012345678901234", 35);
  nn_assert(rc == 1);
  nn_trie_term(&trie);

  /*  Try matching with a sparse node involved. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"ABC", 3);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"ADE", 3);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"AD", 2);
  nn_assert(rc == 0);
  nn_trie_term(&trie);

  /*  Try matching with a dense node involved. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"B", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"C", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"0", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"E", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"F", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"1", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"@", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"b", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"f", 1);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"0", 1);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"f", 1);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"000", 3);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"a", 1);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"c", 1);
  nn_assert(rc == 0);
  nn_trie_term(&trie);

  /*  Check prefix splitting and compaction. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"ABCD", 4);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"AB", 2);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"AB", 2);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"AB", 2);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"ABCDEF", 6);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"ABEF", 4);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"ABCD", 4);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"ABCD", 4);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"ABEF", 4);
  nn_assert(rc == 1);
  nn_trie_term(&trie);

  /*  Check whether there's no problem with removing all subscriptions. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 1);
  rc = nn_trie_match(&trie, (const uint8_t *)"", 0);
  nn_assert(rc == 0);
  rc = nn_trie_match(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 0);
  nn_trie_term(&trie);

  /*  Check converting from sparse node to dense node and vice versa. */
  nn_trie_init(&trie);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"B", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"C", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"0", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"E", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"F", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"1", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"@", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"b", 1);
  nn_assert(rc == 1);
  rc = nn_trie_subscribe(&trie, (const uint8_t *)"f", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"0", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"f", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"E", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"B", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"A", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"1", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"@", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"F", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"C", 1);
  nn_assert(rc == 1);
  rc = nn_trie_unsubscribe(&trie, (const uint8_t *)"b", 1);
  nn_assert(rc == 1);
  nn_trie_term(&trie);
}

int main() {
	Tire *node = new Tire();

  const uint8_t *data = (uint8_t *)"ABCDEFGHIJK";
  node->Subscribe(data, 8);
  node->Subscribe(data, 4);
  node->Subscribe(data, 3);
  node->Subscribe(data, 2);
  node->Subscribe(data, 1);

  node->UnSubscribe(data, 4);
  node->UnSubscribe(data, 3);
  node->UnSubscribe(data, 2);
  node->UnSubscribe(data, 1);

  delete node;

  test();
}