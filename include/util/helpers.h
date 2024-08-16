#include <type_traits>

template <typename T> 
using enable_if_float = std::enable_if_t<std::is_floating_point_v<T>>;