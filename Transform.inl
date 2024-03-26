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
// *. This inline file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////

#include "Angle.hpp"
#include "Angle3.hpp"
#include "D3DX10math.h"
#include "Transform.hpp"
#include "Vector3.hpp"
#include <minwindef.h>
#include <type_traits>
#include <array>
#include "Rect3.hpp"
#include "Rotation3.hpp"
#include "Scalation3.hpp"

namespace game {
	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T>::Transform(const T f00, const T f01, const T f02, const T f03,
		const T f10, const T f11, const T f12, const T f13,
		const T f20, const T f21, const T f22, const T f23,
		const T f30, const T f31, const T f32, const T f33) noexcept
		: f00(f00), f01(f01), f02(f02), f03(f03),
		f10(f10), f11(f11), f12(f12), f13(f13),
		f20(f20), f21(f21), f22(f22), f23(f23),
		f30(f30), f31(f31), f32(f32), f33(f33) {}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	Transform<T>::operator D3DXMATRIX() const {
		return D3DXMATRIX(
			static_cast<FLOAT>(f00), static_cast<FLOAT>(f10), static_cast<FLOAT>(f20), static_cast<FLOAT>(f30),
			static_cast<FLOAT>(f01), static_cast<FLOAT>(f11), static_cast<FLOAT>(f21), static_cast<FLOAT>(f31),
			static_cast<FLOAT>(f02), static_cast<FLOAT>(f12), static_cast<FLOAT>(f22), static_cast<FLOAT>(f32),
			static_cast<FLOAT>(f03), static_cast<FLOAT>(f13), static_cast<FLOAT>(f23), static_cast<FLOAT>(f33));
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::combine(const Transform<T>& transform) const noexcept {
		return Transform<T>(
			(this->f00 * transform.f00) + (this->f01 * transform.f10) + (this->f02 * transform.f20) + (this->f03 * transform.f30),
			(this->f00 * transform.f01) + (this->f01 * transform.f11) + (this->f02 * transform.f21) + (this->f03 * transform.f31),
			(this->f00 * transform.f02) + (this->f01 * transform.f12) + (this->f02 * transform.f22) + (this->f03 * transform.f32),
			(this->f00 * transform.f03) + (this->f01 * transform.f13) + (this->f02 * transform.f23) + (this->f03 * transform.f33),
			(this->f10 * transform.f00) + (this->f11 * transform.f10) + (this->f12 * transform.f20) + (this->f13 * transform.f30),
			(this->f10 * transform.f01) + (this->f11 * transform.f11) + (this->f12 * transform.f21) + (this->f13 * transform.f31),
			(this->f10 * transform.f02) + (this->f11 * transform.f12) + (this->f12 * transform.f22) + (this->f13 * transform.f32),
			(this->f10 * transform.f03) + (this->f11 * transform.f13) + (this->f12 * transform.f23) + (this->f13 * transform.f33),
			(this->f20 * transform.f00) + (this->f21 * transform.f10) + (this->f22 * transform.f20) + (this->f23 * transform.f30),
			(this->f20 * transform.f01) + (this->f21 * transform.f11) + (this->f22 * transform.f21) + (this->f23 * transform.f31),
			(this->f20 * transform.f02) + (this->f21 * transform.f12) + (this->f22 * transform.f22) + (this->f23 * transform.f32),
			(this->f20 * transform.f03) + (this->f21 * transform.f13) + (this->f22 * transform.f23) + (this->f23 * transform.f33),
			(this->f30 * transform.f00) + (this->f31 * transform.f10) + (this->f32 * transform.f20) + (this->f33 * transform.f30),
			(this->f30 * transform.f01) + (this->f31 * transform.f11) + (this->f32 * transform.f21) + (this->f33 * transform.f31),
			(this->f30 * transform.f02) + (this->f31 * transform.f12) + (this->f32 * transform.f22) + (this->f33 * transform.f32),
			(this->f30 * transform.f03) + (this->f31 * transform.f13) + (this->f32 * transform.f23) + (this->f33 * transform.f33));
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::translate(const Vector3<T>& offset) const noexcept {
		const Transform<T> translationTransform = Transform<T>(
			static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0), offset.x,
			static_cast<T>(0.0), static_cast<T>(1.0), static_cast<T>(0.0), offset.y,
			static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0), offset.z,
			static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));
		return this->combine(translationTransform);
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::rotate(const Angle3<T>& angle3) const noexcept {
		const Vector3<T> rad = angle3.asRadians();
		const T cosX = std::cos(rad.x);
		const T sinX = std::sin(rad.x);
		const T cosY = std::cos(rad.y);
		const T sinY = std::sin(rad.y);
		const T cosZ = std::cos(rad.z);
		const T sinZ = std::sin(rad.z);

		// const Transform rotationX = Transform(
		//	1.0F, 0.0F, 0.0F, 0.0F,
		//	0.0F, cosX, -sinX, 0.0F,
		//	0, sinX, cosX, 0.0F,
		//	0.0F, 0.0F, 0.0F, 1.0F);
		// const Transform rotationY = Transform(
		//	cosY, 0.0F, sinY, 0.0F,
		//	0.0F, 1.0F, 0.0F, 0.0F,
		//	-sinY, 0.0F, cosY, 0.0F,
		//	0.0F, 0.0F, 0.0F, 1.0F);
		// const Transform rotationZ = Transform(
		//	cosZ, -sinZ, 0.0F, 0.0F,
		//	sinZ, cosZ, 0.0F, 0.0F,
		//	0.0F, 0.0F, 1.0F, 0.0F,
		//	0.0F, 0.0F, 0.0F, 1.0F);
		const Transform<T> rotation = Transform<T>(
			cosY * cosZ, -(cosY * sinZ), sinY, static_cast<T>(0.0),
			(cosX * sinZ) + (sinX * sinY * cosZ), (cosX * cosZ) - (sinX * sinY * sinZ), -(sinX * cosY), static_cast<T>(0.0),
			(sinX * sinZ) - (cosX * sinY * cosZ), (sinX * cosZ) + (sinY * cosX * sinZ), cosX * cosY, static_cast<T>(0.0),
			static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));

