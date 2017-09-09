Представьте себе, что вы программист, занимающийся производительностью вашего приложения. Вы увидели приведённый ниже код на языке Python и поняли, что он занимает слишком много времени. Попробуйте переписать его одним запросом.

Решением является текст SQL запроса. Обратите внимание на очередность столбцов в ответе. Прочими различиями в формате текстового вывода питона и SQL пренебрегите.

# Схема БД

```sql
CREATE TABLE Spacecraft(
  id SERIAL PRIMARY KEY,
  name TEXT UNIQUE,
  service_life INT DEFAULT 1000,
  birth_year INT CHECK(birth_year > 0)
);

CREATE TABLE Planet(
  id SERIAL PRIMARY KEY,
  name TEXT UNIQUE,
  distance NUMERIC(5,2)
);

CREATE TABLE Commander(
  id SERIAL PRIMARY KEY,
  name TEXT
);

CREATE TABLE Flight(
  id INT PRIMARY KEY,
  spacecraft_id INT REFERENCES Spacecraft,
  planet_id INT REFERENCES Planet,
  commander_id INT REFERENCES Commander,
  start_date DATE,
  UNIQUE(spacecraft_id, start_date),
  UNIQUE(commander_id, start_date)
);
```

# Код  на Python

```python
# encoding: utf-8
import psycopg2 as pg_driver

# Postgres, запущенный в докере, не требует пароля, если клиент находится на localhost
db = pg_driver.connect(user="postgres", host="localhost")
cur = db.cursor()

def fun1(commander_id):
  result = []
  cur.execute("SELECT commander_id, spacecraft_id, start_date FROM Flight")
  for flight in cur.fetchall():
    if flight[0] != commander_id:
      continue
    cur.execute("SELECT id, name FROM Spacecraft")
    for spacecraft in cur.fetchall():
      if spacecraft[0] == flight[1]:
        result.append((spacecraft, flight)) # добавляем в результат пару
  return result

def fun2(commander_id):
  result = []
  for spacecraft, flight in fun1(commander_id):
    cur.execute("SELECT id, name FROM Commander")
    for cmndr in cur.fetchall():
      if cmndr[0] == flight[0]:
        result.append((cmndr[1], spacecraft[1], flight[2])) # добавляем в результат тройку
  return result

for row in fun2(6):
  print row
```
