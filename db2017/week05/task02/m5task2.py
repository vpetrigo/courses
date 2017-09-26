# encoding: utf-8
import sqlite3
from random import randint
from random import shuffle

db = sqlite3.connect('m5task2.db')
cur = db.cursor()

cur.execute("DROP TABLE IF EXISTS T")
cur.execute("CREATE TABLE T(id INT PRIMARY KEY, value INT UNIQUE)")
db.commit()

values = set()
halfset = randint(5, 15)
for i in range(0, halfset*2 + 1):
    while True:
        nextval = randint(1, 100)
        if nextval not in values:
            values.add(nextval)
            break

v2 = [v for v in values]
shuffle(v2)
i = 1
for v in v2:
    cur.execute("INSERT INTO T(id, value) VALUES(?, ?)", (i, v))
    i = i + 1
db.commit()
