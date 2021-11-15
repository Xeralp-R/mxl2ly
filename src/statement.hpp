//
//  statement.hpp
//  mxl2ly
//
//  Created by Reventar on 11/11/2021.
//

#ifndef statement_hpp
#define statement_hpp

#include <string>

namespace lmt {

class AbstractStatement {
public:
    virtual std::string get_type() = 0;
    virtual ~AbstractStatement() {};
};

template <typename Type>
class Statement : public AbstractStatement {
public:
    Statement(std::string type, Type content) : type{type}, content{content} {};
    
    std::string get_type() override { return this->type;    }
    Type get_content()              { return this->content; }
private:
    std::string type;
    Type content;
};

class Length {
    operator long double() { return this->length_millimeters; }
    operator double()      { return static_cast<double>(this->length_millimeters); }
    operator float()       { return static_cast<float>(this->length_millimeters); }
    
    friend Length millimeters(long double d);
    friend Length inches(long double d);
    friend Length points(long double d);
    friend Length tenths(long double amt, long double conversion);
private:
    Length(double length_millimeters) : length_millimeters(length_millimeters) {};
    
    const long double length_millimeters;
};

inline Length millimeters(long double d) {
    return Length(d);
}

inline Length inches(long double d) {
    return Length(d * 25.4);
}

inline Length points(long double d) {
    return Length(d * 0.3528);
}

inline Length tenths(long double amt, long double conversion) {
    return Length(amt * conversion);
}
    
}

#endif /* statement_hpp */
