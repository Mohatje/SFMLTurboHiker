#include "HelperFunctions.h"
#include <string>
namespace turbohiker {

bool HelperFunctions::stringCompare(const std::string& lhs, const std::string& rhs)
{
        if (lhs.size() != rhs.size())
                return false;

        // execute tolower on every char and compare it with rhs
        for (uint32_t i = 0; i < lhs.size(); i++) {
                if (tolower(lhs[i]) != tolower(rhs[i]))
                        return false;
        }
        return true;
}
} // namespace turbohiker