WITH RECURSIVE round(id, value, num) AS (
    SELECT id, value, 1 AS num FROM Cities WHERE id = 0

    UNION ALL
    SELECT Cities.id, Cities.value, num + 1 FROM round, Cities
    WHERE right(round.value, 1) = lower(left(Cities.value, 1))
    AND num < (SELECT COUNT(*) FROM Cities) - 1
)
SELECT * FROM round;
