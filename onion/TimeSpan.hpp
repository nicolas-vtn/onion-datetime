#pragma once

#include <chrono>
#include <string>
#include <type_traits>

namespace onion
{
	class TimeSpan
	{
		// ----- Constructors / Destructor -----
	  public:
		TimeSpan() = default;
		TimeSpan(const std::chrono::duration<int64_t, std::nano>& duration);
		TimeSpan(int64_t days,
				 int64_t hours,
				 int64_t minutes,
				 int64_t seconds,
				 int64_t milliseconds = 0,
				 int64_t microseconds = 0,
				 int64_t nanoseconds = 0);

		static TimeSpan Zero();
		static TimeSpan FromDays(int64_t days);
		static TimeSpan FromHours(int64_t hours);
		static TimeSpan FromMinutes(int64_t minutes);
		static TimeSpan FromSeconds(int64_t seconds);
		static TimeSpan FromMilliseconds(int64_t milliseconds);
		static TimeSpan FromMicroseconds(int64_t microseconds);
		static TimeSpan FromNanoseconds(int64_t nanoseconds);
		static TimeSpan MaxValue();
		static TimeSpan MinValue();

		// ----- OPERATORS -----
	  public:
		bool operator==(const TimeSpan& other) const = default;
		bool operator!=(const TimeSpan& other) const = default;
		bool operator<(const TimeSpan& other) const;
		bool operator<=(const TimeSpan& other) const;
		bool operator>(const TimeSpan& other) const;
		bool operator>=(const TimeSpan& other) const;

		TimeSpan operator+(const TimeSpan& other) const;
		TimeSpan operator-(const TimeSpan& other) const;

		TimeSpan& operator+=(const TimeSpan& other);
		TimeSpan& operator-=(const TimeSpan& other);

		template <typename T>
			requires std::is_arithmetic_v<T>
		TimeSpan operator*(T scalar) const;
		template <typename T>
			requires std::is_arithmetic_v<T>
		TimeSpan& operator*=(T scalar);
		template <typename T>
			requires std::is_arithmetic_v<T>
		friend TimeSpan operator*(T scalar, const TimeSpan& ts);

		template <typename T>
			requires std::is_arithmetic_v<T>
		TimeSpan operator/(T scalar) const;
		template <typename T>
			requires std::is_arithmetic_v<T>
		TimeSpan& operator/=(T scalar);

		// ----- Public API -----
	  public:
		double TotalDays() const;
		double TotalHours() const;
		double TotalMinutes() const;
		double TotalSeconds() const;
		double TotalMilliseconds() const;
		double TotalMicroseconds() const;
		int64_t TotalNanoseconds() const;

		TimeSpan Abs() const;

		std::chrono::duration<int64_t, std::nano> GetDuration() const;

		std::string ToString() const;
		std::string ToString_ISO8601() const;

		// ----- Private Members -----
	  private:
		std::chrono::duration<int64_t, std::nano> m_Duration{0};
	};

	// ----- Operator Implementations -----
	template <typename T>
		requires std::is_arithmetic_v<T>
	TimeSpan TimeSpan::operator*(T scalar) const
	{
		using Rep = int64_t;

		auto result = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::duration<long double, std::nano>(m_Duration.count()) * static_cast<long double>(scalar));

		return TimeSpan(static_cast<std::chrono::nanoseconds>(result));
	}

	template <typename T>
		requires std::is_arithmetic_v<T>
	TimeSpan& TimeSpan::operator*=(T scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	template <typename T>
		requires std::is_arithmetic_v<T>
	TimeSpan operator*(T scalar, const TimeSpan& ts)
	{
		return ts * scalar;
	}

	template <typename T>
		requires std::is_arithmetic_v<T>
	TimeSpan TimeSpan::operator/(T scalar) const
	{
		using namespace std::chrono;

		auto result = duration<long double, std::nano>(m_Duration.count()) / static_cast<long double>(scalar);
		return TimeSpan(duration_cast<nanoseconds>(result));
	}

	template <typename T>
		requires std::is_arithmetic_v<T>
	TimeSpan& TimeSpan::operator/=(T scalar)
	{
		*this = *this / scalar;
		return *this;
	}
} // namespace onion
