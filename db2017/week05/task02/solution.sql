WITH count_less AS 
(
	SELECT T1.value, COUNT(*) AS sorted_id 
    FROM T AS T1 JOIN T AS T2 
    ON (T1.value >= T2.value) 
    GROUP BY T1.value
),
elems_cnt AS
(
    SELECT COUNT(*) as cnt
    FROM T
)
SELECT value, cnt FROM count_less, elems_cnt WHERE sorted_id = cnt / 2 + 1;
