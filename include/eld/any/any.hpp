#pragma once

#include <utility>
#include <cstddef>
#include <cstdint>

namespace eld
{
    namespace detail
    {
        constexpr size_t storage_size()
        {
            return sizeof(uint64_t[2]);
        }

        template<typename T, bool = (sizeof(T) <= storage_size())>
        struct resource_manager
        {
            // workaround to prevent ICF
            static size_t counter;

            template<typename ... Args>
            static void *allocate(Args && ... args)
            {
                return new T(std::forward<Args>(args)...);
            }

            static void copy(void *from, void *to)
            {
                *static_cast<T*>(to) = *static_cast<T*>(from);
            }

            static void move(void *from, void *to)
            {
                *static_cast<T*>(to) = std::move(static_cast<T&&>(*static_cast<T*>(from)));
            }

            static void deallocate(void *ptr)
            {
                delete static_cast<T*>(ptr);
            }

        };

//        template <typename T>
//        struct resource_manager<T, false>
//        {
//            // workaround to prevent ICF
//            static size_t counter;
//
//        };

        template <typename T>
        using external_manager = resource_manager<T, false>;

        template <typename T>
        using internal_manager = resource_manager<T, true>;

        template<typename T>
        struct tag
        {
            // workaround to prevent ICF
            static size_t counter;
        };

        template<typename T>
        size_t tag<T>::counter = 0;

        template<typename T>
        size_t unique_func()
        {
            return resource_manager<T>::counter;
        }
    }

    class any
    {
    public:

        any() = default;

        template<typename T>
        any(T &&other)
                : ptr_(new T(std::forward<T>(other))),
                  deduce_type_(reinterpret_cast<decltype(deduce_type_)>(&detail::unique_func<T>))
        {}

        template<typename T>
        bool contains_type() const
        {
            auto *ptr = reinterpret_cast<decltype(deduce_type_)>(&detail::unique_func<T>);
            return deduce_type_ == ptr;
        }

    private:
        void *ptr_;
        void (*deduce_type_)();
    };

}