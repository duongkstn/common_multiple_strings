
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
    def query(self, from_num=None, to_num=None):
        result = {}
        if from_num is None:
            from_num = 1
        if to_num is None:
            to_num = self.__CXX_object.number_strings
        assert from_num <= to_num, "from_num has to smaller than to_num"
        for k in range(from_num, to_num + 1):
            output = self._query(k)
            if len(output) != 0:
                result[k] = output

        return result


