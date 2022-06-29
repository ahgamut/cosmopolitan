#include "libc/assert.h"
#include "libc/calls/calls.h"
#include "libc/fmt/conv.h"
#include "libc/fmt/fmt.h"
#include "libc/log/log.h"
#include "libc/stdio/stdio.h"
#include "third_party/dabbajson/dabbajson.h"
#include "third_party/dabbajson/dabbajson.internal.h"
#include "third_party/gdtoa/gdtoa.h"

DJArrayElement *DJA_New() {
  DJArrayElement *x = malloc(sizeof(DJArrayElement));
  x->value = NULL;
  x->next = NULL;
  return x;
}

void DJA_FreeLinked(DJArrayElement *elem) {
  if (!elem) return;
  if (elem->next) DJA_FreeLinked(elem->next);
  if (elem->value) FreeDJValue(elem->value);
  free(elem);
}

size_t DJA_CountLinked(DJArrayElement *elem) {
  if (!elem || !elem->value) return 0;
  return 1 + DJA_CountLinked(elem->next);
}

DJObjectElement *DJO_New() {
  DJObjectElement *x = malloc(sizeof(DJObjectElement));
  x->key = NULL;
  x->keylen = 0;
  x->value = NULL;
  x->next = NULL;
  return x;
}

void DJO_FreeLinked(DJObjectElement *elem) {
  if (!elem) return;
  if (elem->next) DJO_FreeLinked(elem->next);
  if (elem->value) FreeDJValue(elem->value);
  if (elem->key) free(elem->key);
  free(elem);
}

size_t DJO_CountLinked(DJObjectElement *elem) {
  if (!elem || !elem->value || !elem->key || !elem->keylen) return 0;
  return 1 + DJO_CountLinked(elem->next);
}
