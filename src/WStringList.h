#ifndef WSTRINGLIST_H_
#define WSTRINGLIST_H_

#include <vector>

#include <Wt/WString>

namespace Wt
{

class WStringList: public std::vector<WString>
{
public:

    WStringList& operator<<(const WString& str)
    {
        push_back(str);
        return *this;
    }

    WString join(const WString& separator) const
    {
        WString result;

        for (auto iter = cbegin(), end(cend()); iter != end; ++iter)
        {
            result += *iter;
            if ((iter + 1) != end)
            {
                result += separator;
            }
        }

        return result;
    }
};

}

#endif
