#include "Rect2.hpp"
#include "Rect3.hpp"
#include "Vector3.hpp"
#include <optional>
#include <type_traits>

namespace game {
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T>::Rect3(const Vector3<T> &position, const Vector3<T> &size) noexcept(
        noexcept(Rect2<T>(position, size)) && noexcept(T(position.z)) && noexcept(T(size.z)))
        : Rect2<T>(position, size), front(position.z), depth(size.z) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T>::Rect3(const Rect2<T> &rect2) noexcept(
        noexcept(Rect2<T>(rect2)) && noexcept(T(T())))
        : Rect2<T>(rect2), front(T()), depth(T()) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T>::Rect3(const Rect2<T> &rect2, const T front, const T depth) noexcept(
        noexcept(Rect2<T>(rect2)) && noexcept(T(front)) && noexcept(T(depth)))
        : Rect2<T>(rect2), front(front), depth(depth) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    template <typename U>
        requires std::is_arithmetic_v<std::remove_reference_t<U>>
    constexpr Rect3<T>::Rect3(const Rect3<U> &rect3) noexcept(
        noexcept(Rect2<T>(rect3)) && noexcept(T(static_cast<T>(rect3.front)))
            && noexcept(T(static_cast<T>(rect3.depth))))
        : Rect2<T>(rect3), front(static_cast<T>(rect3.front)), depth(static_cast<T>(rect3.depth)) {}

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector3<T> Rect3<T>::getPosition() const noexcept {
        return Vector3<T>(this->Rect2<T>::getPosition(), this->front);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector3<T> Rect3<T>::getSize() const noexcept {
        return Vector3<T>(this->Rect2<T>::getSize(), this->depth);
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Vector3<T> Rect3<T>::getCenter() const noexcept(
        noexcept(Vector3<T>(Rect2<T>().getCenter(), T() + (T() / static_cast<T>(2))))) {
        return Vector3<T>(Rect2<T>::getCenter(), this->front + (this->depth / static_cast<T>(2)));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr Rect3<T> Rect3<T>::wrapSizeUnsigned() const noexcept(
        noexcept(Rect3<T>(Rect2<T>().wrapSizeUnsigned(), T(), T()))) {
        Rect3<T> newRect3 = Rect3<T>(this->Rect2<T>::wrapSizeUnsigned(), this->front, this->depth);

        if (newRect3.depth < T()) [[unlikely]] {
            newRect3.front += newRect3.depth;
            newRect3.depth = -newRect3.depth;
        }

        return newRect3;
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr bool Rect3<T>::contains(const Vector3<T> &point) const noexcept(
        noexcept(wrapSizeUnsigned()) && noexcept(Rect2<T>::contains(point))) {
        const Rect3<T> wrappedSizeRect3 = this->wrapSizeUnsigned();
        return wrappedSizeRect3.Rect2<T>::contains(point) &&
               (point.z >= wrappedSizeRect3.front) &&
               (point.z < (wrappedSizeRect3.front + wrappedSizeRect3.depth));
    }

    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    constexpr std::optional<Rect3<T>> Rect3<T>::findIntersection(const Rect3<T> &rect3) const noexcept(
        noexcept(Rect2<T>::findIntersection(rect3))) {
        std::optional<Rect3<T>> result = std::nullopt;

        if (const auto intersectionRect2 = this->Rect2<T>::findIntersection(rect3);
            intersectionRect2.has_value()) [[unlikely]] {
            // Compute the min and max of the both rectangulars on axes Z.
            const T r1MinZ = (std::min)(this->front, this->front + this->depth);
            const T r1MaxZ = (std::max)(this->front, this->front + this->depth);
            const T r2MinZ = (std::min)(rect3.front, rect3.front + rect3.depth);
            const T r2MaxZ = (std::max)(rect3.front, rect3.front + rect3.depth);

            // Compute the intersection boundaries.
            const T interFront = (std::max)(r1MinZ, r2MinZ);
            const T interBack = (std::min)(r1MaxZ, r2MaxZ);

            // If the intersection is valid (positive non zero area), then there is an intersection.
            if (interFront < interBack) [[unlikely]] {
                result = Rect3<T>(*intersectionRect2, interFront, interBack - interFront);
            }
        }

        return result;
    }
}
