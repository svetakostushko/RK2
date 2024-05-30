#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "main.cpp"  // Ensure this points to the correct header/source file

class MockSoftwareEngineer : public SoftwareEngineer {
public:
    MOCK_METHOD(std::uint64_t, GetSoftwareQuality, (), (const));
    MOCK_METHOD(std::uint64_t, GetBusinessComprehension, (), (const));
};

TEST(EmployeeVisitorTest1, SoftwareEngineerVisitor) {
  SoftwareEngineer softwareEngineer;
  IncentiveCalculationVisitor incentiveCalculator;

  softwareEngineer.Accept(incentiveCalculator);

  EXPECT_EQ(incentiveCalculator.GetTotalIncentive(), 100u);
}


TEST(EmployeeVisitorTest2, SalesPersonVisitor) {
  SalesPerson salesPerson;
  IncentiveCalculationVisitor incentiveCalculator;

  salesPerson.Accept(incentiveCalculator);

  EXPECT_EQ(incentiveCalculator.GetTotalIncentive(), 80u);
}


TEST(EmployeeVisitorTest3, MultipleVisitors) {
  SoftwareEngineer softwareEngineer;
  SalesPerson salesPerson;
  CustomerSupporter customerSupporter;
  std::vector<Employee*> employees{&softwareEngineer, &salesPerson, &customerSupporter};

  IncentiveCalculationVisitor incentiveCalculator;
  PrintInformationVisitor printInformationVisitor;
  std::vector<EmployeeVisitor*> visitors{&incentiveCalculator, &printInformationVisitor};

  Calculate(employees, visitors);

  EXPECT_EQ(incentiveCalculator.GetTotalIncentive(), 240u);
}

TEST(MainFunctionTest, MainExecution) {
    // Redirect cout to a string stream to capture output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    // Call the Main function
    Main();

    std::cout.rdbuf(old);  // Reset cout to its old buffer

    std::string expectedOutput =
        "--- Information of Software Engineer ---\n"
        "Software Quality       : 40\n"
        "Business Comprehension : 20\n"
        "--- Information of Software Engineer ---\n"
        "Software Quality       : 40\n"
        "Business Comprehension : 20\n"
        "--- Information of Sales Person ---\n"
        "Sales Volume : 8000\n"
        "--- Information of Sales Person ---\n"
        "Sales Volume : 8000\n"
        "--- Information of Sales Person ---\n"
        "Sales Volume : 8000\n"
        "--- Information of Customer Supporter ---\n"
        "Customer Satisfaction : 60\n"
        "\n*** Total Incentive : 500\n";

    EXPECT_EQ(buffer.str(), expectedOutput);
}

TEST(EmployeeVisitorTest, GetSoftwareQualityCallCount) {
    MockSoftwareEngineer mockSoftwareEngineer;
    IncentiveCalculationVisitor incentiveCalculator;

    EXPECT_CALL(mockSoftwareEngineer, GetSoftwareQuality())
        .Times(testing::Exactly(0)); 

    mockSoftwareEngineer.Accept(incentiveCalculator);

    EXPECT_EQ(incentiveCalculator.GetTotalIncentive(), 100u);
}
