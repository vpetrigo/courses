package robot;

public class RobotConnectionManagerMock implements RobotConnectionManager {
    @Override
    public RobotConnection getConnection() {
        System.out.println("Connection");
        return new RobotConnectionMock();
    }
}
