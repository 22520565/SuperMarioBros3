#include "Rect2.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect2<T>::Rect2(const Vector2<T> &position, const Vector2<T> &size) noexcept(
        noexcept(left(position.x)) && noexcept(top(position.y))
            && noexcept(width(size.x)) && noexcept(height(size.y)))
        : left(position.x), top(position.y), width(size.x), height(size.y) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    template <typename U>
        requires std::is_arithmetic_v<std::remove_reference_t<U>>
    constexpr Rect2<T>::Rect2(const Rect2<U> &rect2) noexcept(
        noexcept(left(rect2.left)) && noexcept(top(rect2.top))
            && noexcept(width(rect2.width)) && noexcept(height(rect2.height)))
        : left(rect2.left), top(rect2.top), width(rect2.width), height(rect2.height) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector2<T> Rect2<T>::getCenter() const noexcept(
        noexcept(Vector2<T>(this->left + (this->width / T(2)), this->top - (this->height / T(2))))) {
        return Vector2<T>(this->left + (this->width / T(2)), this->top - (this->height / T(2)));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect2<T> Rect2<T>::wrapSizeUnsigned() const noexcept(
        noexcept(Rect2<T>(Rect2<T>()))) {
        const Rect2<T> newRect2 = *this;

        if (newRect2.width < T()) [[unlikely]] {
            newRect2.left += newRect2.width;
            newRect2.width = -newRect2.width;
        }
        if (newRect2.height < T()) [[unlikely]] {
            newRect2.top -= newRect2.height;
            newRect2.height = -newRect2.height;
        }

        return newRect2;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr bool Rect2<T>::contains(const Vector2<T> &point) const noexcept(
        noexcept(wrapSizeUnsigned())) {
        const Rect2<T> wrappedSizeRect2 = this->wrapSizeUnsigned();
        return (point.x >= wrappedSizeRect2.left) &&
               (point.x < (wrappedSizeRect2.left + wrappedSizeRect2.width)) &&
               (point.y <= wrappedSizeRect2.top) &&
               (point.y > (wrappedSizeRect2.top - wrappedSizeRect2.height));
    }
}
