//
//  helper.hpp
//  mxl2ly
//
//  Created by Reventar on 17/11/2021.
//

#ifndef helper_hpp
#define helper_hpp

template<class InputIt, class T>
constexpr bool is_element(InputIt first, InputIt last, const T& value)
{
    for (; first != last; ++first) {
        if (*first == value) {
            return true;
        }
    }
    return false;
}

namespace lmt {
    class Length {
        operator long double() { return this->length_millimeters; }
        operator double() { return static_cast<double>(this->length_millimeters); }
        operator float() { return static_cast<float>(this->length_millimeters); }
        
        friend Length millimeters(long double d);
        friend Length inches(long double d);
        friend Length points(long double d);
        friend Length tenths(long double amt, long double conversion);
        
    private:
        Length(double length_millimeters) : length_millimeters(length_millimeters){};
        
        const long double length_millimeters;
    };
    
    inline Length millimeters(long double d) { return Length(d); }
    
    inline Length inches(long double d) { return Length(d * 25.4); }
    
    inline Length points(long double d) { return Length(d * 0.3528); }
    
    inline Length tenths(long double amt, long double conversion) {
        return Length(amt * conversion);
    }
}

#endif /* helper_hpp */
