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
// *. This header file has been altered after copying from origin!
//
////////////////////////////////////////////////////////////

#pragma once
#include "Time.hpp"
#include <chrono>
#include <type_traits>
#include <ratio>

namespace game {
    namespace priv {
        ////////////////////////////////////////////////////////////
        /// \brief Chooses a monotonic clock of highest resolution.
        ///
        /// The high_resolution_clock is usually an alias for other
        /// clocks: steady_clock or system_clock, whichever has a
        /// higher precision.
        ///
        /// game::Clock, however, is aimed towards monotonic time
        /// measurements and so system_clock could never be a choice
        /// as its subject to discontinuous jumps in the system time
        /// (e.g., if the system administrator manually changes
        /// the clock), and by the incremental adjustments performed
        /// by `adjtime` and Network Time Protocol. On the other
        /// hand, monotonic clocks are unaffected by this behavior.
        ///
        /// Note: Linux implementation of a monotonic clock that
        /// takes sleep time into account is represented by
        /// CLOCK_BOOTTIME. Android devices can define the macro:
        /// SFML_ANDROID_USE_SUSPEND_AWARE_CLOCK to use a separate
        /// implementation of that clock, instead.
        ///
        /// For more information on Linux clocks visit:
        /// https://linux.die.net/man/2/clock_gettime
        ///
        ////////////////////////////////////////////////////////////
#if defined(SFML_SYSTEM_ANDROID) && defined(SFML_ANDROID_USE_SUSPEND_AWARE_CLOCK)
        using ClockImpl = SuspendAwareClock;
#else
        using ClockImpl = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
                                             std::chrono::high_resolution_clock,
                                             std::chrono::steady_clock>;
#endif

        static_assert(ClockImpl::is_steady, "Provided implementation is not a monotonic clock");
        static_assert(std::ratio_less_equal_v<ClockImpl::period, std::micro>,
                      "Clock resolution is too low. Expecting at least a microsecond precision");
    }
    class Time;

    class Clock {
      public:
        ////////////////////////////////////////////////////////////
        /// \brief Get the elapsed time.
        ///
        /// This function returns the time elapsed since the last call
        /// to restart() (or the construction of the instance if restart()
        /// has not been called).
        ///
        /// \return Time elapsed.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        Time getElapsedTime() const noexcept(
            noexcept(Time() = std::chrono::duration_cast<std::chrono::microseconds>(
                         priv::ClockImpl::now() - priv::ClockImpl::time_point())));

        ////////////////////////////////////////////////////////////
        /// \brief Check whether the clock is running.
        ///
        /// \return True if the clock is running, false otherwise.
        ///
        ////////////////////////////////////////////////////////////
        [[nodiscard]]
        bool isRunning() const noexcept(
            noexcept(priv::ClockImpl::time_point() == priv::ClockImpl::time_point()));

        ////////////////////////////////////////////////////////////
        /// \brief Start the clock.
        ///
        /// \see stop.
        ///
        ////////////////////////////////////////////////////////////
        void start() noexcept(
            noexcept(priv::ClockImpl::time_point() += (priv::ClockImpl::now() - priv::ClockImpl::time_point()))
                && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point()));

        ////////////////////////////////////////////////////////////
        /// \brief Stop the clock.
        ///
        /// \see start.
        ///
        ////////////////////////////////////////////////////////////
        void stop() noexcept(
            noexcept(Clock().isRunning()) && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point()));

        ////////////////////////////////////////////////////////////
        /// \brief Restart the clock.
        ///
        /// This function puts the time counter back to zero, returns
        /// the elapsed time, and leaves the clock in a running state.
        ///
        /// \return Time elapsed.
        ///
        /// \see reset.
        ///
        ////////////////////////////////////////////////////////////
        Time restart() noexcept(
            noexcept(Clock().getElapsedTime()) && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::now())
                && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point()));

        ////////////////////////////////////////////////////////////
        /// \brief Reset the clock.
        ///
        /// This function puts the time counter back to zero, returns
        /// the elapsed time, and leaves the clock in a paused state.
        ///
        /// \return Time elapsed.
        ///
        /// \see restart.
        ///
        ////////////////////////////////////////////////////////////
        Time reset() noexcept(
            noexcept(Clock().getElapsedTime()) && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::now())
                && noexcept(priv::ClockImpl::time_point() = priv::ClockImpl::time_point()));

      private:
        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        priv::ClockImpl::time_point resetPoint = priv::ClockImpl::now();         //!< Time of last reset.
        priv::ClockImpl::time_point stopPoint = priv::ClockImpl::time_point(); //!< Time of last stop.
    };
}

#include "Clock.inl"
