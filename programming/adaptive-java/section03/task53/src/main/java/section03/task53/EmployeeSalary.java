package section03.task53;

import java.util.List;

public class EmployeeSalary {
    /**
     * Calculates the number of employees with salary >= threshold (only for 111- departments)
     *
     * @param departments are list of departments
     * @param threshold   is lower edge of salary
     * @return the number of employees
     */
    public static long calcNumberOfEmployees(List<Department> departments, long threshold) {
        return departments.stream().filter(d -> d.getCode().startsWith("111-")).
                flatMap(d -> d.getEmployees().stream()).
                filter(e -> e.getSalary() >= threshold).count();
    }

    public static void main(String[] args) {
        List<Employee> newEmployeesIT = List.of(new Employee("Jess", 10000L),
                new Employee("Ivan", 50000L));
        List<Employee> newEmployeesEO = List.of(new Employee("Steve", 100000L),
                new Employee("Mark", 500000L));
        Department department = new Department("IT", "111-123", newEmployeesIT);
        Department departmentEO = new Department("EO", "100-124", newEmployeesEO);

        System.out.println(calcNumberOfEmployees(List.of(department, departmentEO), 20000L));
    }
}
