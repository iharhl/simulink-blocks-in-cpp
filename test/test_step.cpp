#include "gtest/gtest.h"
#include <vector>
#include "sources.h"

TEST(StepBlockOutput, TypeInteger)
{
    // arange
    unsigned num_of_samples = 10;
    int init_value = -1;
    int final_value = 2;
    unsigned step_sample = 4;
    std::vector<int> expected_vec = {-1,-1,-1,2,2,2,2,2,2,2};

    // act
    std::vector<int> returned_vec = SimuBlocks::Step(num_of_samples, init_value, final_value, step_sample);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_EQ(expected_vec[i], returned_vec[i]);
    }

}

TEST(StepBlockOutput, TypeFloat)
{
    // arange
    unsigned num_of_samples = 10;
    float init_value = 1.0f;
    float final_value = 5.0f;
    unsigned step_sample = 5;
    std::vector<float> expected_vec = {1.f,1.f,1.f,1.f,5.f,5.f,5.f,5.f,5.f,5.f};

    // act
    std::vector<float> returned_vec = SimuBlocks::Step(num_of_samples, init_value, final_value, step_sample);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_FLOAT_EQ(expected_vec[i], returned_vec[i]);
    }

}

TEST(StepBlockOutput, TypeSizet)
{
    // arange
    unsigned num_of_samples = 7;
    size_t init_value = 999991;
    size_t final_value = 9999999;
    unsigned step_sample = 2;
    std::vector<size_t> expected_vec = {999991,9999999,9999999,9999999,9999999,9999999,9999999};

    // act
    std::vector<size_t> returned_vec = SimuBlocks::Step(num_of_samples, init_value, final_value, step_sample);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_EQ(expected_vec[i], returned_vec[i]);
    }

}

TEST(StepBlockOutput, TypeUint8)
{
    // arange
    unsigned num_of_samples = 5;
    std::uint8_t init_value = 0;
    std::uint8_t final_value = 255;
    unsigned step_sample = 1;
    std::vector<std::uint8_t> expected_vec = {255,255,255,255,255};

    // act
    std::vector<std::uint8_t> returned_vec = SimuBlocks::Step(num_of_samples, init_value, final_value, step_sample);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_EQ(expected_vec[i], returned_vec[i]);
    }

}

TEST(PulseGeneratorBlockOutput, TypeInt)
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

TEST(PulseGeneratorBlockOutput, TypeFloat)
{
    // arange
    unsigned num_of_samples = 10;
    float amplitude = 4.1f;
    unsigned period = 6;
    unsigned duty_cycle = 50;
    unsigned phase_delay = 2;
    std::vector<float> expected_vec = {0.f,0.f,4.1f,4.1f,4.1f,0.f,0.f,0.f,4.1f,4.1f};

    // act
    std::vector<float> returned_vec = SimuBlocks::PulseGenerator(num_of_samples, amplitude, period, duty_cycle, phase_delay);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_FLOAT_EQ(expected_vec[i], returned_vec[i]);
    }    

}

TEST(RampBlockOutput, TypeInt)
{
    // arange
    unsigned num_of_samples = 7;
    float sloap = 4.3f;
    unsigned start_ramp = 3;
    int init_output = 1;
    std::vector<int> expected_vec = {1,1,5,9,13,17,21};

    // act
    std::vector<int> returned_vec = SimuBlocks::Ramp(num_of_samples, sloap, start_ramp, init_output);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_EQ(expected_vec[i], returned_vec[i]);
    }    

}

TEST(RampBlockOutput, TypeFloat)
{
    // arange
    unsigned num_of_samples = 4;
    float sloap = 4.3f;
    unsigned start_ramp = 1;
    float init_output = 0.5f;
    std::vector<float> expected_vec = {0.5f, 4.8f, 9.1f, 13.4f};

    // act
    std::vector<float> returned_vec = SimuBlocks::Ramp(num_of_samples, sloap, start_ramp, init_output);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_FLOAT_EQ(expected_vec[i], returned_vec[i]);
    }    

}

TEST(ConstantBlockOutput, TypeInt)
{
    // arange
    unsigned num_of_samples = 11;
    int const_value = 15;
    std::vector<int> expected_vec = {15,15,15,15,15,15,15,15,15,15,15};

    // act
    std::vector<int> returned_vec = SimuBlocks::Constant(num_of_samples, const_value);

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