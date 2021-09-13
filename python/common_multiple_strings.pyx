
cimport cython
from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "<Python.h>":
    cdef char* PyUnicode_AsUTF8(object)
    cdef object PyUnicode_DecodeUTF8(char*, Py_ssize_t, char*)

cdef extern from "../common_multiple_strings/common_multiple_strings.h":
    cdef cppclass Common_multiple_strings:
        int number_strings
        void from_path(string) except +
        void from_strings(vector[string]) except +
        vector[string] query(int) except +
        int length_longest_substring(int) except +
        vector[string] filter_substrings_by_length(int, int) except +

cdef class PyCommon_multiple_strings:
    cdef Common_multiple_strings __CXX_object

    def __cinit__(self):
        pass
    
    cdef void _from_path(self, str path):
        cdef string text = <string> PyUnicode_AsUTF8(path)
        self.__CXX_object.from_path(text)
        
    def from_path(self, path):
        self._from_path(path)

    cdef void _from_strings(self, list list_text):
        cdef vector[string] new_list_text;
        for i in range(len(list_text)):  # type conversion
            new_list_text.push_back(<string> PyUnicode_AsUTF8(list_text[i]))
        self.__CXX_object.from_strings(new_list_text)
        
    def from_strings(self, list list_text):
        self._from_strings(list_text)
    
    cdef list _query(self, int k):
        cdef vector[string] output = self.__CXX_object.query(k)
        cdef list result = []
        for i in range(len(output)):
            t = output[i]
            result.append(PyUnicode_DecodeUTF8(t.c_str(), t.length(), NULL))
        return result
    def query(self, times=(None, None)):
        from_num, to_num = times
        if from_num is None:
            from_num = 1
        if to_num is None:
            to_num = self.__CXX_object.number_strings
        assert from_num <= to_num, "times[0] has to smaller than times[1]"
        result = {}
        for k in range(from_num, to_num + 1):
            output = self._query(k)
            if len(output) != 0:
                result[k] = output

        return result

    cdef int _length_longest_substring(self, int k):
        cdef int output = self.__CXX_object.length_longest_substring(k)
        return output

    cdef list _filter_substrings_by_length(self, int k, int length_input):
        cdef vector[string] output = self.__CXX_object.filter_substrings_by_length(k, length_input)
        cdef list result = []
        for i in range(len(output)):
            t = output[i]
            result.append(PyUnicode_DecodeUTF8(t.c_str(), t.length(), NULL))
        return result
    
    def length_longest_substring(self, times=(None, None)):
        from_num, to_num = times
        if from_num is None:
            from_num = 1
        if to_num is None:
            to_num = self.__CXX_object.number_strings
        assert from_num <= to_num, "times[0] has to smaller than times[1]"
        result = 0
        for k in range(from_num, to_num + 1):
            output = self._length_longest_substring(k)
            if output > result:
                result = output
        return result

    def lengths_longest_substrings(self, times=(None, None)):
        from_num, to_num = times
        if from_num is None:
            from_num = 1
        if to_num is None:
            to_num = self.__CXX_object.number_strings
        assert from_num <= to_num, "times[0] has to smaller than times[1]"
        result = {}
        for k in range(from_num, to_num + 1):
            output = self._length_longest_substring(k)
            result[k] = output
        return result

    def filter_substrings_by_length(self, length_input, times=(None, None)):
        from_num, to_num = times
        if from_num is None:
            from_num = 1
        if to_num is None:
            to_num = self.__CXX_object.number_strings
        assert from_num <= to_num, "times[0] has to smaller than times[1]"
        assert length_input > 0, "length_input has to be an positive integer"
        result = {}
        for k in range(from_num, to_num + 1):
            output = self._filter_substrings_by_length(k, length_input)
            if len(output) > 0:
                result[k] = output
        return result
    


