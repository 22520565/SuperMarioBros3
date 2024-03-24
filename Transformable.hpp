#pragma once
#include "Transform.hpp"

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Decomposed transform defined by a position, a rotation and a scale.
    ///
    ////////////////////////////////////////////////////////////
    template <std::floating_point T>
    class Transformable {
      public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        ////////////////////////////////////////////////////////////
        constexpr Transformable() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Virtual destructor
        ///
        ////////////////////////////////////////////////////////////
        constexpr virtual ~Transformable() = default;

        ////////////////////////////////////////////////////////////
        /// \brief Set the position of the object.
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable object is (0, 0, 0).
        ///
        /// \param newPosition: New position.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setPosition(const Vector3<T> &newPosition) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Set the orientation of the object.
        ///
        /// This function completely overwrites the previous rotation.
        /// See the rotate function to add an angle based on the previous rotation angles instead.
        /// The default rotation of a transformable object is (0, 0, 0).
        ///
        /// \param newAngle3: New rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setRotation(const Angle3<T> &newAngle3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Set the scale factors of the object.
        ///
        /// This function completely overwrites the previous scale.
        /// See the scale function to add a factor based on the previous scale instead.
        /// The default scale of a transformable object is (1, 1, 1).
        ///
        /// \param newFactors: New scale factors
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setScale(const Vector3<T> &newFactors) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Set the local origin of the object.
        ///
        /// The origin of an object defines the center point for
        /// all transformations (position, scale, rotation).
        /// The coordinates of this point must be relative to the
        /// center of the object, and ignore all transformations
        /// (position, scale, rotation).
        /// The default origin of a transformable object is (0, 0, 0).
        ///
        /// \param newOrigin: New origin.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setOrigin(const Vector3<T> &newOrigin) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the object.
        ///
        /// \return Current position.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Vector3<T> &getPosition() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the orientation of the object.
        ///
        /// The rotation is always in the range [0, 360) degrees.
        ///
        /// \return Current rotation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Angle3<T> &getRotation() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the current scale of the object.
        ///
        /// \return Current scale factors.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Vector3<T> &getScale() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the local origin of the object.
        ///
        /// \return Current origin.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Vector3<T> &getOrigin() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Move the object by a given offset.
        ///
        /// This function adds to the current position of the object,
        /// unlike setPosition which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// object.setPosition(object.getPosition() + offset);
        /// \endcode
        ///
        /// \param offset: Offset.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void move(const Vector3<T> &offset) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Rotate the object.
        ///
        /// This function adds to the current rotation of the object,
        /// unlike setRotation which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// object.setRotation(object.getRotation() + angle3);
        /// \endcode
        ///
        /// \param angle3 Angle of rotation.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void rotate(const Angle3<T> &angle3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Scale the object.
        ///
        /// This function multiplies the current scale of the object,
        /// unlike setScale which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// sf::Vector2f scale = object.getScale();
        /// object.setScale(scale.x * factor.x, scale.y * factor.y);
        /// \endcode
        ///
        /// \param factor Scale factors.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void scale(const Vector3<T> &factors) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the combined transform of the object.
        ///
        /// \return Transform combining the position/rotation/scalation of the object.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Transform<T> &getTransform() const noexcept;

      private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Vector3<T> origin = Vector3<T>::zero();          // Origin of translation/rotation/scaling of the object.
        Vector3<T> position = Vector3<T>::zero();        // Position of the object.
        Angle3<T> rotation = Angle3<T>::zero();          // Orientation of the object.
        Vector3<T> scaleFactors = Vector3<T>::one();     // Scale factors of the object.
        mutable Transform<T> transform = Transform<T>(); // Combined transformation of the object.
        mutable bool transformNeedUpdate = false;        // Internal state telling if the transform needs to be updated.
    };
}

#include "Transformable.inl"
