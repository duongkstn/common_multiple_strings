![GitHub](https://img.shields.io/badge/Python-3.x-blue.svg)

# A fast Python Common substrings of multiple strings library with C++ implementation

Having a bunch of strings, can I print some substrings which appear K times ? Can I know which is longest substrings ?


## Installing
Make sure `Cython` is installed properly !

Building from source:
```
cd python
python setup.py install
```

## Usuage and examples
### Step 1. Import the library

```
from common_multiple_strings import PyCommon_multiple_strings
tree = PyCommon_multiple_strings()  # init
```

### Step 2. Build the data structure
Build from list of str:
```python
tree.from_strings(list_str)
```

or build from file:
```python
tree.from_path(<path_to_file>)
```
It is noted that sentences in file are presentened line-by-line. Each line is a sentence.

Sample code:
```python
>>> from common_multiple_strings import PyCommon_multiple_strings
>>> tree = PyCommon_multiple_strings()  # init
>>> list_str = [
       'abc',
       'abcxa',
       'xamnb',
       'yamnc',
       'abcd'
    ]
>>> tree.from_strings(list_str)
```

### Step 3. Query

This library introduces 4 types of query:

#### a) List some substrings appear TIMES times:
```python
tree.query(times=TIMES)
```
Ouput is a dictionary with key is an integer K, value is a list of some substrings which appear exactly K times.

Sample code:
```python
>>> print(tree.query(times=(2, None)))
{2: ['amn', 'xa', 'n', 'mn'], 3: ['bc', 'abc'], 4: ['c', 'b'], 5: ['a']}
>>> print(tree.query(times=(3, 3)))
{3: ['bc', 'abc']}
```


#### b) Length of the longest substring appears TIMES times:
```python
tree.length_longest_substring(times=TIMES)
```
Ouput is an integer.

Sample code:
```python
>>> print(tree.length_longest_substring(times=(2, None)))
3
```

#### c) Lengths of the longest substrings appear TIMES times:
```python
tree.lengths_longest_substrings(times=TIMES)
```
Ouput is a dictionary with key is an integer K, value is the length of the longest substring which appear exactly K times.

Sample code:
```python
>>> print(tree.lengths_longest_substrings(times=(2, None)))
{2: 3, 3: 3, 4: 1, 5: 1}
```

#### d) List some substrings which have length of L and appear TIMES times:
```python
tree.filter_substrings_by_length(length_input=L, times=TIMES)
```
Ouput is a dictionary with key is an integer K, value is a list of some substrings which appear exactly K times and have length of L.

Sample code:
```python
>>> print(tree.filter_substrings_by_length(length_input=2, times=(2, None)))
{2: ['xa', 'mn'], 3: ['bc']}
>>> print(tree.filter_substrings_by_length(length_input=10, times=(2, None)))
{}
```

#### Some Notes: 
##### - Params:
`times`, default `(None, None)` is a tuple represents the minimum and maximum appearances of the desired output.
Query substrings appear exactly N times, then `times=(N, N)`
Query substrings appear more than N times, then `times=(N, None)`
Query substrings appear less than N times, then `times=(None, N)`
Query substrings appear less than N times and more than M times, then `times=(M, N)`

`length_input` is an integer, represents the length of substrings

##### - This library accepts various utf8 characters including punctuations, numbers, upper-case characters, ... For more details, checkout `alphabet.cpp` file. Thanks [coccoc-tokenizer](https://github.com/coccoc/coccoc-tokenizer/tree/master/dicts/vn_lang_tool) for providing these available lists 
##### - Query a) and d) does not output all possible results, but you can use it for analytic purposes.

## Algorithm and Complexity
Data structure suffix tree is the core of this library. It encourages fast query and efficient storing. 

If the total length of all input strings are `L`, then the average complexity should be `L * log(L)`.

## References

Algorithm from the lecture of [String Algorithms and Algrorithms in Computational Biology - Gusfield](https://web.cs.ucdavis.edu/~gusfield/cs224f09/commonsubstrings.pdf)

