#pragma once
#include "Rect3.hpp"
#include "Transform.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief 3D camera that defines what region is shown on screen.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    class View final {
      public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        ////////////////////////////////////////////////////////////
        constexpr View() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the view from a rectangular and a rotation.
        ///
        /// \param rect3: Rectangular defining the zone to display.
        /// \param angle3: Rotation of the view.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit View(const Rect3<T> &rect3, const Angle3<T> &angle3) noexcept(
            noexcept(Rect3<T>(rect3)) && noexcept(Angle3<T>(angle3)));

        ////////////////////////////////////////////////////////////
        /// \brief Set the rotation of the view.
        ///
        /// The default rotation of a view is (0, 0, 0).
        ///
        /// \param angle3: New rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setRotation(const Angle3<T> &angle3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Reset the view to the given rectangular.
        ///
        /// Note that this function resets the rotation angle to (0, 0, 0).
        ///
        /// \param rect3: Rectangular defining the zone to display.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void reset(const Rect3<T> &rect3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Reset the view to the given rectangular and given rotation.
        ///
        /// \param rect3: Rectangular defining the zone to display.
        /// \param angle3: Rotation of the view.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void reset(const Rect3<T> &rect3, const Angle3<T> &angle3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the rectangular of the view.
        ///
        /// \return Rectangular of the view.
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Rect3<T> &getRect() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the current orientation of the view.
        ///
        /// \return Rotation angle of the view.
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Angle3<T> &getRotation() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Move the view relatively to its current position.
        ///
        /// \param offset: Move offset.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void move(const Vector3<T> &offset) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Rotate the view relatively to its current orientation.
        ///
        /// \param angle3: Angle to rotate.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void rotate(const Angle3<T> &angle3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the projection transform of the view.
        ///
        /// This function is meant for internal use only.
        ///
        /// \return Projection transform defining the view.
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Transform<T> &getTransform() const noexcept;

      private:
        Rect3<T> rect3 = Rect3<T>();                     // View rectangular.
        Angle3<T> rotation = Angle3<T>::zero();          // Angle of rotation of the view rectangular.
        mutable Transform<T> transform = Transform<T>(); // Precomputed projection transform corresponding to the view.
        mutable bool transformNeedUpdate = true;         // Internal state telling if the transform needs to be updated.
    };
}

#include "View.inl"
