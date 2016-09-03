#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <sstream>

typedef unsigned int uint;

class String : public std::string
{
public:
    String() : std::string(){}
    String( const std::string &val ) : std::string(val){}
    String( const char *val ) : std::string(val){}
    String( const char &val ) {
        std::stringstream ss;
        ss << val;
        *this = ss.str();
    }
    
    String( const int &val ){
        std::stringstream ss;
        ss << val;
        *this = ss.str();
    }
    
    String( const wchar_t *_str )
    {
        std::wstring str = _str;
        std::ostringstream stm;
        const std::ctype<char>& ctfacet =
        std::use_facet< std::ctype<char> >( stm.getloc() ) ;
        for( size_t i=0 ; i<str.size() ; ++i )
            stm << ctfacet.narrow( str[i], 0 ) ;
        *this = stm.str() ;
    }
    
    bool operator ==(const String &other) const
    {
        return compare(other)==0;
    }
    
    bool operator !=(const String &other) const
    {
        return compare(other)!=0;
    }
    
    String operator +(const String &other)
    {
        String nova = *this;
        nova+=other;
        return nova;
    }
};

template <class T>
class List : public std::vector<T>
{
public:
    
    List<T>() : std::vector<T>(){}
    List<T>( const std::vector<T> &vec ) : std::vector<T>(vec){}
    //List<T>( const std::initializer_list<T> &l ) : std::vector<T>(l){}//C++11
    
    template<typename U>
    List<T> &operator <<(const U &val)
    {
        this->push_back(val);
        return *this;
    }
    
    template<typename U>
    List<T> &operator <<(const List<U> &other)
    {
        for(uint i=0;i<other.size();i++)
            this->push_back(other[i]);
        return *this;
    }
    
    template<typename U>
    List<T> operator +(const List<U> &other)
    {
        List<T> nova = *this;
        for(uint i=0;i<other.size();i++)
            nova.push_back(other[i]);
        return nova;
    }
    
    template<typename U>
    List<T> operator +(const U &val)
    {
        List<T> nova = *this;
        nova.push_back(val);
        return nova;
    }
    
    typedef std::ostream& (*stream_manip)(std::ostream&);
    
    List<T> &operator <<(stream_manip)
    {
        *this << '\n';
        return *this;
    }
};

template <typename T>
std::ostream &operator <<(std::ostream &os, const std::vector<T> &v)
{
    for(uint i=0;i<v.size();i++)
        os << v[i] << (i+1<v.size() && v[i]!='\n' && v[i+1]!='\n'?",":"");
    return os;
}

#endif // UTIL_H