		return this->combine(rotation);
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::rotate(const Angle3<T>& angle3, const Vector3<T>& center) const noexcept {
		const Vector3<T> rad = angle3.asRadians();
		const T cosX = std::cos(rad.x);
		const T sinX = std::sin(rad.x);
		const T cosY = std::cos(rad.y);
		const T sinY = std::sin(rad.y);
		const T cosZ = std::cos(rad.z);
		const T sinZ = std::sin(rad.z);

		const T t1 = cosY * cosZ;
		const T t2 = -(cosY * sinZ);
		const T t3 = (cosX * sinZ) + (sinX * sinY * cosZ);
		const T t4 = (cosX * cosZ) - (sinX * sinY * sinZ);
		const T t5 = -(sinX * cosY);
		const T t6 = (sinX * sinZ) - (cosX * sinY * cosZ);
		const T t7 = (sinX * cosZ) + (sinY * cosX * sinZ);
		const T t8 = cosX * cosY;

		const Transform<T> rotation = Transform<T>(
			t1, t2, sinY, (center.x * (t1 - static_cast<T>(1.0))) + (center.y * t2) + (center.z * sinY),
			t3, t4, t5, (center.x * t3) + (center.y * (t4 - static_cast<T>(1.0))) + (center.z * t5),
			t6, t7, t8, (center.x * t6) + (center.y * t7) + (center.z * (t8 - static_cast<T>(1.0))),
			static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));

		return this->combine(rotation);
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::rotate(const Rotation3<T>& rotation3) const noexcept {
		return this->rotate(rotation3.getAngle(), rotation3.getCenter());
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::rotate(const Angle<T> angle, const Vector3<T>& axis) const noexcept {
		const T radAngle = angle.asRadians();
		const T sinAngle = std::sin(radAngle);
		const T cosAngle = std::cos(radAngle);

		const Transform<T> rotationTransform = Transform<T>(
			cosAngle + ((static_cast<T>(1.0) - std::cos(angle)) * axis.x * axis.x),
			((static_cast<T>(1.0) - std::cos(angle)) * axis.x * axis.y) - (sinAngle * axis.z),
			((static_cast<T>(1.0) - std::cos(angle)) * axis.x * axis.z) + (sin(angle) * axis.y),
			static_cast<T>(0.0),
			((static_cast<T>(1.0) - std::cos(angle)) * axis.x * axis.y) + (sinAngle * axis.z),
			cosAngle + ((static_cast<T>(1.0) - std::cos(angle)) * axis.y * axis.y),
			((static_cast<T>(1.0) - std::cos(angle)) * axis.y * axis.z) - (sinAngle * axis.x),
			static_cast<T>(0.0),
			((static_cast<T>(1.0) - std::cos(angle)) * axis.x * axis.z) - (sinAngle * axis.y),
			((static_cast<T>(1.0) - std::cos(angle)) * axis.y * axis.z) + (sinAngle * axis.x),
			cosAngle + ((static_cast<T>(1.0) - std::cos(angle)) * axis.z * axis.z),
			static_cast<T>(0.0),
			static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));

		return this->combine(rotationTransform);
	}

