from Cython.Distutils import build_ext
from Cython.Build import cythonize
from distutils.core import setup
from distutils.extension import Extension

ext_modules = [
    Extension(
        name="common_multiple_strings",
        sources=["common_multiple_strings.pyx", 
        "../common_multiple_strings/common_multiple_strings.cpp",
        "../common_multiple_strings/auxiliary/suffix_tree_simple.cpp",
        "../common_multiple_strings/auxiliary/alphabet.cpp",
        "../common_multiple_strings/auxiliary/utf8.cpp",
        # "../common_multiple_strings/auxiliary/other_characters.txt",
        # "../common_multiple_strings/auxiliary/punctuations.txt",
        ],
        include_dirs=["../common_multiple_strings"],
        language="c++",
    )
]
setup(
    name = "common_multiple_strings",
    version = "1.0",
    description = "common_multiple_strings",
    long_description = "Common Substrings of Multiple Strings written in C++ with python binding",
    author = "Dao Nguyen Duong",
    author_email = "nguyenduongyht@gmail.com",
    url = "",
    license = "",
    ext_modules = ext_modules,
    cmdclass = { "build_ext": build_ext }
)
