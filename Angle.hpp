////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2024 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once
#include <numbers>
#include <cmath>

namespace game
{
	////////////////////////////////////////////////////////////
	/// \brief Represents an angle value.
	///
	////////////////////////////////////////////////////////////
	class Angle
	{
	public:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor.
		///
		/// Sets the angle value to zero.
		///
		////////////////////////////////////////////////////////////
		constexpr Angle() = default;

		////////////////////////////////////////////////////////////
		/// \brief Return the angle's value in degrees.
		///
		/// \return Angle in degrees.
		///
		/// \see asRadians.
		///
		////////////////////////////////////////////////////////////
		[[nodiscard]] constexpr const float& asDegrees() const { return this->degrees; }

		////////////////////////////////////////////////////////////
		/// \brief Return the angle's value in radians
		///
		/// \return Angle in radians
		///
		/// \see asDegrees
		///
		////////////////////////////////////////////////////////////
		[[nodiscard]] constexpr float asRadians() const { return this->degrees * (std::numbers::pi_v<float> / 180.0F); }

		////////////////////////////////////////////////////////////
		/// \brief Wrap to a range such that -180° <= angle < 180°
		///
		/// Similar to a modulo operation, this returns a copy of the angle
		/// constrained to the range [-180°, 180°) == [-Pi, Pi).
		/// The resulting angle represents a rotation which is equivalent to *this.
		///
		/// \return Signed angle, wrapped to [-180°, 180°)
		///
		/// \see wrapUnsigned
		///
		////////////////////////////////////////////////////////////
		[[nodiscard]] constexpr Angle wrapSigned() const {
			return Angle(std::fmod(this->degrees + 180.0F, 360.0F) - 180.0F);
		}

		////////////////////////////////////////////////////////////
		/// \brief Wrap to a range such that 0° <= angle < 360°
		///
		/// Similar to a modulo operation, this returns a copy of the angle
		/// constrained to the range [0°, 360°) == [0, Tau) == [0, 2*Pi).
		/// The resulting angle represents a rotation which is equivalent to *this.
		///
		/// The name "unsigned" originates from the similarity to unsigned integers:
		/// <table>
		/// <tr>
		///   <th></th>
		///   <th>signed</th>
		///   <th>unsigned</th>
		/// </tr>
		/// <tr>
		///   <td>char</td>
		///   <td>[-128, 128)</td>
		///   <td>[0, 256)</td>
		/// </tr>
		/// <tr>
		///   <td>Angle</td>
		///   <td>[-180°, 180°)</td>
		///   <td>[0°, 360°)</td>
		/// </tr>
		/// </table>
		///
		/// \return Unsigned angle, wrapped to [0°, 360°)
		///
		/// \see wrapSigned
		///
		////////////////////////////////////////////////////////////
		[[nodiscard]] constexpr Angle wrapUnsigned() const { return Angle(std::fmod(this->degrees, 360.0F)); }

		////////////////////////////////////////////////////////////
		// Static member data
		////////////////////////////////////////////////////////////
		// NOLINTNEXTLINE(readability-identifier-naming)
		static const Angle Zero; //!< Predefined 0 degree angle value

	private:
		friend constexpr Angle degrees(float angle);
		friend constexpr Angle radians(float angle);

		////////////////////////////////////////////////////////////
		/// \brief Construct from a number of degrees
		///
		/// This function is internal. To construct angle values,
		/// use sf::radians or sf::degrees instead.
		///
		/// \param degrees Angle in degrees
		///
		////////////////////////////////////////////////////////////
		constexpr explicit Angle(float degrees);

		////////////////////////////////////////////////////////////
		// Member data
		////////////////////////////////////////////////////////////
		float degrees=0.0F; //!< Angle value stored as degrees
	};

	////////////////////////////////////////////////////////////
	/// \brief Construct an angle value from a number of degrees
	///
	/// \param angle Number of degrees
	///
	/// \return Angle value constructed from the number of degrees
	///
	/// \see radians
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle degrees(float angle) { return Angle(angle); }

