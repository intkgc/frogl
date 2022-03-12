//
// Created by kirbo on 12.03.2022.
//

#ifndef FROGL_COMPILER_H
#define FROGL_COMPILER_H

#endif //FROGL_COMPILER_H

namespace froglm {
    class compiler {
    public:
        static bool is_function(std::string str);
        static bool is_variable(std::string str);

        static std::string without_spaces(std::string basicString);
    };
}