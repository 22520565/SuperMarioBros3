#pragma once
#include "Rect3.hpp"
#include "Transform.hpp"
#include <D3DX10.h>

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
        /// \brief Construct the view from a rectangular.
        ///
        /// \param rect3: Rectangular defining the zone to display.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit View(const Rect3<T> &rect3) noexcept(
            noexcept(Vector3<T>(rect3.getCenter())) && noexcept(Vector3<T>(rect3.getSize())));

        ////////////////////////////////////////////////////////////
        /// \brief Construct the view from its center and size.
        ///
        /// \param center Center of the zone to display.
        /// \param size   Size of zone to display.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit View(const Vector3<T> &center, const Vector3<T> &size) noexcept(
            noexcept(Vector3<T>(center)) && noexcept(Vector3<T>(size)));

        ////////////////////////////////////////////////////////////
        /// \brief Set the center of the view
        ///
        /// \param newCenter New center
        ///
        /// \see setSize, getCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setCenter(const Vector3f &newCenter) noexcept {
            this->center = newCenter;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Set the size of the view
        ///
        /// \param newSize New size
        ///
        /// \see setCenter, getCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setSize(const Vector3f &newSize) noexcept {
            this->size = newSize;
        }

        ////////////////////////////////////////////////////////////
        /// \brief Get the center of the view
        ///
        /// \return Center of the view
        ///
        /// \see getSize, setCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Vector3f &getCenter() const noexcept { return this->center; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the view
        ///
        /// \return Size of the view
        ///
        /// \see getCenter, setSize
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Vector3f &getSize() const noexcept { return this->size; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the projection transform of the view.
        ///
        /// This function is meant for internal use only.
        ///
        /// \return Projection transform defining the view.
        ///
        ////////////////////////////////////////////////////////////
        D3DXMATRIX getTransform() const noexcept {
            const Vector3f position = this->center - (this->size) / 2.0F;
            D3DXMATRIX matProjection = D3DXMATRIX();
            D3DXMatrixOrthoOffCenterLH(
                &matProjection,
                position.x,
                position.x + size.x,
                position.y,
                position.y + size.y,
                position.z,
                position.z + size.z);
            return matProjection;
        }

      private:
        Vector3<T> center = Vector3<T>::zero();          // Center of the view, in scene coordinates
        Vector3<T> size = Vector3<T>::zero();            // Size of the view, in scene coordinates
        Angle3<T> rotationAngle3 = Angle3<T>::zero();    // Angle of rotation of the view rectangular
        Angle3<T> rotationCenter = Vector3<T>::zero();   // Center of rotation of the view rectangular
        mutable Transform<T> transform = Transform<T>(); // Precomputed projection transform corresponding to the view
        mutable bool transformNeedUpdate = false;        // Internal state telling if the transform needs to be updated
    };
}
