#pragma once
#include "Scalation2.hpp"
#include "Vector3.hpp"
#include <concepts>

namespace game {
    template <typename T>
        requires std::is_arithmetic_v<T>
    class Scalation3 : public Scalation2<T> {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T factorZ = static_cast<T>(1); // Factor to the Z axis.
        T centerZ = static_cast<T>(0); // Z coordinate of the center point.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Scalation3() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Create a rotation with a specified factor and
        /// a specified coordinate of a center point.
        ///
        /// \param factor: Factor of the rotation.
        /// \param center: Coordinate of the center point of the rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit(false) Scalation3(const Vector3<T> &factor, const Vector3<T> &center) noexcept(
            noexcept(Scalation2<T>(factor, center)) && noexcept(T(factor.z)) && noexcept(T(center.z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the scalation3 from another type of scalation3.
        ///
        /// This constructor doesn't replace the copy constructor,
        /// it's called only when U != T.
        /// A call to this constructor will fail to compile if U
        /// is not convertible to T.
        ///
        /// \param scalation2: Scalation3 to convert
        ///
        ////////////////////////////////////////////////////////////
        template <typename U>
            requires std::is_arithmetic_v<U>
        constexpr explicit Scalation3(const Scalation3<U> &scalation3) noexcept(
            noexcept(Scalation2<T>(scalation3)) && noexcept(T(static_cast<T>(scalation3.factorZ)))
                && noexcept(T(static_cast<T>(scalation3.centerZ))));

        ////////////////////////////////////////////////////////////
        /// \brief Default overload of binary operator ==
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (a scalation3).
        /// \param right: Right operand (a scalation3).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Scalation3<T> &left, const Scalation3<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get a vector3 of the rotation's factor.
        ///
        /// \return Vector3 of the rotation's factor.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector3<T> getFactor() const noexcept(
            noexcept(Vector3<T>(Scalation2<T>().getFactor(), T())));

        ////////////////////////////////////////////////////////////
        /// \brief Get an vector3 of the center point's coordinate
        /// of the scalation.
        ///
        /// \return Vector3 of the center point of the scalation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr Vector3<T> getCenter() const noexcept(
            noexcept(Vector3<T>(Scalation2<T>().getCenter(), T())));
    };
}

#include "Scalation3.inl"
