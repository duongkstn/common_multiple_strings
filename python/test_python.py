from common_multiple_strings import PyCommon_multiple_strings
tree = PyCommon_multiple_strings()
list_str = [
    'abc',
    'abcxa',
    'xamnb',
    'yamnc',
    'abcd'
]
tree.from_strings(list_str)
print(tree.query(times=(3, 3)))
print(tree.length_longest_substring(times=(2, None)))
print(tree.lengths_longest_substrings(times=(2, None)))
print(tree.filter_substrings_by_length(length_input=2, times=(2, None)))
print(tree.filter_substrings_by_length(length_input=3, times=(2, None)))
print(tree.filter_substrings_by_length(length_input=10, times=(2, None)))