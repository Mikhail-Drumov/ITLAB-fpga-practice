#include <gtest/gtest.h>
#include <memory>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vcalculator_program.h"

class SeqArithTest : public ::testing::Test {
protected:
    std::unique_ptr<Vcalculator_program> dut;
    std::unique_ptr<VerilatedVcdC> trace;
    vluint64_t sim_time;

    void SetUp() override {
        Verilated::traceEverOn(true);
        dut = std::make_unique<Vcalculator_program>();
        trace = std::make_unique<VerilatedVcdC>();
        dut->trace(trace.get(), 99);
        
        const ::testing::TestInfo* const test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        std::string vcd_name = std::string("dump_") + test_info->name() + ".vcd";
        trace->open(vcd_name.c_str());
        sim_time = 0;
    }

    void TearDown() override {
        trace->close();
    }

    void tick() {
        dut->clk = 0;
		dut->eval();
		trace->dump(sim_time++);
        
		dut->clk = 1;
		dut->eval();
		trace->dump(sim_time++);
    }

    void press_key(int id) {
        dut->KEY &= ~(1 << id); // Нажали
        tick();
        dut->KEY |= (1 << id);  // Отпустили
        tick();
    }
};

TEST_F(SeqArithTest, FullScenario) {
    dut->rst = 1;
    dut->clk = 0;
    dut->KEY = 0xF;
    dut->SW = 0;
    
    for (int i = 0; i < 5; i++) tick();
    dut->rst = 0;
    tick();

    for (int i = 0; i < 16; i++) {
        dut->SW = (dut->SW & ~0xF) | (i & 0xF);
        press_key(0);
        EXPECT_EQ((dut->LEDR & 0xF), (i & 0xF));

        for (int j = 0; j < 16; j++) {
            dut->SW = (dut->SW & ~0xF) | (j & 0xF);
            press_key(1);
            EXPECT_EQ(((dut->LEDR >> 4) & 0xF), (j & 0xF));

            // Addition
            press_key(2);
            EXPECT_EQ((dut->LEDG & 0xF), ((i + j) & 0xF));

            // Subtraction
            press_key(3);
            EXPECT_EQ((dut->LEDG & 0xF), ((i - j) & 0xF));
        }
    }
}