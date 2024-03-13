#pragma once
#include "Rect2.hpp"
#include "Vector3.hpp"

namespace game {
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    class Rect3 : public Rect2<T> {
      public:
        T front = T();
        T depth = T();
        constexpr Rect3<T>() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the rectangular from position and size.
        /// Be careful, the last parameter is the size,
        /// not the bottom-right-back corner!
        ///
        /// \param position: Position of the top-left corner of the rectangular.
        /// \param size: Size of the rectangular.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rect3(const Vector3<T> &position, const Vector3<T> &size) noexcept(
            noexcept(Rect2<T>(position, size)) && noexcept(T(position.z)) && noexcept(T(size.z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the rectangular from another type of rectangular.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param rec3: Rectangular to convert.
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>
            requires std::is_arithmetic_v<std::remove_reference_t<U>>
        constexpr explicit Rect3(const Rect3<U> &rect3) noexcept(
            noexcept(Rect2<T>(rect3)) && noexcept(T(rect3.front)) && noexcept(T(rect3.depth)));

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the center of the rectangular.
        ///
        /// \return Center of rectangular.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector3<T> getCenter() const noexcept {
            return Vector3<T>(Rect2<T>::getCenter(), this->front + (this->depth / T(2)));
        }
    };
}

#include "Rect3.inl"
