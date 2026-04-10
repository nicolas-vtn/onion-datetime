#include "TimeSpan.hpp"

#include <iomanip>
#include <sstream>

namespace onion
{
	// ---- CONSTEXPR ----
	constexpr int64_t NanosPerSecond = 1'000'000'000;
	constexpr int64_t NanosPerMinute = 60 * NanosPerSecond;
	constexpr int64_t NanosPerHour = 60 * NanosPerMinute;
	constexpr int64_t NanosPerDay = 24 * NanosPerHour;

	TimeSpan::TimeSpan(const std::chrono::duration<int64_t, std::nano>& duration) : m_Duration(duration) {}

	TimeSpan::TimeSpan(int64_t days,
					   int64_t hours,
					   int64_t minutes,
					   int64_t seconds,
					   int64_t milliseconds,
					   int64_t microseconds,
					   int64_t nanoseconds)
	{
		m_Duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::days(days) + std::chrono::hours(hours) + std::chrono::minutes(minutes) +
			std::chrono::seconds(seconds) + std::chrono::milliseconds(milliseconds) +
			std::chrono::microseconds(microseconds) + std::chrono::nanoseconds(nanoseconds));
	}

	TimeSpan TimeSpan::Zero()
	{
		return TimeSpan();
	}

	TimeSpan TimeSpan::FromDays(int64_t days)
	{
		return TimeSpan(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::days(days)));
	}

	TimeSpan TimeSpan::FromHours(int64_t hours)
	{
		return TimeSpan(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::hours(hours)));
	}

	TimeSpan TimeSpan::FromMinutes(int64_t minutes)
	{
		return TimeSpan(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::minutes(minutes)));
	}

	TimeSpan TimeSpan::FromSeconds(int64_t seconds)
	{
		return TimeSpan(std::chrono::seconds(seconds));
	}

	TimeSpan TimeSpan::FromMilliseconds(int64_t milliseconds)
	{
		return TimeSpan(std::chrono::milliseconds(milliseconds));
	}

	TimeSpan TimeSpan::FromMicroseconds(int64_t microseconds)
	{
		return TimeSpan(std::chrono::microseconds(microseconds));
	}

	TimeSpan TimeSpan::FromNanoseconds(int64_t nanoseconds)
	{
		return TimeSpan(std::chrono::nanoseconds(nanoseconds));
	}

	TimeSpan TimeSpan::MaxValue()
	{
		return TimeSpan(std::chrono::nanoseconds::max());
	}

	TimeSpan TimeSpan::MinValue()
	{
		return TimeSpan(std::chrono::nanoseconds::min());
	}

	TimeSpan TimeSpan::operator+(const TimeSpan& other) const
	{
		return TimeSpan(m_Duration + other.m_Duration);
	}

	TimeSpan TimeSpan::operator-(const TimeSpan& other) const
	{
		return TimeSpan(m_Duration - other.m_Duration);
	}

	TimeSpan& TimeSpan::operator+=(const TimeSpan& other)
	{
		m_Duration += other.m_Duration;
		return *this;
	}

	TimeSpan& TimeSpan::operator-=(const TimeSpan& other)
	{
		m_Duration -= other.m_Duration;
		return *this;
	}

	bool TimeSpan::operator<(const TimeSpan& other) const
	{
		return m_Duration < other.m_Duration;
	}

	bool TimeSpan::operator<=(const TimeSpan& other) const
	{
		return m_Duration <= other.m_Duration;
	}

	bool TimeSpan::operator>(const TimeSpan& other) const
	{
		return m_Duration > other.m_Duration;
	}

	bool TimeSpan::operator>=(const TimeSpan& other) const
	{
		return m_Duration >= other.m_Duration;
	}

	double TimeSpan::TotalDays() const
	{
		return std::chrono::duration<double, std::ratio<86400>>(m_Duration).count();
	}

	double TimeSpan::TotalHours() const
	{
		return std::chrono::duration<double, std::ratio<3600>>(m_Duration).count();
	}

	double TimeSpan::TotalMinutes() const
	{
		return std::chrono::duration<double, std::ratio<60>>(m_Duration).count();
	}

	double TimeSpan::TotalSeconds() const
	{
		return std::chrono::duration<double>(m_Duration).count();
	}

	double TimeSpan::TotalMilliseconds() const
	{
		return std::chrono::duration<double, std::milli>(m_Duration).count();
	}

	double TimeSpan::TotalMicroseconds() const
	{
		return std::chrono::duration<double, std::micro>(m_Duration).count();
	}

	int64_t TimeSpan::TotalNanoseconds() const
	{
		return m_Duration.count();
	}

	TimeSpan TimeSpan::Abs() const
	{
		if (m_Duration.count() < 0)
		{
			return TimeSpan(-m_Duration);
		}

		return *this;
	}

	std::chrono::duration<int64_t, std::nano> TimeSpan::GetDuration() const
	{
		return m_Duration;
	}

	std::string TimeSpan::ToString() const
	{
		using namespace std::chrono;

		int64_t totalNs = m_Duration.count();

		bool negative = totalNs < 0;
		if (negative)
			totalNs = -totalNs;

		int64_t days = totalNs / NanosPerDay;
		totalNs %= NanosPerDay;

		int64_t hours = totalNs / NanosPerHour;
		totalNs %= NanosPerHour;

		int64_t minutes = totalNs / NanosPerMinute;
		totalNs %= NanosPerMinute;

		int64_t seconds = totalNs / NanosPerSecond;
		totalNs %= NanosPerSecond;

		int64_t nanoseconds = totalNs;

		std::ostringstream oss;

		if (negative)
			oss << "-";

		if (days > 0)
			oss << days << ".";

		oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":"
			<< std::setw(2) << std::setfill('0') << seconds;

		if (nanoseconds > 0)
		{
			oss << "." << std::setw(9) << std::setfill('0') << nanoseconds;
		}

		return oss.str();
	}

	std::string TimeSpan::ToString_ISO8601() const
	{
		using namespace std::chrono;

		int64_t totalNs = m_Duration.count();

		if (totalNs == 0)
			return "PT0S";

		bool negative = totalNs < 0;
		if (negative)
			totalNs = -totalNs;

		int64_t days = totalNs / NanosPerDay;
		totalNs %= NanosPerDay;

		int64_t hours = totalNs / NanosPerHour;
		totalNs %= NanosPerHour;

		int64_t minutes = totalNs / NanosPerMinute;
		totalNs %= NanosPerMinute;

		int64_t seconds = totalNs / NanosPerSecond;
		totalNs %= NanosPerSecond;

		int64_t nanoseconds = totalNs;

		std::ostringstream oss;

		if (negative)
			oss << "-";

		oss << "P";

		if (days > 0)
			oss << days << "D";

		if (hours > 0 || minutes > 0 || seconds > 0 || nanoseconds > 0)
			oss << "T";

		if (hours > 0)
			oss << hours << "H";

		if (minutes > 0)
			oss << minutes << "M";

		if (seconds > 0 || nanoseconds > 0)
		{
			oss << seconds;

			if (nanoseconds > 0)
			{
				std::string frac = std::to_string(nanoseconds);
				frac.insert(frac.begin(), 9 - frac.length(), '0');

				// trim trailing zeros
				while (!frac.empty() && frac.back() == '0')
					frac.pop_back();

				if (!frac.empty())
					oss << "." << frac;
			}

			oss << "S";
		}

		return oss.str();
	}

} // namespace onion
