Это элементарный тест на понимание некоторых особенностей работы агрегатных функций.

У вас есть две таблицы, которые содержат в себе некие ключевые 
слова и связь между статьями и ключевыми  словами:

```sql
Keyword(id INT PRIMARY KEY, value TEXT) и 
PaperKeyword(paper_id INT, keyword_id INT REFERENCES Keyword)
```

Вы хотите найти ключевые слова, которые не проассоциированы ни с одной статьёй.
Для этого есть много способов, но вы по каким бы то ни было причинам 
решили воспользоваться агрегатными функциями и внешними  соединениями, и написали простой запрос.

Сколько строк будет в результате выполнения этого запроса?

```sql
SELECT Keyword.id
FROM Keyword LEFT OUTER JOIN PaperKeyword ON (Keyword.id = PaperKeyword.keyword_id)
GROUP BY Keyword.id
HAVING COUNT(*) = 0
```

Если вам нужно количество записей в таблицах, то их столько:

```sql
SELECT COUNT(*) FROM Keyword; -- вернул 100
SELECT COUNT(DISTINCT keyword_id) FROM PaperKeyword; -- вернул 75
SELECT COUNT(*) FROM PaperKeyword; -- вернул 1000
```
