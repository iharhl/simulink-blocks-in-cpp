#include "gtest/gtest.h"
#include <vector>
#include "sources.h"
#include "Constant.h"
#include "PulseGenerator.h"
#include "SineWave.h"
#include "Step.h"
#include "Ramp.h"
#include <iostream>

TEST(StepBlock, TypeUint8)
{
    // Arange
    const std::uint8_t InitValue = 0;
    const std::uint8_t FinalValue = 120;
    const unsigned StepSample = 3;

    std::array<std::uint8_t, 10> ExpectedOutput = {0,0,120,120,120,120,120,120,120,120};
    std::array<std::uint8_t, 10> ActualOutput;

    SimuBlocks::Step StepBlock(InitValue, FinalValue, StepSample);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        StepBlock.Tick();
        ActualOutput[i] = StepBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(StepBlock, TypeFloat)
{
    // Arange
    const float InitValue = 1.f;
    const float FinalValue = 5.f;
    const unsigned StepSample = 5;

    std::array<float, 10> ExpectedOutput = {1.f,1.f,1.f,1.f,5.f,5.f,5.f,5.f,5.f,5.f};
    std::array<float, 10> ActualOutput;

    SimuBlocks::Step StepBlock(InitValue, FinalValue, StepSample);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        StepBlock.Tick();
        ActualOutput[i] = StepBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_FLOAT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(PulseGeneratorBlock, TypeUint8)
{
    // Arange
    const std::uint8_t Amplitude = 18;
    const unsigned Period = 4;
    const unsigned DutyCycle = 25;
    const unsigned PhaseDelay = 0;

    std::array<std::uint8_t, 10> ExpectedOutput = {18,0,0,0,18,0,0,0,18,0};
    std::array<std::uint8_t, 10> ActualOutput;

    SimuBlocks::PulseGenerator PulseGeneratorBlock(Amplitude, Period, DutyCycle, PhaseDelay);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        PulseGeneratorBlock.Tick();
        ActualOutput[i] = PulseGeneratorBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(PulseGeneratorBlock, TypeFloat)
{
    // Arange
    const float Amplitude = 4.1f;
    const unsigned Period = 6;
    const unsigned DutyCycle = 50;
    const unsigned PhaseDelay = 2;

    std::array<float, 10> ExpectedOutput = {0.f,0.f,4.1f,4.1f,4.1f,0.f,0.f,0.f,4.1f,4.1f};
    std::array<float, 10> ActualOutput;

    SimuBlocks::PulseGenerator PulseGeneratorBlock(Amplitude, Period, DutyCycle, PhaseDelay);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        PulseGeneratorBlock.Tick();
        ActualOutput[i] = PulseGeneratorBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_FLOAT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

// TEST(RampBlock, TypeInt)
// {
//     // arange
//     unsigned num_of_samples = 7;
//     float sloap = 4.3f;
//     unsigned start_ramp = 3;
//     int init_output = 1;
//     std::vector<int> expected_vec = {1,1,5,9,13,17,21};

//     // act
//     std::vector<int> returned_vec = SimuBlocks::Ramp(num_of_samples, sloap, start_ramp, init_output);

//     // compare
//     for (int i = 0; i < num_of_samples; ++i)
//     {
//         ASSERT_EQ(expected_vec[i], returned_vec[i]);
//     }    
// }

TEST(RampBlock, TypeUint8)
{
    // Arange
    const std::uint8_t Sloap = 7;
    const unsigned StartRampSample = 3;
    const std::uint8_t InitialOutput = 1;

    std::array<std::uint8_t, 5> ExpectedOutput = {1,1,8,15,22};
    std::array<std::uint8_t, 5> ActualOutput;

    SimuBlocks::Ramp RampBlock(Sloap, StartRampSample, InitialOutput);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        RampBlock.Tick();
        ActualOutput[i] = RampBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_FLOAT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(RampBlock, TypeFloat)
{
    // Arange
    const float Sloap = 4.3f;
    const unsigned StartRampSample = 1;
    const float InitialOutput = 0.5f;

    std::array<float, 4> ExpectedOutput = {0.5f, 4.8f, 9.1f, 13.4f};
    std::array<float, 4> ActualOutput;

    SimuBlocks::Ramp RampBlock(Sloap, StartRampSample, InitialOutput);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        RampBlock.Tick();
        ActualOutput[i] = RampBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_FLOAT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(ConstBlock, TypeInt)
{
    // Arange
    const std::uint8_t ConstValue = 15;

    std::array<std::uint8_t, 5> ExpectedOutput = {15,15,15,15,15};
    std::array<std::uint8_t, 5> ActualOutput;

    SimuBlocks::Constant ConstBlock(ConstValue);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        ActualOutput[i] = ConstBlock.GetOutput();
        ConstBlock.Tick();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(ConstBlock, TypeFloat)
{
    // Arange
    const float ConstValue = 34.43f;

    std::array<float, 5> ExpectedOutput = {34.43f,34.43f,34.43f,34.43f,34.43f};
    std::array<float, 5> ActualOutput;

    SimuBlocks::Constant ConstBlock(ConstValue);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        ActualOutput[i] = ConstBlock.GetOutput();
        ConstBlock.Tick();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_FLOAT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

// TEST(SineWaveBlock, TypeFloatSuccess)
// {
//     // arange
//     unsigned num_of_samples = 15;
//     float amplitude = 2.1f;
//     unsigned samples_per_period = 12;
//     std::vector<float> expected_vec = {0.f,1.13534f,1.91022f,2.07862f,1.58707f,0.59163f,-0.59163f,-1.58707f,-2.07862f,-1.91022f,-1.13534f,0.f,1.13534f,1.91022f,2.07862f};

//     // act
//     std::vector<float> returned_vec = SimuBlocks::SineWave(num_of_samples, amplitude, samples_per_period);

//     // compare
//     for (int i = 0; i < num_of_samples; ++i)
//     {
//         ASSERT_NEAR(expected_vec[i], returned_vec[i], 0.00002);
//     } 
// }

// TEST(SineWaveBlock, ThrowFailure)
// {
//     // arange
//     unsigned num_of_samples = 12;
//     float amplitude = 2.1f;
//     unsigned samples_per_period = 0;

//     // act and assert
//     ASSERT_THROW(SimuBlocks::SineWave(num_of_samples, amplitude, samples_per_period), std::invalid_argument);
// }

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