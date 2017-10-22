package robot;

public class RobotConnectionBadMock implements RobotConnection {
    @Override
    public void moveRobotTo(int x, int y) {
        System.out.printf("Move robot to X: %d; Y: %d\n", x, y);
        throw new RuntimeException("move: Cannot move robot");
    }

    @Override
    public void close() {
        System.out.println("Close connection");
        throw new RobotConnectionException("bad mock: Cannot close connection");
    }
}