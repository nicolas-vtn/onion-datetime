#include <exception>
#include <format>
#include <iostream>
#include <stdexcept>
#include <cassert>

#include <onion/DateTime.hpp>

using namespace onion;

static bool TestDateTimeConstructors() {

	// Default constructor
	DateTime defaultDate{};

	// Parametrized constructor
	DateTime parametrizedDate(2020, 9, 11, 14, 5, 55);

	// Test OutOfRange input
	// Year out of range
	try {
		DateTime invalidDate(10998, 9, 11, 14, 5, 55);
		assert(false && "Expected out_of_range exception for year");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for year");
	}

	try {
		DateTime invalidDate(-1, 9, 11, 14, 5, 55);
		assert(false && "Expected out_of_range exception for year");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for year");
	}

	// Month out of range
	try {
		DateTime invalidDate(2020, 13, 11, 14, 5, 55);
		assert(false && "Expected out_of_range exception for month");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for month");
	}

	// Month out of range
	try {
		DateTime invalidDate(2020, 0, 11, 14, 5, 55);
		assert(false && "Expected out_of_range exception for month");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for month");
	}

	// Day out of range
	try {
		DateTime invalidDate(2020, 9, 35, 14, 5, 55);
		assert(false && "Expected out_of_range exception for day");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for day");
	}

	// Day out of range
	try {
		DateTime invalidDate(2020, 9, 0, 14, 5, 55);
		assert(false && "Expected out_of_range exception for day");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for day");
	}

	// Hour out of range
	try {
		DateTime invalidDate(2020, 9, 11, 24, 5, 55);
		assert(false && "Expected out_of_range exception for hour");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for hour");
	}

	// Hour out of range
	try {
		DateTime invalidDate(2020, 9, 11, -1, 5, 55);
		assert(false && "Expected out_of_range exception for hour");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for hour");
	}

	// Minute out of range
	try {
		DateTime invalidDate(2020, 9, 11, 14, 60, 55);
		assert(false && "Expected out_of_range exception for minute");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for minute");
	}

	// Minute out of range
	try {
		DateTime invalidDate(2020, 9, 11, 14, -1, 55);
		assert(false && "Expected out_of_range exception for minute");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for minute");
	}

	// Second out of range
	try {
		DateTime invalidDate(2020, 9, 11, 14, 5, 60);
		assert(false && "Expected out_of_range exception for second");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for second");
	}

	// Second out of range
	try {
		DateTime invalidDate(2020, 9, 11, 14, 5, -1);
		assert(false && "Expected out_of_range exception for second");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for second");
	}

	// Millisecond out of range
	try {
		DateTime invalidDate(2020, 9, 11, 14, 5, 55, 1000);
		assert(false && "Expected out_of_range exception for millisecond");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for millisecond");
	}

	// Millisecond out of range
	try {
		DateTime invalidDate(2020, 9, 11, 14, 5, 55, -1);
		assert(false && "Expected out_of_range exception for millisecond");
	}
	catch (const std::out_of_range& e) {
	}
	catch (...) {
		assert(false && "Expected out_of_range exception for millisecond");
	}

	// Test Invalid calendar date (e.g., February 30)
	try {
		DateTime invalidDate(2020, 2, 30, 14, 5, 55);
		assert(false && "Expected invalid_argument exception for calendar date");
	}
	catch (const std::invalid_argument& e) {
	}
	catch (...) {
		assert(false && "Expected invalid_argument exception for calendar date");
	}

	return true;
}

static bool TestDateTimeUtcNow() {
	// ToDo : Implement
	return true;
}

static bool TestDateTimeGetters() {
	DateTime dateTime(2020, 9, 11, 14, 5, 55, 123);
	assert(dateTime.getYear() == 2020 && "Expected year to be 2020");
	assert(dateTime.getMonth() == 9 && "Expected month to be 9");
	assert(dateTime.getDay() == 11 && "Expected day to be 11");
	assert(dateTime.getHours() == 14 && "Expected hour to be 14");
	assert(dateTime.getMinutes() == 5 && "Expected minute to be 5");
	assert(dateTime.getSeconds() == 55 && "Expected second to be 55");
	assert(dateTime.getMilliseconds() == 123 && "Expected millisecond to be 123");
	return true;
}

