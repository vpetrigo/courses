# Третий запрос

Запрос находит рейсы, выполненные капитаном `_commander_name`
 в период с 1 апреля 2084 года по 1 мая 2084 года, на которых
было перевезено более чем `_pax_count` пассажиров из расы `'Men'`.  

```sql
-- Здесь можно сделать что-нибудь до начала теста
-- CREATE INDEX idx1 ON Commander(name);

-------- Запрос, нуждающийся в оптимизации
-- 
-- Запрос будет получать параметры commander_name и pax_count
-- Названия и типы возвращаемых столбцов:
-- TABLE(flight_id INT, commander_name TEXT, pax_count INT)

SELECT id AS flight_id, name AS commander_name, pax_count FROM (
    SELECT F.id, C.name
    FROM Commander C
    JOIN Flight F ON F.commander_id=C.id
    WHERE F.date BETWEEN '2084-04-01' AND '2084-05-01'
    AND C.name = _commander_name
) R
JOIN (
    SELECT F.id, COUNT(P.id)::INT AS pax_count
    FROM Flight F
    JOIN Booking B ON B.flight_id = F.id
    JOIN Pax P ON B.pax_id=P.id
    WHERE P.race='Men'
    GROUP BY F.id
) T USING(id) WHERE T.pax_count>_pax_count;
```
