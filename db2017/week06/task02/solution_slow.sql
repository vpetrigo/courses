WITH RECURSIVE bfs AS (
    SELECT id, value, array[id] AS path FROM Keyword
    WHERE parent_id IS NULL
 
    UNION ALL
    SELECT C.id, C.value, P.path || C.id
    FROM Keyword C JOIN bfs P ON P.id = C.parent_id
)
SELECT DISTINCT D.id, COUNT(*) OVER (PARTITION by D.id) 
FROM bfs D JOIN bfs P 
ON (P.path @> D.path)
ORDER BY id;
