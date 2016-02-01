#include "genecis_stringlist.h"

USING_NAMESPACE(genecis::base)

/**
 * Empty Constructor
 */
genecis_string::genecis_string()
    : _data(), _data_lower()
{

}

/**
 * Default Constructor
 */
genecis_string::genecis_string(data_type &s)
    : _data(s)
{
    convert_to_lower() ;
}

/**
 * Constructor from char*
 */
genecis_string::genecis_string(const char *str)
    : _data(str)
{
    convert_to_lower() ;
}

/**
 * Constructor with size and fill
 */
genecis_string::genecis_string(size_type n, char ch)
    : _data(n,ch)
{
    convert_to_lower() ;
}

/**
 * Empty Destructor
 */
genecis_string::~genecis_string()
{

}

/**
 * Copy Constructor
 */
genecis_string::genecis_string(const self_type &rhs)
{
    _data = rhs._data ;
    convert_to_lower() ;
}

/**
 * Assignment operator for GStrings
 */
genecis_string::self_type& genecis_string::operator=(const self_type &rhs)
{
    _data = rhs._data ;
    convert_to_lower() ;
    return *this ;
}

/**
 * Assignment operator for char*
 */
genecis_string::self_type& genecis_string::operator=(const char *str)
{
    _data = str ;
    convert_to_lower() ;
    return *this ;
}

/**
 * Assign operator for std::string
 */
genecis_string::self_type& genecis_string::operator=(const data_type &s)
{
    _data = s ;
    convert_to_lower() ;
    return *this ;
}

/**
 * Comparison operator<
 */
bool genecis_string::operator<(const self_type &rhs) const
{
    return std::strcmp(_data.c_str(), rhs._data.c_str()) < 0 ;
}

/**
 * Comparison operator>
 */
bool genecis_string::operator>(const self_type &rhs) const
{
    return std::strcmp(_data.c_str(), rhs._data.c_str()) > 0 ;
}

/**
 * Comparison operator>=
 */
bool genecis_string::operator>=(const self_type &rhs) const
{
    return !operator<(rhs) ;
}

/**
 * Comparison operator==
 */
bool genecis_string::operator==(const self_type &rhs) const
{
    return (_data == rhs._data) ;
}

/**
 * Comparison operator!=
 */
bool genecis_string::operator!=(const self_type &rhs) const
{
    return !(_data == rhs._data) ;
}

/**
 * Concatenates rhs to this
 */
genecis_string::self_type& genecis_string::operator+=(const self_type &rhs)
{
    _data += rhs._data ;
    return *this ;
}

/**
 * Overload operator+= for char*
 */
genecis_string::self_type& genecis_string::operator+=(const char *str)
{
    _data += str ;
    return *this ;
}

/**
 * Overload operator+= for char*
 */
genecis_string::self_type& genecis_string::operator+=(char c)
{
    _data += c ;
    return *this ;
}

/**
 * Overload operator+= for std::string
 */
genecis_string::self_type& genecis_string::operator+=(const data_type &str)
{
    _data += str ;
    return *this ;
}

/**
 * Accessor operator[]
 */
char genecis_string::operator[](size_type i)
{
    return _data[i] ;
}

/**
 * Splits the string utilizing the delimiter provided.
 * If size of the internal data is less than one, an empty
 * StringList is returned, otherwise a StringList is
 * returned with the elements of __s split by the delimiter.
 */
genecis_stringlist genecis_string::split(char delim, EmptyParts em)
{
    genecis_stringlist tmp ;
    if( _data.size() > 0 ) {
        data_type curr ;
        stream_type iss ;
        iss << _data ;
        while( true ) {
            std::getline(iss, curr, delim) ;
            // Remove leading spaces
            while( true ) {
                char c = curr[0] ;
                if( isspace(c) ) {
                    curr.erase(0, 1) ;
                } else {
                    break ;
                }
            }
            data_type::size_type n = curr.find('\"') ;
            if( n != data_type::npos ) {
                curr.erase(n, 1) ;
                data_type tmp ;
                std::getline(iss, tmp, '\"') ;
                curr += tmp ;
                n = curr.find('\"') ;
                if( n != data_type::npos ) {
                    curr.erase(n, 1) ;
                }
                if( iss.peek() == ',') {
                    iss.get() ;
                }
            }
            if( ((em & SkipEmpty) && curr.empty()) || iss.eof() ) {
                if( iss.eof() ) {
                    tmp.push_back( curr ) ;
                    break ;
                }
                continue ;
            }
            tmp.push_back( curr ) ;
        }
    }
    return tmp ;
}

