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

TEST_F(MainFunctionTest, TotalIncentiveCalculation) {
    // Setup specific employees and visitors
    SoftwareEngineer se_1, se_2;
    SalesPerson sp_1, sp_2, sp_3;
    CustomerSupporter cs_1;

    employeeList.push_back(&se_1); employeeList.push_back(&se_2);
    employeeList.push_back(&sp_1); employeeList.push_back(&sp_2); employeeList.push_back(&sp_3);
    employeeList.push_back(&cs_1);

    visitorList.push_back(&printInformationVisitor);
    visitorList.push_back(&incentiveCalculationVisitor);

    // Call Main function or equivalent logic
    Main(employeeList, visitorList);

    // Assert expected total incentive
    EXPECT_EQ(incentiveCalculationVisitor.GetTotalIncentive(), expectedIncentive);
}
