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
        virtual ~AbstractStatement(){};
    };
    
    template <typename Type> class Statement : public AbstractStatement {
    public:
        Statement(std::string type, Type content) : type{type}, content{content} {};
        
        std::string get_type() override { return this->type; }
        Type get_content() const { return this->content; }
        
    private:
        std::string type;
        Type content;
    };
    
} // namespace lmt

#endif /* statement_hpp */
