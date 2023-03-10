#include "gtest/gtest.h"
#include <vector>
#include "sources.h"
#include <iostream>

TEST(StepBlock, TypeIntSuccess)
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

TEST(StepBlockOutput, TypeFloatSuccess)
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

TEST(StepBlock, TypeSizetSuccess)
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

TEST(StepBlock, TypeUint8Success)
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

TEST(PulseGeneratorBlockOutput, TypeIntSuccess)
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

TEST(PulseGeneratorBlock, TypeFloatSuccess)
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

TEST(RampBlock, TypeIntSuccess)
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

TEST(RampBlockOut, TypeFloatSuccess)
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

TEST(ConstantBlock, TypeIntSuccess)
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

TEST(ConstantBlock, TypeFloatSuccess)
{
    // arange
    unsigned num_of_samples = 3;
    float const_value = 34.43f;
    std::vector<float> expected_vec = {34.43f,34.43f,34.43f};

    // act
    std::vector<float> returned_vec = SimuBlocks::Constant(num_of_samples, const_value);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_EQ(expected_vec[i], returned_vec[i]);
    }    
}

TEST(SineWaveBlock, TypeFloatSuccess)
{
    // arange
    unsigned num_of_samples = 15;
    float amplitude = 2.1f;
    unsigned samples_per_period = 12;
    std::vector<float> expected_vec = {0.f,1.13534f,1.91022f,2.07862f,1.58707f,0.59163f,-0.59163f,-1.58707f,-2.07862f,-1.91022f,-1.13534f,0.f,1.13534f,1.91022f,2.07862f};

    // act
    std::vector<float> returned_vec = SimuBlocks::SineWave(num_of_samples, amplitude, samples_per_period);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_NEAR(expected_vec[i], returned_vec[i], 0.00002);
    } 
}

TEST(SineWaveBlock, ThrowFailure)
{
    // arange
    unsigned num_of_samples = 12;
    float amplitude = 2.1f;
    unsigned samples_per_period = 0;

    // act and assert
    ASSERT_THROW(SimuBlocks::SineWave(num_of_samples, amplitude, samples_per_period), std::invalid_argument);
}

TEST(RandomNumberBlock, TypeFloatSuccess)
{
    // arange
    unsigned num_of_samples = 6;
    float min_limit = 0;
    float max_limit = 2;

    // act
    std::vector<float> returned_vec = SimuBlocks::RandomNumber(num_of_samples, min_limit, max_limit);

    // compare
    for (int i = 0; i < num_of_samples; ++i)
    {
        ASSERT_LE(returned_vec[i], max_limit);
        ASSERT_GE(returned_vec[i], min_limit);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); 
}