
-- 
-- Nicolas Seriot's JSONTestSuite
-- https://github.com/nst/JSONTestSuite
-- commit d64aefb55228d9584d3e5b2433f720ea8fd00c82
-- 
-- MIT License
-- 
-- Copyright (c) 2016 Nicolas Seriot
-- 
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
-- 
-- The above copyright notice and this permission notice shall be included in all
-- copies or substantial portions of the Software.
-- 
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
-- SOFTWARE.
-- 

-- these test cases are prefixed with n_
-- ljson should reject all of them as invalid

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_with_trailing_garbage.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x22\x22\x78 ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_unicode_CapitalU.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x22\x5c\x55\x41\x36\x36\x44\x22 ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_unescaped_tab.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x9\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_unescaped_newline.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x6e\x65\x77\xa\x6c\x69\x6e\x65\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_unescaped_ctrl_char.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x61\x0\x61\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_start_escape_unclosed.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_single_string_no_double_quotes.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x61\x62\x63 ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_single_quote.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x27\x73\x69\x6e\x67\x6c\x65\x20\x71\x75\x6f\x74\x65\x27\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_single_doublequote.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x22 ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_no_quotes_with_bad_escape.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x5c\x6e\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_leading_uescaped_thinspace.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x5c\x75\x30\x30\x32\x30\x22\x61\x73\x64\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_invalid_utf8_after_escape.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\xe5\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_invalid_unicode_escape.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x71\x71\x71\x71\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_invalid_backslash_esc.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x61\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_invalid-utf-8-in-escape.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\xe5\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_incomplete_surrogate_escape_invalid.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x44\x38\x30\x30\x5c\x75\x44\x38\x30\x30\x5c\x78\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_incomplete_surrogate.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x44\x38\x33\x34\x5c\x75\x44\x64\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_incomplete_escaped_character.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x30\x30\x41\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_incomplete_escape.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_escaped_emoji.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\xf0\x9f\x8c\x80\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_escaped_ctrl_char_tab.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x9\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_escaped_backslash_bad.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x5c\x5c\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_escape_x.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x78\x30\x30\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_backslash_00.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x0\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_accentuated_char_no_quotes.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\xc3\xa9\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_1_surrogate_then_escape_u1x.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x44\x38\x30\x30\x5c\x75\x31\x78\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_1_surrogate_then_escape_u1.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x44\x38\x30\x30\x5c\x75\x31\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_1_surrogate_then_escape_u.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x44\x38\x30\x30\x5c\x75\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_string_1_surrogate_then_escape.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x5b\x22\x5c\x75\x44\x38\x30\x30\x5c\x22\x5d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_object_with_single_string.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x7b\x20\x22\x66\x6f\x6f\x22\x20\x3a\x20\x22\x62\x61\x72\x22\x2c\x20\x22\x61\x22\x20\x7d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_object_unterminated-value.json
assert(false == pcall(DecodeJson, [[ {"a":"a ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_object_unquoted_key.json
assert(false == pcall(DecodeJson, [[ {a: "b"} ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_object_single_quote.json
assert(false == pcall(DecodeJson, [[ {'a':0} ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_object_repeated_null_null.json
assert(false == pcall(DecodeJson, [[ {null:null,null:null} ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_object_non_string_key_but_huge_number_instead.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x7b\x39\x39\x39\x39\x45\x39\x39\x39\x39\x3a\x31\x7d ]]))

-- https://github.com/nst/JSONTestSuite/tree/d64aefb55228d9584d3e5b2433f720ea8fd00c82/test_parsing/n_object_non_string_key.json
 -- (converted to binary for safety)
assert(false == pcall(DecodeJson, [[ \x7b\x31\x3a\x31\x7d ]]))

