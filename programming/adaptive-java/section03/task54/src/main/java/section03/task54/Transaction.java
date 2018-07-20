package section03.task54;

import java.util.Date;

/**
 * Transaction: uuid: String, state: State (CANCELED, FINISHED, PROCESSING), sum: Long, created: Date
 */
public class Transaction {
    public enum State {CANCELED, FINISHED, PROCESSING}

    private String uuid;
    private State state;
    private Long sum;
    private Date created;

    public Transaction(String trUuid, State trState, Long trSum, Date trCreated) {
        uuid = trUuid;
        state = trState;
        sum = trSum;
        created = trCreated;
    }

        public String getUuid() {
        return uuid;
    }

    public void setUuid(String uuid) {
        this.uuid = uuid;
    }

    public State getState() {
        return state;
    }

    public void setState(State state) {
        this.state = state;
    }

    public Long getSum() {
        return sum;
    }

    public void setSum(Long sum) {
        this.sum = sum;
    }

    public Date getCreated() {
        return created;
    }

    public void setCreated(Date created) {
        this.created = created;
    }
}
