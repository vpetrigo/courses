package section03.task53;

public class Employee {
    private String name;
    private Long salary;

    public Employee(String employeeName, Long employeeSalary) {
        name = employeeName;
        salary = employeeSalary;
    }

    public Long getSalary() {
        return salary;
    }

    public String getName() {
        return name;
    }
}
