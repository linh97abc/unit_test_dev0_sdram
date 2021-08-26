#include <iostream>
#include "ut_nios_wrapper.h"
#include "io.h"
#include <stdio.h>
#include "mem_verify.h"
#include "sdram_mock.h"
using namespace std;

SYSTEM_MOCK *mock;

bool test_TMEM_Verify(void)
{
    auto ip_mock = (SDRAM_MOCK<SDRAM_BASE, SDRAM_SPAN> *)mock->get_ip_mock(SDRAM_BASE).get();

    ip_mock->setErrorMock(false);

    return TMEM_Verify(SDRAM_BASE, SDRAM_SPAN, 1, true);
}

bool test_TMEM_QuickVerify(void)
{
    auto ip_mock = (SDRAM_MOCK<SDRAM_BASE, SDRAM_SPAN> *)mock->get_ip_mock(SDRAM_BASE).get();

    ip_mock->setErrorMock(false);

    return TMEM_QuickVerify(SDRAM_BASE, SDRAM_SPAN, SDRAM_SDRAM_DATA_WIDTH, SDRAM_SDRAM_ADDR_WIDTH);
}

bool test_TMEM_Verify_SDRAM_error(void)
{
    auto ip_mock = (SDRAM_MOCK<SDRAM_BASE, SDRAM_SPAN> *)mock->get_ip_mock(SDRAM_BASE).get();

    ip_mock->setErrorMock(true, 1);

    return !TMEM_Verify(SDRAM_BASE, SDRAM_SPAN, 1, true);
}

bool test_TMEM_QuickVerifySDRAM_error(void)
{
    auto ip_mock = (SDRAM_MOCK<SDRAM_BASE, SDRAM_SPAN> *)mock->get_ip_mock(SDRAM_BASE).get();

    ip_mock->setErrorMock(true, 1);

    return !TMEM_QuickVerify(SDRAM_BASE, SDRAM_SPAN, SDRAM_SDRAM_DATA_WIDTH, SDRAM_SDRAM_ADDR_WIDTH);
}

void run_test(const char *test_name, bool (*test_fn)(void))
{
    bool bPass;
    cout << "================================================" << endl;
    cout << "starting test - " << test_name << endl;
    try
    {
        bPass = test_fn();
    }
    catch (int e)
    {
        bPass = false;
    }

    cout << (bPass ? "Pass - " : "FAILED - ") << test_name << endl;
}

#define RUN_TEST(test_name) run_test(#test_name, test_name)

int main(int argc, char **argv)
{
    mock = SYSTEM_MOCK::get();
    mock->reset();
    mock->set_assert_to_throw();
    cout << "Starting Unit test EXE " << argv[0] << endl;

    RUN_TEST(test_TMEM_Verify);
    RUN_TEST(test_TMEM_QuickVerify);
    RUN_TEST(test_TMEM_Verify_SDRAM_error);
    RUN_TEST(test_TMEM_QuickVerifySDRAM_error);

    return 0;
}
