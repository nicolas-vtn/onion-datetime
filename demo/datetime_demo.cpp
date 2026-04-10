#include <exception>
#include <format>
#include <iostream>

#include <onion/DateTime.hpp>

using namespace onion;

int main()
{

	std::cout << "------------- DATE TIME DEMO -------------\n" << std::endl;

	std::cout << "\nDemo default constructor (current UTC time):" << std::endl;
	DateTime dateTimeNow;
	std::cout << "Current UTC DateTime: " << dateTimeNow.toString() << std::endl;

	std::cout << "\nDemo UtcNow() static method:" << std::endl;
	DateTime utcNow = DateTime::UtcNow();
	std::cout << "UtcNow: " << utcNow.toString() << std::endl;

	std::cout << "\nDemo parameterized constructor with valid date and time:" << std::endl;
	DateTime specificDateTime(2024, 6, 15, 12, 30, 45, 500);
	std::cout << "Specific DateTime: " << specificDateTime.toString() << std::endl;

	std::cout << "\nDemo parameterized constructor with invalid date (February 30):" << std::endl;
	try
	{
		DateTime invalidDateTime(2024, 2, 30, 10, 0, 0);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Expected error for invalid date: " << ex.what() << std::endl;
	}

	std::cout << "\nDemo parameterized constructor with invalid time (25 hours):" << std::endl;
	try
	{
		DateTime invalidTimeDateTime(2024, 6, 15, 25, 0, 0);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Expected error for invalid time: " << ex.what() << std::endl;
	}

	std::cout << "\nDemo comparison operators:" << std::endl;
	DateTime dt1(2024, 6, 15, 12, 30, 45);
	DateTime dt2(2024, 6, 15, 12, 30, 45);
	DateTime dt3(2024, 6, 15, 13, 0, 0);

	std::cout << "dt1: " << dt1.toString() << std::endl;
	std::cout << "dt2: " << dt2.toString() << std::endl;
	std::cout << "dt3: " << dt3.toString() << std::endl;

	std::cout << "dt1 == dt2: " << (dt1 == dt2) << std::endl;
	std::cout << "dt1 != dt3: " << (dt1 != dt3) << std::endl;
	std::cout << "dt1 < dt3: " << (dt1 < dt3) << std::endl;
	std::cout << "dt3 > dt2: " << (dt3 > dt2) << std::endl;

	std::cout << "\nDemo toStringg() formating:" << std::endl;
	std::cout << "ISO 8601 format: " << dateTimeNow.toString() << std::endl;
	std::cout << "Custom format (\"%Y-%m-%d %H:%M:%S\"): " << dateTimeNow.toString("%Y-%m-%d %H:%M:%S") << std::endl;

	std::cout << "\nDemo toUnixTimestamp():" << std::endl;
	std::cout << "Current UTC DateTime: " << dateTimeNow.toString() << std::endl;
	std::cout << "Unix Timestamp: " << dateTimeNow.toUnixTimestamp() << std::endl;

	std::cout << "\nDemo std::format support:" << std::endl;
	std::cout << std::format("Formatted DateTime (\"%Y-%m-%d %H:%M:%S\"): {}", dateTimeNow) << std::endl;

	std::cout << "\nDemo DateTime <-> TimeSpan operators:" << std::endl;

	DateTime start(2024, 6, 15, 12, 0, 0);
	DateTime end(2024, 6, 16, 14, 30, 15, 250);

	std::cout << "Start: " << start.toString() << std::endl;
	std::cout << "End  : " << end.toString() << std::endl;

	// Difference
	TimeSpan diff = end - start;
	std::cout << "End - Start = " << diff.ToString() << std::endl;

	// Add TimeSpan
	DateTime added = start + diff;
	std::cout << "Start + diff = " << added.toString() << std::endl;

	// Subtract TimeSpan
	DateTime subtracted = end - diff;
	std::cout << "End - diff = " << subtracted.toString() << std::endl;

	std::cout << "\n\n\n";

	std::cout << "\n------------- TIMESPAN DEMO -------------\n" << std::endl;

	// Construction
	TimeSpan ts1 = TimeSpan::FromDays(1);
	TimeSpan ts2 = TimeSpan::FromHours(2);
	TimeSpan ts3 = TimeSpan::FromMinutes(30);
	TimeSpan ts4 = TimeSpan::FromSeconds(45);
	TimeSpan ts5 = TimeSpan::FromMilliseconds(500);
	TimeSpan ts6 = TimeSpan::FromMicroseconds(250);
	TimeSpan ts7 = TimeSpan::FromNanoseconds(100);

	TimeSpan combined = ts1 + ts2 + ts3 + ts4 + ts5 + ts6 + ts7;

	std::cout << "Combined TimeSpan: " << combined.ToString() << std::endl;

	std::cout << "\nTotal values:" << std::endl;
	std::cout << "Days         : " << combined.TotalDays() << std::endl;
	std::cout << "Hours        : " << combined.TotalHours() << std::endl;
	std::cout << "Minutes      : " << combined.TotalMinutes() << std::endl;
	std::cout << "Seconds      : " << combined.TotalSeconds() << std::endl;
	std::cout << "Milliseconds : " << combined.TotalMilliseconds() << std::endl;
	std::cout << "Microseconds : " << combined.TotalMicroseconds() << std::endl;
	std::cout << "Nanoseconds  : " << combined.TotalNanoseconds() << std::endl;

	std::cout << "\nArithmetic operators:" << std::endl;

	TimeSpan a = TimeSpan::FromHours(2);
	TimeSpan b = TimeSpan::FromMinutes(30);

	std::cout << "a: " << a.ToString() << std::endl;
	std::cout << "b: " << b.ToString() << std::endl;

	TimeSpan sum = a + b;
	TimeSpan diffTs = a - b;

	std::cout << "a + b: " << sum.ToString() << std::endl;
	std::cout << "a - b: " << diffTs.ToString() << std::endl;

	std::cout << "\nScalar operations:" << std::endl;

	TimeSpan base = TimeSpan::FromMinutes(10);

	TimeSpan mulInt = base * 3;
	TimeSpan mulDouble = base * 1.5;
	TimeSpan div = base / 2;

	std::cout << "Base: " << base.ToString() << std::endl;
	std::cout << "Base * 3   : " << mulInt.ToString() << std::endl;
	std::cout << "Base * 1.5 : " << mulDouble.ToString() << std::endl;
	std::cout << "Base / 2   : " << div.ToString() << std::endl;

	std::cout << "\nComparison operators (detailed):" << std::endl;

	std::cout << std::boolalpha;

	// Define values
	TimeSpan c1 = TimeSpan::FromSeconds(60);  // 00:01:00
	TimeSpan c2 = TimeSpan::FromMinutes(1);	  // 00:01:00
	TimeSpan c3 = TimeSpan::FromSeconds(120); // 00:02:00
	TimeSpan c4 = TimeSpan::FromSeconds(30);  // 00:00:30

	// Print values
	std::cout << "c1: " << c1.ToString() << std::endl;
	std::cout << "c2: " << c2.ToString() << std::endl;
	std::cout << "c3: " << c3.ToString() << std::endl;
	std::cout << "c4: " << c4.ToString() << std::endl;

	// Equality
	std::cout << "\nEquality:" << std::endl;
	std::cout << "c1 == c2: " << (c1 == c2) << std::endl; // true
	std::cout << "c1 == c3: " << (c1 == c3) << std::endl; // false

	// Inequality
	std::cout << "\nInequality:" << std::endl;
	std::cout << "c1 != c3: " << (c1 != c3) << std::endl; // true
	std::cout << "c1 != c2: " << (c1 != c2) << std::endl; // false

	// Less / Greater
	std::cout << "\nOrdering:" << std::endl;
	std::cout << "c1 < c3 : " << (c1 < c3) << std::endl; // true
	std::cout << "c3 < c1 : " << (c3 < c1) << std::endl; // false

	std::cout << "c3 > c2 : " << (c3 > c2) << std::endl; // true
	std::cout << "c4 > c1 : " << (c4 > c1) << std::endl; // false

	// Less / Greater or equal
	std::cout << "\nInclusive comparisons:" << std::endl;
	std::cout << "c1 <= c2: " << (c1 <= c2) << std::endl; // true
	std::cout << "c1 >= c2: " << (c1 >= c2) << std::endl; // true
	std::cout << "c4 <= c1: " << (c4 <= c1) << std::endl; // true
	std::cout << "c3 >= c1: " << (c3 >= c1) << std::endl; // true

	std::cout << "\nNegative TimeSpan:" << std::endl;

	TimeSpan neg = TimeSpan::FromMinutes(-90);
	std::cout << "Negative: " << neg.ToString() << std::endl;

	std::cout << "\n\n\n";
	return 0;
}
