WITH aux AS (
  SELECT A.id, A.value, A.path, COUNT(*) as size, ROW_NUMBER(*) OVER(ORDER BY A.path) as ord
  FROM KeywordLtree A, KeywordLtree B
  WHERE A.path @> B.path
  GROUP BY A.id, A.value, A.path
)
SELECT id, value, 1 + (ord - 1) * 2 - nlevel(path) as lft, (ord + size - 1) * 2 - nlevel(path) as rgt
FROM aux ORDER BY lft;