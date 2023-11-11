#define BOOST_TEST_MODULE IntegerTests
#include <boost/test/unit_test.hpp>

#include <IntegerLib/H/Integer.h>


BOOST_AUTO_TEST_CASE(integer_add_01) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    std::string r = "20000000000000000000000000000000";
    BOOST_CHECK_EQUAL(r, a.Add(b).ToString());
}

BOOST_AUTO_TEST_CASE(integer_add_02) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("-10000000000000000000000000000000");
    std::string r = "0";
    BOOST_CHECK_EQUAL(r, a.Add(b).ToString());
}

BOOST_AUTO_TEST_CASE(integer_add_03) {
    big::Integer a("-10000000000000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    big::Integer r;
    BOOST_CHECK(r.IsEq(a.Add(b)));
}

BOOST_AUTO_TEST_CASE(integer_gt_01) {
    big::Integer a("-10000000000000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(false, a.IsGT(b));
}

BOOST_AUTO_TEST_CASE(integer_gt_02) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("-10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(true, a.IsGT(b));
}

BOOST_AUTO_TEST_CASE(integer_gt_03) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("-1000000000000000000000");
    BOOST_CHECK_EQUAL(true, a.IsGT(b));
}

BOOST_AUTO_TEST_CASE(integer_gt_04) {
    big::Integer a("-1000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(false, a.IsGT(b));
}

BOOST_AUTO_TEST_CASE(integer_gte_01) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(true, a.IsGTE(b));
}

BOOST_AUTO_TEST_CASE(integer_gte_02) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("-10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(true, a.IsGTE(b));
}

BOOST_AUTO_TEST_CASE(integer_lt_01) {
    big::Integer a("-10000000000000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(true, a.IsLT(b));
}

BOOST_AUTO_TEST_CASE(integer_lt_02) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("-10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(false, a.IsLT(b));
}

BOOST_AUTO_TEST_CASE(integer_lt_03) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("-1000000000000000000000");
    BOOST_CHECK_EQUAL(false, a.IsLT(b));
}

BOOST_AUTO_TEST_CASE(integer_lt_04) {
    big::Integer a("-1000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(true, a.IsLT(b));
}

BOOST_AUTO_TEST_CASE(integer_lte_01) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(true, a.IsLTE(b));
}

BOOST_AUTO_TEST_CASE(integer_lte_02) {
    big::Integer a("10000000000000000000000000000000");
    big::Integer b("-10000000000000000000000000000000");
    BOOST_CHECK_EQUAL(false, a.IsLTE(b));
}

BOOST_AUTO_TEST_CASE(integer_eq_01) {
    big::Integer a("0");
    big::Integer b("-0");
    BOOST_CHECK_EQUAL(true, a.IsEq(b));
}
