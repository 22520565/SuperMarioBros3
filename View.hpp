#pragma once
#include "Rect3.hpp"
#include "Transform.hpp"
#include <D3DX10.h>

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief 3D camera that defines what region is shown on screen.
    ///
    ////////////////////////////////////////////////////////////
    class View final {
      public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// This constructor creates a default view of (0, 0, 1000, 1000).
        ///
        ////////////////////////////////////////////////////////////
        constexpr View();

        ////////////////////////////////////////////////////////////
        /// \brief Construct the view from a rectangular.
        ///
        /// \param rectangle Rectangular defining the zone to display.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit View(const Rect3<FLOAT> &rectangular);

        ////////////////////////////////////////////////////////////
        /// \brief Construct the view from its center and size.
        ///
        /// \param center Center of the zone to display.
        /// \param size   Size of zone to display.
        ///
        ////////////////////////////////////////////////////////////
        constexpr explicit View(const Vector3<FLOAT> &center, const Vector3<FLOAT> &size);

        ////////////////////////////////////////////////////////////
        /// \brief Set the target viewport
        ///
        /// The viewport is the rectangle into which the contents of the
        /// view are displayed, expressed as a factor (between 0 and 1)
        /// of the size of the RenderTarget to which the view is applied.
        /// For example, a view which takes the left side of the target would
        /// be defined with View.setViewport(sf::FloatRect(0, 0, 0.5, 1)).
        /// By default, a view has a viewport which covers the entire target.
        ///
        /// \param viewport New viewport rectangular.
        ///
        ////////////////////////////////////////////////////////////
        void setViewport(const Rect<FLOAT> &viewport);

        ////////////////////////////////////////////////////////////
        /// \brief Set the center of the view
        ///
        /// \param newCenter New center
        ///
        /// \see setSize, getCenter
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setCenter(const Vector3<FLOAT> &newCenter) noexcept {
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
        constexpr void setSize(const Vector3<FLOAT> &newSize) noexcept {
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
        constexpr const Vector3<FLOAT> &getCenter() const noexcept { return this->center; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the view
        ///
        /// \return Size of the view
        ///
        /// \see getCenter, setSize
        ///
        ////////////////////////////////////////////////////////////
        constexpr const Vector3<FLOAT> &getSize() const noexcept { return this->size; }

        ////////////////////////////////////////////////////////////
        /// \brief Get the projection transform of the view.
        ///
        /// This function is meant for internal use only.
        ///
        /// \return Projection transform defining the view.
        ///
        ////////////////////////////////////////////////////////////
        D3DXMATRIX getTransform() const noexcept {
           const Vector3<FLOAT> position = this->center - (this->size) / 2.0F;
            D3DXMATRIX matProjection = D3DXMATRIX();
            D3DXMatrixOrthoOffCenterLH(
                &matProjection,
                position.x,
                position.x+size.x,
                position.y,
                position.y+size.y,
                position.z,
                position.z+size.z);
            return matProjection;
        }

      private:
        Vector3<FLOAT> center; // Center of the view, in scene coordinates
        Vector3<FLOAT> size;   // Size of the view, in scene coordinates
        FLOAT rotation;        // Angle of rotation of the view rectangle, in degrees
        Rect<FLOAT> viewport = // Viewport rectangle, expressed as a factor of the render-target's size
            Rect<FLOAT>(Vector2<FLOAT>::zero(), Vector2<FLOAT>::one());
    };
}
