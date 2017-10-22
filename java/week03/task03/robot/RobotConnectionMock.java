package robot;

public class RobotConnectionMock implements RobotConnection {
    @Override
    public void moveRobotTo(int x, int y) {
        System.out.printf("Move robot to X: %d; Y: %d\n", x, y);
    }

    @Override
    public void close() {
        System.out.println("Close connection");
    }
}