	////////////////////////////////////////////////////////////
	/// \brief Construct an angle value from a number of radians
	///
	/// \param angle Number of radians
	///
	/// \return Angle value constructed from the number of radians
	///
	/// \see degrees
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle radians(float angle) { return Angle(angle * (180 / std::numbers::pi_v<float>)); }

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of == operator to compare two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return True if both angle values are equal
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator==(Angle left, Angle right){
		return left.asDegrees() == right.asDegrees();
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of != operator to compare two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return True if both angle values are different
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator!=(Angle left, Angle right) {
		return left.asDegrees() != right.asDegrees();
	}


	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of < operator to compare two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return True if \a left is less than \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator<(Angle left, Angle right) {
		return left.asDegrees() < right.asDegrees();
	}


	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of > operator to compare two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return True if \a left is greater than \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator>(Angle left, Angle right) {
		return left.asDegrees() > right.asDegrees();
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of <= operator to compare two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return True if \a left is less than or equal to \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator<=(Angle left, Angle right) {
		return left.asDegrees() <= right.asDegrees();
	}


	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of >= operator to compare two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return True if \a left is greater than or equal to \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr bool operator>=(Angle left, Angle right) {
		return left.asDegrees() >= right.asDegrees();
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of unary - operator to negate an angle value.
	///
	/// Represents a rotation in the opposite direction.
	///
	/// \param right Right operand (an angle)
	///
	/// \return Negative of the angle value
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle operator-(Angle right)
	{
		return degrees(-right.asDegrees());
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary + operator to add two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return Sum of the two angle values
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle operator+(Angle left, Angle right) {
		return degrees(left.asDegrees() + right.asDegrees());
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary += operator to add/assign two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return Sum of the two angle values
	///
	////////////////////////////////////////////////////////////
	constexpr Angle& operator+=(Angle& left, Angle right) {
		return left = left + right;
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary - operator to subtract two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return Difference of the two angle values
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle operator-(Angle left, Angle right) {
		return degrees(left.asDegrees() - right.asDegrees());
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary -= operator to subtract/assign two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return Difference of the two angle values
	///
	////////////////////////////////////////////////////////////
	constexpr Angle& operator-=(Angle& left, Angle right) {
		return left = left - right;
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary * operator to scale an angle value
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (a number)
	///
	/// \return \a left multiplied by \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle operator*(Angle left, float right) {
		return degrees(left.asDegrees() * right);
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary * operator to scale an angle value
	///
	/// \param left  Left operand (a number)
	/// \param right Right operand (an angle)
	///
	/// \return \a left multiplied by \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle operator*(float left, Angle right) {
		return right * left;
	}


	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary *= operator to scale/assign an angle value
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (a number)
	///
	/// \return \a left multiplied by \a right
	///
	////////////////////////////////////////////////////////////
	constexpr Angle& operator*=(Angle& left, float right) {
		return left = left * right;
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary / operator to scale an angle value
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (a number)
	///
	/// \return \a left divided by \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle operator/(Angle left, float right) {
		return degrees(left.asDegrees() / right);
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary /= operator to scale/assign an angle value
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (a number)
	///
	/// \return \a left divided by \a right
	///
	////////////////////////////////////////////////////////////
	constexpr Angle& operator/=(Angle& left, float right) {
		return left = left / right;
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary / operator to compute the ratio of two angle values
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return \a left divided by \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr float operator/(Angle left, Angle right) {
		return left.asDegrees() / right.asDegrees();
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary % operator to compute modulo of an angle value.
	///
	/// Right hand angle must be greater than zero.
	///
	/// Examples:
	/// \code
	/// sf::degrees(90) % sf::degrees(40)  // 10 degrees
	/// sf::degrees(-90) % sf::degrees(40) // 30 degrees (not -10)
	/// \endcode
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return \a left modulo \a right
	///
	////////////////////////////////////////////////////////////
	[[nodiscard]] constexpr Angle operator%(Angle left, Angle right) {
		return degrees(std::fmod(left.asDegrees(), right.asDegrees()));
	}

	////////////////////////////////////////////////////////////
	/// \relates Angle
	/// \brief Overload of binary %= operator to compute/assign remainder of an angle value
	///
	/// \param left  Left operand (an angle)
	/// \param right Right operand (an angle)
	///
	/// \return \a left modulo \a right
	///
	////////////////////////////////////////////////////////////
	constexpr Angle& operator%=(Angle& left, Angle right){ return left = left % right; }
}
