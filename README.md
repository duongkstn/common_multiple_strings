# A fast Python Common substrings of multiple strings library with C++ implementation

Having a bunch of strings, can I print some strings which appear K times ?


## Installing
Make sure `Cython` is installed properly !
Building from source:
```
cd python
python setup.py install
```

## Usuage
### Step 1. Import the library

```
from common_multiple_strings import PyCommon_multiple_strings
tree = PyCommon_multiple_strings()  # init
```

### Step 2. Build the data structure
Build from list of str:
```
tree.from_strings(list_str)
```

or build from file:
```
from_path(<path_to_file>)
```
It is noted that sentences in file are presentened line-by-line. Each line is a sencentence.

### Step 3. Query
List some substrings which appear exactly N times of all strings:
```
tree.query(from_num=N, to_num=N)
```

List some substrings which appear from N to M times of all strings:
```
tree.query(from_num=N, to_num=M)
```

List some substrings which appear more than N times of all strings:
```
tree.query(from_num=N, to_num=None)
```

List some substrings which appear less than N times of all strings:
```
tree.query(from_num=None, to_num=N)
```

### Important notes: This algorithm does not output all possible results, but you can use it for analytic purposes.
