import robot.RobotConnectionManagerMock;
import robot.RobotConnectionException;
import robot.RobotConnectionManager;
import robot.RobotConnection;

public class TestWithNormalMock {
    public static void main(String[] args) {
        moveRobot(new RobotConnectionManagerMock(), 1, 2);
    }

    public static void moveRobot(RobotConnectionManager robotConnectionManager, int toX, int toY) {
        final int RETRY_NUM = 3;
        boolean connectionEstablished = false;
        RobotConnection rc = robotConnectionManager.getConnection();

        for (int i = 0; i < RETRY_NUM && !connectionEstablished; ++i) {
            try (rc) {
                rc.moveRobotTo(toX, toY);
                connectionEstablished = true;
            }
            catch (RobotConnectionException re) {
                if (i == RETRY_NUM - 1) {
                    throw re;
                }
            }
        }
    }
}
