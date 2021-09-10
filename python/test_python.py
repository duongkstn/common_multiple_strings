from common_multiple_strings import PyCommon_multiple_strings
tree = PyCommon_multiple_strings()
tree = PyCommon_multiple_strings()
list_str = [
    'abc',
    'abcxa',
]
tree.from_strings(list_str)
print(tree.query(from_num=None, to_num=None))