#include "genecis_stringlist.h"

USING_NAMESPACE(genecis::base)

/**
 * Empty Constructor
 */
genecis_stringlist::genecis_stringlist()
    : _data(0)
{

}

/**
 * Copy Constructor
 */
genecis_stringlist::genecis_stringlist(const self_type& rhs)
    : _data(rhs._data)
{

}

/**
 * Assign operator from another GStringList
 */
genecis_stringlist::self_type& genecis_stringlist::operator=(const self_type& rhs)
{
    _data = rhs._data ;
    return *this ;
}

/**
 * Safe access of container
 */
genecis_stringlist::string_type genecis_stringlist::operator()(size_type index)
{
    if( _data.size() < std::size_t(index) ) {
        return string_type() ;
    } else {
        return _data[index] ;
    }
}

/**
 * Fast access of container
 */
genecis_stringlist::string_type genecis_stringlist::operator[](size_type index)
{
    return _data[index] ;
}

/**
 * Number of data_types stored in container
 */
genecis_stringlist::size_type genecis_stringlist::size()
{
    return _data.size() ;
}

/**
 * Alias for std::vector.push_back()
 */
void genecis_stringlist::push_back(string_type& s)
{
    _data.push_back( s ) ;
}

/**
 * Alias for std::vector.push_back()
 */
void genecis_stringlist::push_back(std::string& s)
{
    _data.push_back( genecis_string(s) ) ;
}

/**
 * Joins elements i to n separated by separator
 */
genecis_stringlist::string_type genecis_stringlist::join(string_type separator, size_type i, size_type n)
{
    string_type tmp ;
    for(; i<n; ++i) {
        tmp += _data[i] ;
        tmp += separator ;
    }
    return tmp ;
}
