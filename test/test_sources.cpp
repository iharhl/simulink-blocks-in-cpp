#include "gtest/gtest.h"
#include "Constant.h"
#include "PulseGenerator.h"
#include "SineWave.h"
#include "Step.h"
#include "Ramp.h"
#include "RandomNumberGenerator.h"
#include "TransferFunction.h"
#include "FixedPointArithmetic.h"
#include <iostream>

TEST(StepBlock, TypeUint8)
{
    // Arrange
    const std::uint8_t InitValue = 0;
    const std::uint8_t FinalValue = 120;
    const unsigned StepSample = 3;

    const std::array<std::uint8_t, 10> ExpectedOutput = {0,0,120,120,120,120,120,120,120,120};
    std::array<std::uint8_t, 10> ActualOutput {};

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
    // Arrange
    const float InitValue = 1.f;
    const float FinalValue = 5.f;
    const unsigned StepSample = 5;

    const std::array<float, 10> ExpectedOutput = {1.f,1.f,1.f,1.f,5.f,5.f,5.f,5.f,5.f,5.f};
    std::array<float, 10> ActualOutput {};

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
    // Arrange
    const std::uint8_t Amplitude = 18;
    const unsigned Period = 4;
    const unsigned DutyCycle = 25;
    const unsigned PhaseDelay = 0;

    const std::array<std::uint8_t, 10> ExpectedOutput = {18,0,0,0,18,0,0,0,18,0};
    std::array<std::uint8_t, 10> ActualOutput {};

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
    // Arrange
    const float Amplitude = 4.1f;
    const unsigned Period = 6;
    const unsigned DutyCycle = 50;
    const unsigned PhaseDelay = 2;

    const std::array<float, 10> ExpectedOutput = {0.f,0.f,4.1f,4.1f,4.1f,0.f,0.f,0.f,4.1f,4.1f};
    std::array<float, 10> ActualOutput {};

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

TEST(RampBlock, TypeUint8)
{
    // Arrange
    const std::uint8_t Sloap = 7;
    const unsigned StartRampSample = 3;
    const std::uint8_t InitialOutput = 1;

    const std::array<std::uint8_t, 6> ExpectedOutput = {1,1,1,8,15,22};
    std::array<std::uint8_t, 6> ActualOutput {};

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
    // Arrange
    const float Sloap = 4.3f;
    const unsigned StartRampSample = 1;
    const float InitialOutput = 0.5f;

    const std::array<float, 4> ExpectedOutput = {0.5f, 4.8f, 9.1f, 13.4f};
    std::array<float, 4> ActualOutput {};

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

TEST(ConstBlock, TypeUint8)
{
    // Arrange
    const std::uint8_t ConstValue = 15;

    const std::array<std::uint8_t, 5> ExpectedOutput = {15,15,15,15,15};
    std::array<std::uint8_t, 5> ActualOutput {};

    SimuBlocks::Constant ConstBlock(ConstValue);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        ConstBlock.Tick();
        ActualOutput[i] = ConstBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(ConstBlock, TypeFloat)
{
    // Arrange
    const float ConstValue = 34.43f;

    const std::array<float, 5> ExpectedOutput = {34.43f,34.43f,34.43f,34.43f,34.43f};
    std::array<float, 5> ActualOutput {};

    SimuBlocks::Constant ConstBlock(ConstValue);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        ConstBlock.Tick();
        ActualOutput[i] = ConstBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_FLOAT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(SineWaveBlock, TypeDouble)
{
    // Arrange
    const double Amplitude = 4.5f;
    const unsigned SamplesPerPeriod = 15;
    const unsigned PhaseDelay = 2;
    const double Bias = 0.2f;

    const std::array<double, 15> ExpectedOutput = {}; // TODO
    std::array<double, 15> ActualOutput {};

    SimuBlocks::SineWave SineWaveBlock(Amplitude, SamplesPerPeriod, PhaseDelay, Bias);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        SineWaveBlock.Tick();
        ActualOutput[i] = SineWaveBlock.GetOutput();
        std::cout << ActualOutput[i] << " ";
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_EQ(ExpectedOutput[i], ActualOutput[i]);
}

TEST(SineWaveBlock, TypeFloat)
{
    // Arrange
    const float Amplitude = 2.1f;
    const unsigned SamplesPerPeriod = 12;
    const unsigned PhaseDelay = 0;
    const float Bias = 0;

    const std::array<float, 15> ExpectedOutput = {0.f,1.13534f,1.91022f,2.07862f,1.58707f,0.59163f,\
                                            -0.59163f,-1.58707f,-2.07862f,-1.91022f,-1.13534f,\
                                            0.f,1.13534f,1.91022f,2.07862f};
    std::array<float, 15> ActualOutput {};

    SimuBlocks::SineWave SineWaveBlock(Amplitude, SamplesPerPeriod, PhaseDelay, Bias);

    // Act
    for (int i = 0; i < ExpectedOutput.size(); ++i)
    {
        SineWaveBlock.Tick();
        ActualOutput[i] = SineWaveBlock.GetOutput();
    }

    // Assert
    for (int i = 0; i < ExpectedOutput.size(); ++i)
        ASSERT_NEAR(ExpectedOutput[i], ActualOutput[i], 0.00001);
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

TEST(RandomNumberBlock, TypeFloat)
{
    // Arrange
    const float MinLimit = 0.f;
    const float MaxLimit = 2.f;

    std::array<float, 15> ActualOutput {};
    int duplicates = 0; // record number of duplicates

    SimuBlocks::RandomNumberGenerator RandomNumberGeneratorBlock(MinLimit, MaxLimit);

    // Act
    for (int i = 0; i < ActualOutput.size(); ++i)
    {
        RandomNumberGeneratorBlock.Tick();
        ActualOutput[i] = RandomNumberGeneratorBlock.GetOutput();
        if (i != 0) { if (ActualOutput[i] == ActualOutput[i-1]) { duplicates++; } }
    }

    // Compare
    for (float i : ActualOutput)
    {
        ASSERT_LE(i, MaxLimit);
        ASSERT_GE(i, MinLimit);
    }
    ASSERT_LE(duplicates, static_cast<int>(ActualOutput.size() / 2));
}

TEST(TransferFunctionBlock, IntegratorResponse)
{
    // Arrange
    const std::array<float,3> NominatorCoefficients = {0, 0, 1};
    const std::array<float,3> DenominatorCoefficients = {0, 1, 0};
    const float SamplingPeriod = 0.001;

    std::array<float, 5> ActualOutput {};
    const std::array<float, 5> ExpectedOutput = {SamplingPeriod*0, SamplingPeriod*1, SamplingPeriod*2, SamplingPeriod*3, SamplingPeriod*4};

    SimuBlocks::TransferFunction<float> TransferFunctionBlock(NominatorCoefficients, DenominatorCoefficients, SamplingPeriod);

    // Act
    TransferFunctionBlock.SetInput(1);
    for (float& i : ActualOutput)
    {
        TransferFunctionBlock.Tick();
        i = TransferFunctionBlock.GetOutput();
    }

    // Compare
    for (int i = 0; i < ActualOutput.size(); ++i)
    {
        ASSERT_FLOAT_EQ(ExpectedOutput[i], ActualOutput[i]);
    }
}

TEST(TransferFunctionBlock, SecondOrderTFResponse)
{
    // Arrange
    const std::array<float,3> NominatorCoefficients = {0, 1, 2}; // s+2
    const std::array<float,3> DenominatorCoefficients = {1, 1, 2}; // s^2+s+2
    const float SamplingPeriod = 0.0001;

    const int Timestep1 = static_cast<int>(1 / SamplingPeriod); // [tick]
    const int Timestep2 = static_cast<int>(2 / SamplingPeriod); // [tick]

    const float ExpectedMinOutputAtTimestep1 = 1.0;
    const float ExpectedMaxOutputAtTimestep1 = 1.1;
    const float ExpectedMinOutputAtTimestep2 = 1.35;
    const float ExpectedMaxOutputAtTimestep2 = 1.45;

    SimuBlocks::TransferFunction<float> TransferFunctionBlock(NominatorCoefficients, DenominatorCoefficients, SamplingPeriod);

    float ActualOutputAtTimestep1;
    float ActualOutputAtTimestep2;

    // Act
    TransferFunctionBlock.SetInput(1);
    for (int i = 0; i <= Timestep2; ++i)
    {
        TransferFunctionBlock.Tick();
        if (i == Timestep1)
            ActualOutputAtTimestep1 = TransferFunctionBlock.GetOutput();
        else if (i == Timestep2)
            ActualOutputAtTimestep2 = TransferFunctionBlock.GetOutput();
    }

    // Compare
    ASSERT_LT(ActualOutputAtTimestep1, ExpectedMaxOutputAtTimestep1);
    ASSERT_GT(ActualOutputAtTimestep1, ExpectedMinOutputAtTimestep1);
    ASSERT_LT(ActualOutputAtTimestep2, ExpectedMaxOutputAtTimestep2);
    ASSERT_GT(ActualOutputAtTimestep2, ExpectedMinOutputAtTimestep2);
}

TEST(FixedPointArithmetic, Test1)
{

    // Arrange
    using sfix16_En8 = fixdt<int16_t, 8>;
    // int16_t ValueAsInteger = 2432;
    const float ValueAsFloat = 9.5;
    
    // Act
    const sfix16_En8 FixedPointValue(9.5f);

    // Assert

    // GTest assert does not work...
    // ASSERT_EQ(FixedPointValue, ValueAsInteger);
    // assert(FixedPointValue == ValueAsInteger);

    ASSERT_EQ(static_cast<float>(FixedPointValue), ValueAsFloat);
    ASSERT_EQ(sizeof(FixedPointValue), 2); // 2 bytes
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); 
}