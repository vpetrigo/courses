DROP TABLE IF EXISTS Cities;

CREATE TABLE Cities(
      id INT PRIMARY KEY,
      value TEXT
);
-- Пример данных
INSERT INTO Cities(id, value) VALUES
    (1, 'Воркута'), (0, 'Джамбул'), (2, 'Львов'), 
    (3, 'Кингисепп'), (4, 'Москва'), (5, 'Амстердам');
