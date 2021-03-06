#include "imp_double.h"

namespace math
{
    
imp_double::imp_double()
    : val_(0)
    , delta_(EPS)
{
}
    
imp_double::imp_double(double val)
    : val_(val)
    , delta_(abs(val) * EPS)
{
}

imp_double::imp_double(double val, double delta)
{
    val_   = val;
    delta_ = std::max(delta, EPS * abs(val));
}
    
imp_double& imp_double::operator += (const imp_double& rhs)
{
    val_   += rhs.get_value();
    delta_ += rhs.get_delta();
    
    return *this;
}

imp_double& imp_double::operator -= (const imp_double& rhs)
{
    val_   -= rhs.get_value();
    delta_ += rhs.get_delta();
    
    return *this;
}

imp_double& imp_double::operator *= (const imp_double& rhs)
{
    val_  *= rhs.get_value();
    delta_ = delta_* abs(rhs.get_value()) + rhs.get_delta() * abs(val_);
    
    return *this;
}

imp_double& imp_double::operator /= (const imp_double& rhs)
{
    val_  /= rhs.get_value();
    delta_ = delta_ / abs(rhs.get_value()) + (abs(val_) * rhs.get_delta() / (rhs.get_value() * rhs.get_value()));
    
    return *this;
}
  
bool operator < (const imp_double& lhs, const imp_double& rhs)
{
    if (lhs.get_value() + lhs.get_delta() < rhs.get_value() - rhs.get_delta())
        return true;
    else 
        return false;
}

std::ostream& operator <<(std::ostream& out, const imp_double& d)
{
    out << d.get_value() << '#' << d.get_delta();
    
    return out;
}

/*
    assume that input is always valid
*/
std::istream& operator >>(std::istream& in, imp_double& d)
{
    double val, delta;
    char c; // '#'
    in >> val >> c >> delta;
    d.val_   = val;
    d.delta_ = delta;
    
    return in;
}
  
} // math