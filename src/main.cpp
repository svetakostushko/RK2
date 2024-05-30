#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

class SoftwareEngineer;
class SalesPerson;
class CustomerSupporter;

class EmployeeVisitor
{
public:
    virtual ~EmployeeVisitor() = default;

    virtual void VisitSoftwareEngineer(SoftwareEngineer& softwareEngineer) = 0;
    virtual void VisitSalesPerson(SalesPerson& salesPerson) = 0;
    virtual void VisitCustomerSupporter(CustomerSupporter& customerSupporter) = 0;
};

class Employee
{
public:
    virtual ~Employee() = default;

    virtual void Accept(EmployeeVisitor& visitor) = 0;
};

class SoftwareEngineer : public Employee
{
public:
    void Accept(EmployeeVisitor& visitor) override { visitor.VisitSoftwareEngineer(*this); }

    /* hard coded value for simplicity of example */
    std::uint64_t GetSoftwareQuality() const { 
        std::cout << "GetSoftwareQuality" << std::endl;
        return 40; 
    }
    std::uint64_t GetBusinessComprehension() const { return 20; }
};

class SalesPerson : public Employee
{
public:
    void Accept(EmployeeVisitor& visitor) override { visitor.VisitSalesPerson(*this); }

    /* hard coded value for simplicity of example */
    std::uint64_t GetSalesVolume() const { return 8000; }
};

class CustomerSupporter : public Employee
{
public:
    void Accept(EmployeeVisitor& visitor) override { visitor.VisitCustomerSupporter(*this); }

    /* hard coded value for simplicity of example */
    std::uint64_t GetCustomerSatisfaction() const { return 60; }
};

class IncentiveCalculationVisitor : public EmployeeVisitor
{
public:
    void VisitSoftwareEngineer(SoftwareEngineer& softwareEngineer) override
    {
        totalIncentive_ += softwareEngineer.GetSoftwareQuality() * 2 +
                           softwareEngineer.GetBusinessComprehension();
    }

    void VisitSalesPerson(SalesPerson& salesPerson) override
    {
        totalIncentive_ += static_cast<std::uint64_t>(salesPerson.GetSalesVolume() * 0.01);
    }

    void VisitCustomerSupporter(CustomerSupporter& customerSupporter) override
    {
        totalIncentive_ += customerSupporter.GetCustomerSatisfaction();
    }

    std::uint64_t GetTotalIncentive() const { return totalIncentive_; }

private:
    std::uint64_t totalIncentive_{ 0u };
};

class PrintInformationVisitor : public EmployeeVisitor
{
public:
    void VisitSoftwareEngineer(SoftwareEngineer& softwareEngineer) override
    {
        std::cout << "--- Information of Software Engineer ---" << std::endl;
        std::cout << "Software Quality       : " << softwareEngineer.GetSoftwareQuality() << std::endl;
        std::cout << "Business Comprehension : " << softwareEngineer.GetBusinessComprehension() << std::endl;
    }

    void VisitSalesPerson(SalesPerson& salesPerson) override
    {
        std::cout << "--- Information of Sales Person ---" << std::endl;
        std::cout << "Sales Volume : " << salesPerson.GetSalesVolume() << std::endl;
    }

    void VisitCustomerSupporter(CustomerSupporter& customerSupporter) override
    {
        std::cout << "--- Information of Customer Supporter ---" << std::endl;
        std::cout << "Customer Satisfaction : " << customerSupporter.GetCustomerSatisfaction() << std::endl;
    }
};

void Calculate(const std::vector<Employee*>& employeeList,
               const std::vector<EmployeeVisitor*>& visitorList)
{
    for (auto employee : employeeList)
    {
        for (auto visitor : visitorList)
        {
            employee->Accept(*visitor);
        }
    }
}
void Main()
{
    //
    SoftwareEngineer se_1, se_2;
    SalesPerson sp_1, sp_2, sp_3;
    CustomerSupporter cs_1;

    PrintInformationVisitor printInformationVisitor;
    IncentiveCalculationVisitor incentiveCalculationVisitor;

    //
    std::vector<Employee*> employeeList;

    employeeList.push_back(&se_1); employeeList.push_back(&se_2);
    employeeList.push_back(&sp_1); employeeList.push_back(&sp_2); employeeList.push_back(&sp_3);
    employeeList.push_back(&cs_1);

    std::vector<EmployeeVisitor*> visitorList;
    visitorList.push_back(&printInformationVisitor);
    visitorList.push_back(&incentiveCalculationVisitor);

    //
    Calculate(employeeList, visitorList);

    //
    std::cout << "\n*** Total Incentive : " << incentiveCalculationVisitor.GetTotalIncentive() << std::endl;
}
