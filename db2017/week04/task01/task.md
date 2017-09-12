У вас есть приложение для управления конференциями и в нём специальная функция, которая позволяет мониторить конференции со слишком высоким коэффициентом принятия. Коэффициент принятия (acceptance ratio) для каждой конференции в каждом году -- это отношение количества принятых статей в этому году к общему количеству поданных статей в этому году.

Схема БД была довольно простой:

```sql
-- Серия ежегодных конференций

CREATE TABLE Conference (
  id   INT PRIMARY KEY,
  name TEXT
);

-- "Событие" -- конференция в конкретном году

CREATE TABLE ConferenceEvent (
  id               INT PRIMARY KEY,
  conference_id    INT REFERENCES Conference,
  year             INT,
  total_papers     INT,
  accepted_papers  INT,
  acceptance_ratio NUMERIC(3, 2),
  UNIQUE (conference_id, year)
);
```

Так получилось, что в очередном обновлении вашей информационной системы схеме БД пришлось пережить некоторую миграцию. SQL-операторы, проделывающие миграцию, показаны ниже:

```sql
ALTER TABLE ConferenceEvent DROP COLUMN total_papers;
ALTER TABLE ConferenceEvent DROP COLUMN accepted_papers;
ALTER TABLE ConferenceEvent DROP COLUMN acceptance_ratio;
CREATE TABLE Paper(
  id INT PRIMARY KEY,
  event_id INT REFERENCES ConferenceEvent,
  title TEXT,
  accepted BOOLEAN);
```

К счастью, вы озаботились созданием представления, и хотите
теперь его переписать, чтобы приложение этой миграции не заметило. 
Представление называется `HighPaperAcceptance` и до миграции оно выглядело так:

```sql
CREATE VIEW HighPaperAcceptance AS
SELECT C.name, CE.year, CE.total_papers, CE.acceptance_ratio
FROM ConferenceEvent CE 
JOIN Conference C ON C.id = CE.conference_id
WHERE CE.total_papers > 5 AND CE.acceptance_ratio > 0.75;
```

Вам нужно написать запрос, формирующий тело представления после миграции. 
Ключевые слова `CREATE VIEW` писать не нужно. Удалять старое представление не нужно.
Пример валидного, но неправильного ответа:

```sql
SELECT C.name, CE.year, 0 as total_papers, 0 AS acceptance_ratio
FROM ConferenceEvent CE JOIN Conference C ON C.id = CE.conference_id;
```

Полезные подсказки по языку SQL в Постгресе:
boolean приводится к целочисленным 0 и 1 приведением к целому числу: `SELECT TRUE::INT;`
Целые числа превращаются в числа с двумя знаками после запятой приведением к `NUMERIC(3,2)`: `SELECT 1::NUMERIC(3,2)`
