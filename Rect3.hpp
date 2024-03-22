#pragma once
#include "Rect2.hpp"
#include "Vector3.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Utility class for manipulating 3D axis aligned rectangulars.
    ///
    ////////////////////////////////////////////////////////////
    template <typename T>
        requires std::is_arithmetic_v<std::remove_reference_t<T>>
    class Rect3 : public Rect2<T> {
      public:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        T front = T(); // Front coordinate of the rect.
        T depth = T(); // Depth of the rect.

        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        /// Creates an empty rectangular (it is equivalent to calling
        /// Rect3({0, 0, 0}, {0, 0, 0})).
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rect3<T>() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the rectangular from position and size.
        /// Be careful, the last parameter is the size,
        /// not the bottom-right-back corner!
        ///
        /// \param position: Position of the top-left-front corner of the rectangular.
        /// \param size: Size of the rectangular.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rect3(const Vector3<T> &position, const Vector3<T> &size) noexcept(
            noexcept(Rect2<T>(position, size)) && noexcept(T(position.z)) && noexcept(T(size.z)));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a rectangular from a rectangle.
        ///
        /// \param rect2: Rectangle to construct.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rect3(const Rect2<T> &rect2) noexcept(
            noexcept(Rect2<T>(rect2)) && noexcept(T(T())));

        ////////////////////////////////////////////////////////////
        /// \brief Construct a rectangular from a rectangle with
        /// its front coordinate and its depth.
        ///
        /// \param rect2: Rectangle to construct.
        /// \param front: Position of the front.
        /// \param depth: Size in depth.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit Rect3(const Rect2<T> &rect2, const T front, const T depth) noexcept(
            noexcept(Rect2<T>(rect2)) && noexcept(T(front)) && noexcept(T(depth)));

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
            noexcept(Rect2<T>(rect3)) && noexcept(T(static_cast<T>(rect3.front)))
                && noexcept(T(static_cast<T>(rect3.depth))));

        ////////////////////////////////////////////////////////////
        /// \brief Default overload of binary operator ==
        ///
        /// \note Since C++20, if operator == is defined, a!=b can be implicitly rewritten !(a==b).
        /// Thus, it's not necessary to define operator != and you can still use operator != normally.
        ///
        /// \param left: Left operand (a rect3).
        /// \param right: Right operand (a rec3).
        ///
        /// \return True if \a left is equal to \a right.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        friend constexpr bool
        operator==(const Rect3<T> &left, const Rect3<T> &right) = default;

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the rectangular's top-left-front corner
        ///
        /// \return Position of rectangular
        ///
        /// \see getSize, getCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector3<T> getPosition() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the rectangular
        ///
        /// \return Size of rectangle
        ///
        /// \see getPosition, getCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector3<T> getSize() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the center of the rectangular.
        ///
        /// \return Center of rectangular.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Vector3<T> getCenter() const noexcept(
            noexcept(Vector3<T>(Rect2<T>().getCenter(), T() + (T() / static_cast<T>(2)))));

        ////////////////////////////////////////////////////////////
        /// \brief Get a copy of the rectangular that its size
        /// is wrapped to unsigned.
        ///
        /// \return An unsigned-wrapped-size rectangular.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Rect3<T> wrapSizeUnsigned() const noexcept(
            noexcept(Rect3<T>(Rect2<T>().wrapSizeUnsigned(), T(), T())));

        ////////////////////////////////////////////////////////////
        /// \brief Check if a point is inside the rectangular's area.
        ///
        /// This check is non-inclusive. If the point lies on the
        /// edge of the rectangular, this function will return false.
        ///
        /// \param point: Point to test.
        ///
        /// \return True if the point is inside, false otherwise.
        ///
        ////////////////////////////////////////////////////////////
        constexpr bool contains(const Vector3<T> &point) const noexcept(
            noexcept(wrapSizeUnsigned()) && noexcept(Rect2<T>::contains(point)));

        ////////////////////////////////////////////////////////////
        /// \brief Check the intersection between two rectangulars
        ///
        /// \param rect3: Rectangular to test.
        ///
        /// \return Intersection rectangular if intersecting, std::nullopt otherwise.
        ///
        ////////////////////////////////////////////////////////////
        constexpr std::optional<Rect3<T>> findIntersection(const Rect3<T> &rect3) const noexcept(
            noexcept(Rect2<T>::findIntersection(rect3)));
    };

    // Define common types.

    using Rect3c = Rect3<char>;
    using Rect3uc = Rect3<unsigned char>;
    using Rect3s = Rect3<short>;
    using Rect3us = Rect3<unsigned short>;
    using Rect3i = Rect3<int>;
    using Rect3u = Rect3<unsigned>;
    using Rect3l = Rect3<long>;
    using Rect3ul = Rect3<unsigned long>;
    using Rect3ll = Rect3<long long>;
    using Rect3ull = Rect3<unsigned long long>;

    using Rect3i8 = Rect3<int8_t>;
    using Rect3il8 = Rect3<int_least8_t>;
    using Rect3if8 = Rect3<int_fast8_t>;
    using Rect3u8 = Rect3<uint8_t>;
    using Rect3ul8 = Rect3<uint_least8_t>;
    using Rect3uf8 = Rect3<uint_fast8_t>;
    using Rect3i16 = Rect3<int16_t>;
    using Rect3il16 = Rect3<int_least16_t>;
    using Rect3if16 = Rect3<int_fast16_t>;
    using Rect3u16 = Rect3<uint16_t>;
    using Rect3ul16 = Rect3<uint_least16_t>;
    using Rect3uf16 = Rect3<uint_fast16_t>;
    using Rect3i32 = Rect3<int32_t>;
    using Rect3il32 = Rect3<int_least32_t>;
    using Rect3if32 = Rect3<int_fast32_t>;
    using Rect3u32 = Rect3<uint32_t>;
    using Rect3ul32 = Rect3<uint_least32_t>;
    using Rect3uf32 = Rect3<uint_fast32_t>;
    using Rect3i64 = Rect3<int64_t>;
    using Rect3il64 = Rect3<int_least64_t>;
    using Rect3if64 = Rect3<int_fast64_t>;
    using Rect3u64 = Rect3<uint64_t>;
    using Rect3ul64 = Rect3<uint_least64_t>;
    using Rect3uf64 = Rect3<uint_fast64_t>;

    using Rect3f = Rect3<float>;
    using Rect3d = Rect3<double>;
    using Rect3ld = Rect3<long double>;
    using Rect3f16 = Rect3<std::float16_t>;
    using Rect3bf16 = Rect3<std::bfloat16_t>;
    using Rect3f32 = Rect3<std::float32_t>;
    using Rect3f64 = Rect3<std::float64_t>;
    using Rect3f128 = Rect3<std::float128_t>;
}

#include "Rect3.inl"