/**
 * Splits the string utilizing the delimiter provided.
 * If size of the internal data is less than one, an empty
 * StringList is returned, otherwise a StringList is
 * returned with the elements of __s split by the delimiter.
 */
genecis_stringlist genecis_string::split(char delim, EmptyParts em) const
{
    genecis_stringlist tmp ;
    if( _data.size() > 0 ) {
        data_type curr ;
        stream_type iss ;
        iss << _data ;
        while( true ) {
            std::getline(iss, curr, delim) ;
            data_type::size_type n = curr.find('\"') ;
            if( n != data_type::npos ) {
                curr.erase(n, 1) ;
                data_type tmp ;
                std::getline(iss, tmp, '\"') ;
                curr += tmp ;
                n = curr.find('\"') ;
                if( n != data_type::npos ) {
                    curr.erase(n, 1) ;
                }
                if( iss.peek() == ',') {
                    iss.get() ;
                }
            }
            if( ((em & SkipEmpty) && curr.empty()) || iss.eof() ) {
                if( iss.eof() ) {
                    tmp.push_back( curr ) ;
                    break ;
                }
                continue ;
            }
            tmp.push_back( curr ) ;
        }
    }
    return tmp ;
}

/**
 * Size of the internal string
 */
genecis_string::size_type genecis_string::size()
{
    return _data.size() ;
}

/**
 * Size of the internal string
 */
genecis_string::size_type genecis_string::size() const
{
    return _data.size() ;
}

/**
 * Converts string to Integer
 */
int genecis_string::toInt()
{
    return std::atoi(_data.c_str()) ;
}

/**
 * Converts string to char*
 */
const char* genecis_string::toChar()
{
    return _data.c_str() ;
}

/**
 * Converts string to char*
 */
const char* genecis_string::toChar() const
{
    return _data.c_str() ;
}

/**
 * Accessor to raw structure
 */
genecis_string::data_type& genecis_string::data() {
    return _data ;
}

/**
 * Alias for underlying std::string::empty()
 */
bool genecis_string::isEmpty()
{
    return _data.empty() ;
}

/**
 * Alias for underlying std::string::empty()
 */
bool genecis_string::isEmpty() const
{
    return _data.empty() ;
}

/**
 * Alias for substring call
 */
genecis_string genecis_string::substr(size_type i, size_type n)
{
    return _data.substr(i,n).c_str() ;
}

/**
 * Empties the container
 */
void genecis_string::clear()
{
    _data.clear() ;
}

/**
 * Removes last character in the string
 */
void genecis_string::chop_end()
{
    if( _data.size() > 0 ) {
        _data = _data.substr(0, _data.size()-1) ;
    }
}

/**
 * Compares two GStrings based on CaseCheck
 */
int genecis_string::compare(const self_type &other, self_type::CaseCheck cs) const
{
    if( cs == genecis_string::CaseSensitive ) {
        return std::strcmp(toChar(), other.toChar()) ;
    } else {
        return std::strcmp(_data_lower.c_str(), other._data_lower.c_str()) ;
    }
}

/**
 * Determines if other is contained within the GString
 */
bool genecis_string::contains(const self_type &other, self_type::CaseCheck cs) const
{
    if( cs == genecis_string::CaseSensitive ) {
        return (_data.find(other._data) != std::string::npos) ;
    } else {
        return (_data_lower.find(other._data_lower) != std::string::npos) ;
    }
}

/**
 * Converts the data string to lower case for quick access
 * later during comparison calls
 */
void genecis_string::convert_to_lower()
{
    _data_lower = _data ;
    std::transform(_data.begin(), _data.end(), _data_lower.begin(), ::tolower) ;
}
