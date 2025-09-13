#pragma once

#include <algorithm>
#include <type_traits>
namespace muduo
{

class copyable
{
protected:
    copyable() = default;
    ~copyable() = default;
};

}