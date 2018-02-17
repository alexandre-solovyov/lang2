
#ifndef TESTS_H
#define TESTS_H

#include <gtest/gtest.h>
#include <model/Tools.h>
#include <QString>

#define ASSERT_EQQ( actual, expected )                                    \
    {                                                                     \
        QString tmp_actual = (actual);                                    \
        QString tmp_expected = (expected);                                \
        if( tmp_actual != tmp_expected )                                  \
        {                                                                 \
            GTEST_NONFATAL_FAILURE_("Strings are different:");            \
            Tools::print( "  Actual: " + tmp_actual );                    \
            Tools::print( "  Expected: " + tmp_expected );                \
        }                                                                 \
    }                                                                     \

#endif
