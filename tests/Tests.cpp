#include <gtest/gtest.h>
#include <main.cpp>

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
TEST_F(MainLogicTest, TotalIncentiveCalculation) {
    RunMainLogic();  // This function should configure the visitors and employees.

    // Assuming you have some way to retrieve the incentiveCalculator from RunMainLogic or its state is globally accessible.
    extern IncentiveCalculationVisitor incentiveCalculationVisitor;  // This needs to be declared somewhere accessible.

    unsigned int expectedTotalIncentive = 0;  // You need to calculate the expected total based on your business logic.

    // Assert that the total incentive calculated by the visitor is as expected.
    EXPECT_EQ(incentiveCalculationVisitor.GetTotalIncentive(), expectedTotalIncentive);
}
