reference: https://www.json.org/json-en.html

* developed entirely within Cosmopolitan Libc development environment
* simple `runner.com` for testing (uses zipos for testing sample JSON)
* all interactions happen by opaque pointer `DJValue *` in `dabbajson.h`
* NaN boxing is done on the `DJValue *` type which takes only 64 bits
* internal` DJValue` type used for conversions only
* internal macros to unbox the `DJValue *` into respective JSON types
* writing JSON to file/buffer is mostly complete
* reading JSON from file/buffer is mostly complete

TODOs:

- [x] implement reading/writing utf-8 characters
- [ ] add tests
- [ ] a better lexer/parser logic for reading JSON?
- [ ] separate integer type necessary or just cast from `double`?
- [ ] recursive access via varargs? (`a[1]["b"][2] --> GetDJValueRecursive(obj, "dsd", 1, "b", 2)`)
- [ ] implement equality operator?
- [ ] use linked list for array instead of ptr+length?
- [ ] use hash table for records instead of ptr,ptr,length?
- [ ] allow insertion/deletion into array/records?
- [ ] NaN boxing side-effects?
- [x] reduce memory allocations by boxing on `DJValue*`
- [ ] avoid opaque pointer to reduce memory allocations? (ie box on `DJValue` and use it everywhere)
