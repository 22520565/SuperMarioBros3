#pragma once
#include "Rotation3.hpp"
#include "Scalation3.hpp"
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
        /// \param newRotation: New rotation3.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setRotation(const Rotation3<T> &newRotation) noexcept;

        ////////////////////////////////////////////////////////////
        /// \brief Set the scalation of the object.
        ///
        /// This function completely overwrites the previous scalation.
        /// See the scale function to add a factor based on the previous scale instead.
        /// The default scalation factor of a transformable object is (1, 1, 1).
        /// The default coordinate of scalation center point of a transformable object is (0, 0, 0).
        ///
        /// \param newScalation: New scalation3.
        ///
        ////////////////////////////////////////////////////////////
        constexpr void setScalation(const Scalation3<T> &newScalation) noexcept;

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
        /// \brief Get the current scalation of the object.
        ///
        /// \return Current scaling.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        constexpr const Vector3<T> &getScalation() const noexcept;

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
        /// auto scalation = object.getScalation();
        /// scalation.factorX*=factor.x;
        /// scalation.factorY*=factor.y;
        /// scalation.factorZ*=factor.z;
        /// object.setScalation(scalation);
        /// \endcode
        ///
        /// \param factor: Scalation factor.
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
        Vector3<T> position = Vector3<T>::zero();        // Position of the object.
        Rotation3<T> rotation = Rotation3<T>();          // Rotation of the object.
        Scalation3<T> scalation = Scalation3<T>();       // Scalation of the object.
        mutable Transform<T> transform = Transform<T>(); // Transform of the object.
        mutable bool transformNeedUpdate = false;        // Determinate whether the transform needs update or not.
    };
}

#include "Transformable.inl"
