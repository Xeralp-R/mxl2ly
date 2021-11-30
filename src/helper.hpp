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

#endif /* helper_hpp */
