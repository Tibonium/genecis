#pragma once

#include <genecis/base/genecis_defines.h>
#include <genecis/container/array.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdio>

BEGIN_NAMESPACE(genecis)
BEGIN_NAMESPACE(base)

USING_NAMESPACE(container)

class genecis_string ;
class genecis_stringlist ;

std::ostream& operator<<(std::ostream& os, const genecis_string& output) ;
std::istream& operator>>(std::istream& is, genecis_string& input) ;

std::ofstream& operator<<(std::ofstream& of, const genecis_string& output) ;
std::ifstream& operator>>(std::ifstream& fi, genecis_string& input) ;

class genecis_string {
public:

    typedef genecis_string              self_type ;
    typedef short                       size_type ;
    typedef std::string                 data_type ;
    typedef data_type::iterator         iterator ;
    typedef data_type::const_iterator   const_iterator ;
    typedef std::stringstream           stream_type ;
    typedef enum { CaseSensitive = 0, CaseInsensitive = 1 } CaseCheck ;
    typedef enum { KeepEmpty = 0x0, SkipEmpty = 0x1 }   EmptyParts ;

    /**
     * Empty Constructor
     */
    genecis_string() ;

    /**
     * Default Constructor
     */
    genecis_string(data_type &s) ;

    /**
     * Constructor from char*
     */
    genecis_string(const char *str) ;

    /**
     * Constructs a new genecis_string with size n
     * and filled with character ch.
     */
    genecis_string(size_type n, char ch) ;

    /**
     * Empty Destructor
     */
    virtual ~genecis_string() ;

    /**
     * Copy Constructor
     */
    genecis_string(const self_type &rhs) ;

    /**
     * Assignment operator for genecis_string
     */
    self_type& operator=(const self_type &rhs) ;

    /**
     * Assignment operator for char*
     */
    self_type& operator=(const char *str);

    /**
     * Assign operator for std::string
     */
    self_type& operator=(const data_type &s) ;

    /**
     * Iterator Aliases
     */
    iterator begin() {
        return _data.begin() ;
    }

    iterator end() {
        return _data.end() ;
    }

    const_iterator begin() const {
        return _data.begin() ;
    }

    const_iterator end() const {
        return _data.end() ;
    }

    /**
     * Comparison operator<
     */
    bool operator<(const self_type &rhs) const ;

    /**
     * Comparison operator>
     */
    bool operator>(const self_type &rhs) const ;

    /**
     * Comparison operator>=
     */
    bool operator>=(const self_type &rhs) const ;

    /**
     * Comparison operator==
     */
    bool operator==(const self_type &rhs) const ;

    /**
     * Comparison operator!=
     */
    bool operator!=(const self_type &rhs) const ;

    /**
     * Concatenates rhs to this
     */
    self_type& operator+=(const self_type &rhs) ;

    /**
     * Overload operator+= for char*
     */
    self_type& operator+=(const char *str) ;

    /**
     * Overload operator+= for char*
     */
    self_type& operator+=(char c) ;

    /**
     * Overload operator+= for std::string
     */
    self_type& operator+=(const data_type &str) ;

    /**
     * Index accessor
     */
    char operator[](size_type i) ;

    /**
     * Splits the string utilizing the delimiter provided.
     * If size of the internal data is less than one, an empty
     * StringList is returned, otherwise a StringList is
     * returned with the elements of __s split by the delimiter.
     */
    genecis_stringlist split(char delim, EmptyParts em = SkipEmpty) ;

    /**
     * Splits the string utilizing the delimiter provided.
     * If size of the internal data is less than one, an empty
     * StringList is returned, otherwise a StringList is
     * returned with the elements of __s split by the delimiter.
     */
    genecis_stringlist split(char delim, EmptyParts em = SkipEmpty) const ;

    /**
     * Size of the internal string
     */
    size_type size() ;

    /**
     * Size of the internal string
     */
    size_type size() const ;

    /**
     * Converts string to Integer
     */
    int toInt() ;

    /**
     * Converts string to char*
     * Alias to std::string::c_str()
     */
    const char* toChar() ;

    /**
     * Converts string to char*
     * Alias to std::string::c_str()
     */
    const char* toChar() const ;

    /**
     * Accessor to the raw structure
     */
    data_type& data() ;

    /**
     * If size is zero, genecis_string is empty
     */
    bool isEmpty() ;

    /**
     * If size is zero, genecis_string is empty
     */
    bool isEmpty() const ;

    /**
     * Returns a substring starting at position i
     * and size n.
     */
    self_type substr(size_type i, size_type n=data_type::npos) ;

    /**
     * Compares two strings together and returns
     * <, =, or > zero.
     */
    int compare(const self_type &other, self_type::CaseCheck cs = self_type::CaseInsensitive) const ;

    /**
     * Determines if the string other is contained within this genecis_string
     */
    bool contains(const self_type &other, self_type::CaseCheck cs = self_type::CaseInsensitive) const ;

    /**
     * Empties the container
     */
    void clear() ;

    /**
     * Removes the last character from the genecis_string
     * Protected against strings of size zero.
     */
    void chop_end() ;

    /**
     * Output stream operator<<
     */
    friend std::ostream& operator<<(std::ostream& os, const genecis_string& output) ;

    /**
     * Input stream operator>>
     */
    friend std::istream& operator>>(std::istream& is, genecis_string& input) ;

    /**
     * Output stream operator<<
     */
    friend std::ofstream& operator<<(std::ofstream& of, const genecis_string& output) ;

    /**
     * Input stream operator>>
     */
    friend std::ifstream& operator>>(std::ifstream& fi, genecis_string& input) ;

    /**
     * getline overload for genecis_string
     */
    static void getline(std::fstream& fi, self_type& line) {
        std::getline(fi, line.data()) ;
        line.convert_to_lower() ;
    }

    /**
     * Helper function to convert a numerical value into an genecis_string
     */
    static self_type number(int value) {
        std::stringstream iss ;
        iss << value ;
        return self_type(iss.str().c_str()) ;
    }

private:

    data_type _data ;

    data_type _data_lower ;

    /**
     * Converts underlying string to lower case version
     */
    void convert_to_lower() ;
};

/**
 * Prints the underlying stored string to the output stream
 */
inline std::ostream& operator<<(std::ostream& os, const genecis_string& output)
{
    os << output._data ;
    return os ;
}

/**
 * Prints the underlying stored string to the output stream
 */
inline std::istream& operator>>(std::istream& is, genecis_string& input)
{
    is >> input._data ;
    return is ;
}

/**
 * Prints the underlying stored string to the output stream
 */
inline std::ofstream& operator<<(std::ofstream& of, const genecis_string& output)
{
    of << output._data ;
    return of ;
}

/**
 * Prints the underlying stored string to the output stream
 */
inline std::ifstream& operator>>(std::ifstream& fi, genecis_string& input)
{
    std::string line ;
    fi >> line ;
    input._data = line ;
    return fi ;
}

END_NAMESPACE
END_NAMESPACE
