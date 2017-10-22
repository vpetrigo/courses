package robot;

public class RobotConnectionManagerBadMock implements RobotConnectionManager {
    @Override
    public RobotConnection getConnection() {
        System.out.println("Connection");
        return new RobotConnectionBadMock();
    }
}
