WITH RECURSIVE round(id, value, num) AS (
    SELECT id, value, 1 AS num, ARRAY[id] AS visited FROM Cities WHERE id = 0

    UNION ALL
    SELECT Cities.id, Cities.value, num + 1, array_append(visited, Cities.id) FROM round, Cities
    WHERE right(round.value, 1) = lower(left(Cities.value, 1))
    AND Cities.id != ALL(visited)
)
SELECT id, value, num FROM round;
