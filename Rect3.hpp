#pragma once
#include "Vector3.hpp"
#include "Rect.hpp"

namespace game {
template <typename T>
class Rect3 {
public:
	Vector3<T> position = Vector3<T>::zero();
	Vector3<T> size = Vector3<T>::zero();
	constexpr Rect3<T>() = default;

	constexpr explicit Rect3(const Vector3<T>& position, const Vector3<T>& size) noexcept(
		noexcept(Vector3<T>(position)) && noexcept(Vector3<T>(size)))
		: position(position), size(size) {}

        /// \brief Construct the rectangular from another type of rectangular.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param rec3: Rectangular to convert.
    template <typename U>
    constexpr explicit Rect3(const Rect3<U>& rect3) noexcept(
        noexcept(Vector3<T>(static_cast<Vector3<T>>(rect3.position)))
        && noexcept(Vector3<T>(static_cast<Vector3<T>>(rect3.size))))
        : position(static_cast<Vector3<T>>(rect3.position)), size(static_cast<Vector3<T>>(rect3.size)) {}
};
}
