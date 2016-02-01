#pragma once

#include <genecis/base/genecis_defines.h>
#include <genecis/base/genecis_string.h>
#include <vector>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(base)

class genecis_stringlist ;

std::ostream& operator<<(std::ostream &os, const genecis_stringlist &output) ;

class genecis_stringlist {
public:

    typedef genecis_stringlist         self_type ;
    typedef genecis_string             string_type ;
    typedef string_type::size_type     size_type ;
    typedef std::vector<string_type>   container_type ;

    /**
     * Empty Constructor
     */
    genecis_stringlist() ;

    /**
     * Copy Constructor
     */
    genecis_stringlist(const self_type& rhs) ;

    /**
     * Assignment operator
     */
    self_type& operator=(const self_type& rhs) ;

    /**
     * Safe accessor, gaurds against out of bounds errors
     */
    string_type operator[](size_type index) ;

    /**
     * Fast, unsafe accessor
     */
    string_type operator()(size_type index) ;

    /**
     * Number of GStrings in the list
     */
    size_type size() ;

    /**
     * Alias for adding an element to the list
     */
    void push_back(string_type& s) ;

    /**
     * Alias for adding a std::string to the list
     */
    void push_back(std::string& s) ;

    /**
     * Joins elements i to n separated by separator
     */
    string_type join(string_type separator, size_type i, size_type n) ;

    /**
     * Output overload of opertor<<
     */
    friend std::ostream& operator<<(std::ostream &os, const genecis_stringlist &output) ;

private:

    container_type _data ;
};

inline std::ostream& operator<<(std::ostream &os, const genecis_stringlist &output)
{
    int size( output._data.size() ) ;
    os << "[" << size << "]: {" ;
    for(int i=0; i<size; ++i) {
        os << output._data[i] ;
        if( i < size-1 ) {
            os << ", " ;
        }
    }
    os << "}" ;
    return os ;
}

END_NAMESPACE
END_NAMESPACE
