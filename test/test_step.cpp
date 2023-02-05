#include "gtest/gtest.h"
#include <vector>
#include "sources.h"

TEST(TestStep, DummyTest1)
{
    // arange
    int num_of_samples = 10;
    int init_value = 0;
    int final_value = 2;
    int step_sample = 4;
    std::vector<int> expected_vec = {0,0,0,0,2,2,2,2,2,2};

    // act
    std::vector<int> returned_vec = SimuBlocks::Step(num_of_samples, init_value, final_value, step_sample);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_EQ(expected_vec[i], returned_vec[i]);
    }

}

TEST(TestPulse, DummyTest2)
{
    // arange
    unsigned num_of_samples = 10;
    int amplitude = 4;
    unsigned period = 6;
    unsigned duty_cycle = 50;
    std::vector<int> expected_vec = {4,4,4,0,0,0,4,4,4,0};

    // act
    std::vector<int> returned_vec = SimuBlocks::PulseGenerator(num_of_samples, amplitude, period, duty_cycle);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_EQ(expected_vec[i], returned_vec[i]);
    }    

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); 
}