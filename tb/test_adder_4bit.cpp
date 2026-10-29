#include <gtest/gtest.h>
#include <memory>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vadder_4bit.h"

class AdderTest : public ::testing::Test {
protected:
    std::unique_ptr<Vadder_4bit> dut;
    std::unique_ptr<VerilatedVcdC> trace;
    vluint64_t sim_time;

    void SetUp() override {
        dut = std::make_unique<Vadder_4bit>();
        trace = std::make_unique<VerilatedVcdC>();
        Verilated::traceEverOn(true);
        
        // Название VCD-дампа зависит от имени текущего теста
        const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        std::string vcd_name = std::string("dump_") + test_info->name() + ".vcd";
        
        dut->trace(trace.get(), 99);
        trace->open(vcd_name.c_str());
        
        sim_time = 0;
    }

    void TearDown() override {
        trace->close();
    }

    // Вспомогательный метод для симуляции одного такта (clock cycle)
    void tick() {
		dut->eval();
        trace->dump(sim_time++);
    }
};

TEST_F(AdderTest, Adding) {
	int A, B, expected;
	
	for (A = 0; A < 16; A++) {
		for (B = 0; B < 16; B++) {
			dut->A = A;
			dut->B = B;
			dut->cin = 0;
			
			tick();
			
			expected = (A + B) & 0xF;
			EXPECT_EQ(dut->S, expected) << "Failed at A=" << A << ", B=" << B <<
				"; S=" << dut->S << ", but expected S=" << expected << "\n";
		}
	}
}
