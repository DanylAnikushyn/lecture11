#include <iostream>

// constexpr pow function
template<std::size_t N>
constexpr int pow(int num)
{
    return num * pow<N-1>(num);
}

template<>
constexpr int pow<0>(int)
{
    return 1;
}


template <std::size_t N, typename T, typename... Ts>
constexpr auto max(const T& arg1, const T& arg2, const Ts&... args) 
{
    constexpr auto limit = pow<N>(10);
    const auto constr_arg1 = std::abs(arg1) < limit ? arg1 : (arg1 > 0 ? limit : -limit); 
    const auto constr_arg2 = std::abs(arg2) < limit ? arg2 : (arg2 > 0 ? limit : -limit); 
    const auto result = constr_arg1 > constr_arg2 ? constr_arg1 : constr_arg2;
    if constexpr (sizeof...(args) > 0) return max<N, int>(result, args...);
    return result;
}

int main() 
{
    std::cout << max<2, int>(-102, -111) << std::endl; 
    std::cout << max<1, int>(11, 8, 12, 9) << std::endl;
    std::cout << max<1, int>(-10, 2, 1, -2, 3, 4, 5, 2, 5) << std::endl;
    std::cout << max<0, int>(0, 1, -2, 2) << std::endl;
    return 0;
}