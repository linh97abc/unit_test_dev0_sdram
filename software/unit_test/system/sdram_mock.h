/******************************************************************************
 * Copyright (c) 2020 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

#ifndef INC_SYSTEM_SDRAM_MOCK_H
#define INC_SYSTEM_SDRAM_MOCK_H

// Standard headers
#include <memory>
#include <vector>

// Mock headers
#include "alt_types_mock.h"
#include "memory_mock.h"

/**
 * A template for a generic memory mock, which uses a vector as underlying data structure.
 */
template <unsigned BASE, unsigned SPAN>
class SDRAM_MOCK : public MEMORY_MOCK_IF
{
public:
    SDRAM_MOCK() : m_base_addr(BASE), m_span(SPAN) { m_memory.resize(SPAN / 4); }
    virtual ~SDRAM_MOCK() {}
    alt_u32 get_mem_word(void* addr) override
    {
        std::uintptr_t addr_int = reinterpret_cast<std::uintptr_t>(addr);
        std::uintptr_t regNum = (addr_int - BASE) / 4;

        if(m_error && (regNum == m_regError))
        {
            return 0;
        }

        return m_memory[regNum];
    }
    void set_mem_word(void* addr, alt_u32 data) override
    {
        std::uintptr_t addr_int = reinterpret_cast<std::uintptr_t>(addr);
        std::uintptr_t regNum = (addr_int - BASE) / 4;

        if(!m_error || (addr_int != m_regError))
        {
            m_memory[regNum] = data;
        }
        else
        {
            m_memory[regNum] = 0;
        }
        
    }
    void reset() override
    {
        for (auto& elem : m_memory)
        {
            elem = 0;
        }
    }
    bool is_addr_in_range(void* addr) override
    {
        return MEMORY_MOCK_IF::is_addr_in_range(addr, (alt_u32*) BASE, SPAN);
    }

    void setErrorMock(bool set, std::uintptr_t addr = BASE)
    {
        m_error = set;
        m_regError = (addr - BASE) / 4;
    }


private:
    std::vector<alt_u32> m_memory;
    alt_u32 m_base_addr;
    alt_u32 m_span;
    std::uintptr_t m_regError;
    bool m_error;
};

#endif /* INC_SYSTEM_SDRAM_MOCK_H */