	// TODO: Calc this!
	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::rotate(const Angle<T> angle, const Vector3<T>& axis,
		const Vector3<T>& center) const noexcept {
		return this->translate(-center).rotate(angle, axis).translate(center);
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::scale(const Vector3<T>& factor) const noexcept {
		const Transform<T> scalingTransform = Transform<T>(
			factor.x, static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0),
			static_cast<T>(0.0), factor.y, static_cast<T>(0.0), static_cast<T>(0.0),
			static_cast<T>(0.0), static_cast<T>(0.0), factor.z, static_cast<T>(0.0),
			static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));
		return this->combine(scalingTransform);
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::scale(const Vector3<T>& factor, const Vector3<T>& center) const noexcept {
		const Transform<T> scalingTransform = Transform<T>(
			factor.x, static_cast<T>(0.0), static_cast<T>(0.0), (static_cast<T>(1.0) - factor.x) * center.x,
			static_cast<T>(0.0), factor.y, static_cast<T>(0.0), (static_cast<T>(1.0) - factor.y) * center.y,
			static_cast<T>(0.0), static_cast<T>(0.0), factor.z, (static_cast<T>(1.0) - factor.z) * center.z,
			static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(1.0));
		return this->combine(scalingTransform);
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Transform<T> Transform<T>::scale(const Scalation3<T>& scalation3) const noexcept {
		return this->scale(scalation3.getFactor(), scalation3.getCenter());
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Vector3<T> Transform<T>::transformPoint(const Vector3<T>& point) const noexcept {
		return Vector3<T>(point.x * this->f00 + point.y * this->f01 + point.z * this->f02 + this->f03,
			point.x * this->f10 + point.y * this->f11 + point.z * this->f12 + this->f13,
			point.x * this->f20 + point.y * this->f21 + point.z * this->f22 + this->f23);
	}

	////////////////////////////////////////////////////////////
	template <typename T>
		requires std::is_floating_point_v<std::remove_reference_t<T>>
	constexpr Rect3<T> Transform<T>::transformRect(const Rect3<T>& rect3) const noexcept {
		// Transform the 8 corners of the rectangular
		const std::array<Vector3<T>, 8UL> points = std::array<Vector3<T>, 8UL>{
			transformPoint(Vector3<T>(rect3.left, rect3.top, rect3.front)),
				transformPoint(Vector3<T>(rect3.left + rect3.width, rect3.top, rect3.front)),
				transformPoint(Vector3<T>(rect3.left, rect3.top - rect3.height, rect3.front)),
				transformPoint(Vector3<T>(rect3.left + rect3.width, rect3.top - rect3.height, rect3.front)),
				transformPoint(Vector3<T>(rect3.left, rect3.top, rect3.front + rect3.depth)),
				transformPoint(Vector3<T>(rect3.left + rect3.width, rect3.top, rect3.front + rect3.depth)),
				transformPoint(Vector3<T>(rect3.left, rect3.top - rect3.height, rect3.front + rect3.depth)),
				transformPoint(Vector3<T>(rect3.left + rect3.width, rect3.top - rect3.height, rect3.front + rect3.depth)),
		};

		T left = points[0].x;
		T top = points[0].y;
		T front = points[0].z;
		T right = points[0].x;
		T bottom = points[0].y;
		T back = points[0].z;

		for (std::size_t i = 1UL; i < points.size(); ++i)
		{
			if (points[i].x < left) { left = points[i].x; }
			else if (points[i].x > right) { right = points[i].x; }

			if (points[i].y > top) { top = points[i].y; }
			else if (points[i].y < bottom) { bottom = points[i].y; }

			if (points[i].z < front) { front = points[i].z; }
			else if (points[i].z > back) { back = points[i].z; }
		}

		return Rect3<T>(Vector3<T>(left, top, front), Vector3<T>(right - left, top - bottom, back - front));
	}
}
