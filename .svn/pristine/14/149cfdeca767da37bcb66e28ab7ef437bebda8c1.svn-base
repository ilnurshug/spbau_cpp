#pragma once
#include <cmath>
#include <iostream>
#include <sstream>

namespace math
{

#define EPS (double)1e-15
    
#define BINARY_OPERATOR( T, OP )                        \
friend T operator OP( const T& lhs, const T& rhs )      \
	{ T tmp( lhs ); tmp OP##= rhs; return tmp; }    \
	
#define INC_DEC_OPERATOR( T, OP )                    	\
friend T operator OP(T& lhs, int)      			\
	{ T tmp( lhs ); OP lhs; return tmp; }        	\

template <class T>
class operators 
{
public:
    
    BINARY_OPERATOR( T, + )
    
    BINARY_OPERATOR( T, - )
    
    BINARY_OPERATOR( T, * )
    
    BINARY_OPERATOR( T, / )
    
    INC_DEC_OPERATOR( T, ++ )
    
    INC_DEC_OPERATOR( T, -- )
    
    friend bool operator  >(const T& lhs, const T& rhs) { return rhs < lhs; }
    
    friend bool operator <=(const T& lhs, const T& rhs) { return !(rhs < lhs); }
    
    friend bool operator >=(const T& lhs, const T& rhs) { return !(lhs < rhs); }
    
    friend bool operator ==(const T& lhs, const T& rhs) { return !(rhs < lhs) && !(lhs < rhs); }
    
    friend bool operator !=(const T& lhs, const T& rhs) { return !(lhs == rhs); }
};
    
    
class imp_double  : public operators<imp_double>
{
public:
    imp_double();
    imp_double(double val);
    imp_double(double val, double delta);
    
    double get_delta() const { return delta_; }
    double get_value() const { return val_;   }
    
    imp_double& operator +=(const imp_double&);
    
    imp_double& operator -=(const imp_double&);
    
    imp_double& operator *=(const imp_double&);
    
    imp_double& operator /=(const imp_double&);
    
    imp_double operator -() const { return imp_double(-val_, delta_); }
    
    friend bool operator <(const imp_double&, const imp_double&);
    
    friend std::ostream& operator <<(std::ostream&, const imp_double&);
    friend std::istream& operator >>(std::istream&, imp_double&);
    
private:
    
    double val_;
    double delta_;
};
    
} // math