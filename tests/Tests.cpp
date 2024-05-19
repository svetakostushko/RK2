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
