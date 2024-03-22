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

#include "Clock.hpp"
#include "Time.hpp"
#include <chrono>

namespace game {
    ////////////////////////////////////////////////////////////
    inline Time Clock::getElapsedTime() const noexcept(
        noexcept(Time() = std::chrono::duration_cast<std::chrono::microseconds>(
                     priv::ClockImpl::now() - priv::ClockImpl::time_point()))) {
        Time result = Time();
        if (isRunning()) [[likely]] {
            result = std::chrono::duration_cast<std::chrono::microseconds>(priv::ClockImpl::now() - this->resetPoint);
        } else [[unlikely]] {
            result = std::chrono::duration_cast<std::chrono::microseconds>(this->stopPoint - this->resetPoint);
        }
        return result;
    }

    ////////////////////////////////////////////////////////////
    inline bool Clock::isRunning() const noexcept(
        noexcept(priv::ClockImpl::time_point() == priv::ClockImpl::time_point())) {
        return this->stopPoint == priv::ClockImpl::time_point();
    }

    ////////////////////////////////////////////////////////////
    inline void Clock::start() noexcept(
        noexcept(priv::ClockImpl::time_point() += (priv::ClockImpl::now() - priv::ClockImpl::time_point()))
            && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point())) {
        if (!isRunning()) [[likely]] {
            this->resetPoint += (priv::ClockImpl::now() - this->stopPoint);
            this->stopPoint = priv::ClockImpl::time_point();
        }
    }

    ////////////////////////////////////////////////////////////
    inline void Clock::stop() noexcept(
        noexcept(Clock().isRunning()) && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point())) {
        if (this->isRunning()) [[likely]] {
            this->stopPoint = priv::ClockImpl::now();
        }
    }

    ////////////////////////////////////////////////////////////
    inline Time Clock::restart() noexcept(
        noexcept(Clock().getElapsedTime()) && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::now())
            && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point())) {
        const Time elapsed = getElapsedTime();
        this->resetPoint = priv::ClockImpl::now();
        this->stopPoint = priv::ClockImpl::time_point();
        return elapsed;
    }

    ////////////////////////////////////////////////////////////
    inline Time Clock::reset() noexcept(
        noexcept(Clock().getElapsedTime()) && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::now())
            && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point())) {
        const Time elapsed = getElapsedTime();
        this->resetPoint = priv::ClockImpl::now();
        this->stopPoint = resetPoint;
        return elapsed;
    }
}