static bool TestAssignationOperator() {
	DateTime dt1(2020, 9, 11, 14, 5, 55);
	DateTime dt2 = dt1; // Copy assignment
	assert(dt1 == dt2 && "Expected dt1 to be equal to dt2 after copy assignment");
	return true;
}

static bool TestDateTimeComparisonOperators() {
	DateTime dt1(2020, 9, 11, 14, 5, 55);
	DateTime dt2(2020, 9, 11, 14, 5, 55);
	DateTime dt3(2020, 9, 11, 14, 6, 0);
	assert(dt1 == dt2 && "Expected dt1 to be equal to dt2");
	assert(dt1 != dt3 && "Expected dt1 to be not equal to dt3");
	assert(dt1 < dt3 && "Expected dt1 to be less than dt3");
	assert(dt3 > dt1 && "Expected dt3 to be greater than dt1");
	assert(dt1 <= dt2 && "Expected dt1 to be less than or equal to dt2");
	assert(dt3 >= dt2 && "Expected dt3 to be greater than or equal to dt2");
	return true;
}

static bool TestDateTimeToString() {
	DateTime dateTime(2020, 9, 11, 14, 5, 55, 123);
	std::string isoString = dateTime.toString();
	assert(isoString == "2020-09-11T14:05:55.123Z" && "Expected ISO string to be '2020-09-11T14:05:55.123Z'");
	std::string customFormat = dateTime.toString("%Y/%m/%d %H:%M:%S");
	assert(customFormat == "2020/09/11 14:05:55.123" && "Expected custom format string to be '2020/09/11 14:05:55.123'");
	return true;
}

static bool TestDateTimeUnixTimestamp() {
	DateTime dateTime(2020, 9, 11, 14, 5, 55);
	long long unixTimestamp = dateTime.toUnixTimestamp();
	assert(unixTimestamp == 1599833155 && "Expected Unix timestamp for 2020-09-11T14:05:55Z to be 1599833155");
	return true;
}

int main()
{
	bool constructorsTestPassed = TestDateTimeConstructors();
	if (constructorsTestPassed) {
		std::cout << "TestDateTimeConstructors passed." << std::endl;
	}
	else {
		assert(false && "TestDateTimeConstructors failed.");
	}

	bool utcNowTestPassed = TestDateTimeUtcNow();
	if (utcNowTestPassed) {
		std::cout << "TestDateTimeUtcNow passed." << std::endl;
	}
	else {
		assert(false && "TestDateTimeUtcNow failed.");
	}

	bool gettersTestPassed = TestDateTimeGetters();
	if (gettersTestPassed) {
		std::cout << "TestDateTimeGetters passed." << std::endl;
	}
	else {
		assert(false && "TestDateTimeGetters failed.");
	}

	bool assignationOperatorTestPassed = TestAssignationOperator();
	if (assignationOperatorTestPassed) {
		std::cout << "TestAssignationOperator passed." << std::endl;
	}
	else {
		assert(false && "TestAssignationOperator failed.");
	}

	bool comparisonOperatorsTestPassed = TestDateTimeComparisonOperators();
	if (comparisonOperatorsTestPassed) {
		std::cout << "TestDateTimeComparisonOperators passed." << std::endl;
	}
	else {
		assert(false && "TestDateTimeComparisonOperators failed.");
	}

	bool toStringTestPassed = TestDateTimeToString();
	if (toStringTestPassed) {
		std::cout << "TestDateTimeToString passed." << std::endl;
	}
	else {
		assert(false && "TestDateTimeToString failed.");
	}

	bool unixTimestampTestPassed = TestDateTimeUnixTimestamp();
	if (unixTimestampTestPassed) {
		std::cout << "TestDateTimeUnixTimestamp passed." << std::endl;
	}
	else {
		assert(false && "TestDateTimeUnixTimestamp failed.");
	}

	std::cout << "\n\nAll tests passed successfully !!" << std::endl;

	return 0;
}
