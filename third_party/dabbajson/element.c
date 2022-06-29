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

size_t DJA_CountLinked(const DJArrayElement *elem) {
  if (!elem || !elem->value) return 0;
  return 1 + DJA_CountLinked(elem->next);
}

DJValue *ArrayElementsToDJValue(DJArrayElement *head, size_t num_elements) {
  /* create the DJValue from the DJArrayElement linked list */
  DJValue *answer = malloc(sizeof(DJValue));
  DJArray *arr = malloc(sizeof(DJArray));
  DJArrayElement *tmp;
  arr->len = num_elements;
  arr->values = malloc(sizeof(DJValue *) * arr->len);
  for (size_t i = 0; i < num_elements; i++) {
    arr->values[i] = head->value;
    tmp = head;
    head = head->next;
    /* we are not freeing the attributes of tmp because
     * they are being std::move'd into the DJArray */
    free(tmp);
  }
  BOX_ArrayIntoDJValue(arr, *answer);
  return answer;
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

size_t DJO_CountLinked(const DJObjectElement *elem) {
  if (!elem || !elem->value || !elem->key || !elem->keylen) return 0;
  return 1 + DJO_CountLinked(elem->next);
}

DJValue *ObjectElementsToDJValue(DJObjectElement *head, size_t num_elements) {
  /* create the DJValue from the DJObjectElement linked list */
  DJValue *answer = malloc(sizeof(DJValue));
  DJObject *obj = malloc(sizeof(DJObject));
  DJObjectElement *tmp;

  obj->len = num_elements;
  obj->keylens = malloc(sizeof(size_t) * obj->len);
  obj->keys = malloc(sizeof(char *) * obj->len);
  obj->values = malloc(sizeof(DJValue *) * obj->len);
  for (size_t i = 0; i < num_elements; i++) {
    obj->values[i] = head->value;
    obj->keys[i] = head->key;
    obj->keylens[i] = head->keylen;
    tmp = head;
    head = head->next;
    /* we are not freeing the attributes of tmp because
     * they are being std::move'd into the DJObject */
    free(tmp);
  }
  BOX_ObjectIntoDJValue(obj, *answer);
  return answer;
}
