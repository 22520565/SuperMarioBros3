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
        constexpr View() noexcept = default;

        ////////////////////////////////////////////////////////////
        /// \brief Construct the view from a rectangular and a rotation.
        ///
        /// \param rect3: Rectangular defining the zone to display.
        /// \param rotation3: Rotation of the view.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit View(const Rect3<T> &rect3, const Rotation3<T> &rotation3) noexcept(
            noexcept(Rect3<T>(rect3)) && noexcept(Rotation3<T>(rotation3)));

        ////////////////////////////////////////////////////////////
        /// \brief Set the rectangular of the view.
        ///
        /// \param newRect3: New rectangular.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setRect(const Rect3<T> &newRect3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Set the rotation of the view.
        ///
        /// \param newRotation3: New rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setRotation(const Rect3<T> &newRotation3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the rectangular of the view.
        ///
        /// \return Rectangular of the view
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Rect3<T> &getRect() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the rotation of the view.
        ///
        /// \return Rotation of the view
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Rotation3<T> &getRotation() const noexcept;

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
        Rotation3<T> rotation3 = Rotation3<T>();         // View rotation.
        mutable Transform<T> transform = Transform<T>(); // Precomputed projection transform corresponding to the view
        mutable bool transformNeedUpdate = false;        // Internal state telling if the transform needs to be updated
    };
}

#include "View.inl"
