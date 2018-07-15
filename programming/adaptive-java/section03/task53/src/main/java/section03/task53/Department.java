package section03.task53;

import java.util.List;

public class Department {
    private String name;
    private String code;
    private List<Employee> employees;

    public Department(String nameDep, String codeDep, List<Employee> employeesDep) {
        name = nameDep;
        code = codeDep;
        employees = employeesDep;
    }

    public String getName() {
        return name;
    }

    public String getCode() {
        return code;
    }

    public List<Employee> getEmployees() {
        return employees;
    }
}
