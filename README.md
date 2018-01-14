# Simple LibXML2 parser

Ref: http://xmlsoft.org/tutorial/index.html

Leak checking:

    mkdir build
    cd build
    cmake ..
    make
    valgrind --leak-check=full ./study_libxml ../sample_books.xml

