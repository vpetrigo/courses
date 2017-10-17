WITH RECURSIVE bfs AS (
    SELECT id, value, array[id] AS path FROM Keyword
    WHERE parent_id IS NULL
    UNION ALL
    SELECT C.id, C.value, P.path || C.id
    FROM Keyword C JOIN bfs P ON P.id = C.parent_id
),
get_parents(parents) AS (
    SELECT unnest(path) FROM bfs
)
SELECT id, COUNT(*) FROM bfs
JOIN get_parents ON (id = parents)
GROUP BY id ORDER BY id;
