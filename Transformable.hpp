#pragma once
#include "Rotation3.hpp"
#include "Transform.hpp"
#include <cmath>
#include <cstdint>

namespace game {
    ////////////////////////////////////////////////////////////
    /// \brief Decomposed transform defined by a position,
    /// a rotation and a scalation.
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
        /// \brief Set the rotation of the object.
        ///
        /// This function completely overwrites the previous rotation.
        /// See the rotate function to add an angle based on the previous rotation angles instead.
        /// The default rotation angles of a transformable object is (0, 0, 0).
        /// The default coordinate of rotation center point of a transformable object is (0, 0, 0).
        ///
        /// \param rotation: New rotation3.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setRotation(const Rotation3<T> &newRotation) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Set the scalation of the object.
        ///
        /// This function completely overwrites the previous scalation
        /// except the scalation center point.
        /// See the scale function to add a factor based on the previous scale instead.
        /// The default scalation factor of a transformable object is (1, 1, 1).
        /// The default coordinate of scalation center point of a transformable object is (0, 0, 0).
        ///
        /// \param factor: Scaling factor in three dimensions.
        /// \param center: Coordinate of the center point to scale.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setScalation(const Vector3<T> &factor) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Set the scalation of the object.
        ///
        /// This function completely overwrites the previous scalation.
        /// See the scale function to add a factor based on the previous scale instead.
        /// The default scalation factor of a transformable object is (1, 1, 1).
        /// The default coordinate of scalation center point of a transformable object is (0, 0, 0).
        ///
        /// \param factor: Scaling factor in three dimensions.
        /// \param center: Coordinate of the center point to scale.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setScalation(const Vector3<T> &factor, const Vector3<T> &center) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the position of the object.
        ///
        /// \return Current position.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Vector3<T> &getPosition() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the rotation of the object.
        ///
        /// \return Current rotation.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Rotation3<T> &getRotation() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the current scalation factor of the object.
        ///
        /// \return Current scaling factor in three dimensions.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Vector3<T> &getScalationFactor() const noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the coordinate of the current scalation center of the object.
        ///
        /// \return Current scalation center.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Vector3<T> &getScalationCenter() const noexcept;

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
        ////////////////////////////////////////////////////////////
        constexpr void move(const Vector3<T> &offset) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Rotate the object.
        ///
        /// This function adds angle to the current rotation angle of the object,
        /// unlike setRotation which overwrites it. The rotation center point stays remain.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// auto rotation = object.getRotation();
        /// object.setRotation({rotation.getAngle() + angle, rotation.getCenter()});
        /// \endcode
        ///
        /// \param angle3: Rotation angle.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void rotate(const Angle3<T> &angle3) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Scale the object.
        ///
        /// This function multiplies factors with the current scale factors of the object,
        /// unlike setScale which overwrites it. The scalation center point stays remain.
        /// Thus, it is equivalent to the following code:
        /// \code
        /// auto scalationFactor = object.getScalationFactor();
        /// scalationFactor.x*=factor.x;
        /// scalationFactor.y*=factor.y;
        /// scalationFactor.z*=factor.z;
        /// object.setScalation(scalationFactor, object.getScalationCenter());
        /// \endcode
        ///
        /// \param factor: Scaling factor in three dimensions.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void scale(const Vector3<T> &factor) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Get the combined transform of the object.
        ///
        /// \return Transform combining the position/rotation/scalation of the object.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Transform<T> &getTransform() const;

      private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Vector3<T> position = Vector3<T>::zero(); // Position of the object.
        Rotation3<T> rotation = Rotation3<T>();
        Vector3<T> scalationFactor = Vector3<T>::one();  // Scalation factor of the object.
        Vector3<T> scalationCenter = Vector3<T>::zero(); // Scalation center point of the object.
        mutable Transform<T> transform = Transform<T>();
        mutable bool transformNeedUpdate = false;
    };
}

#include "Transformable.inl"
