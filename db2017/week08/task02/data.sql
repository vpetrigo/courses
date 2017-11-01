CREATE OR REPLACE FUNCTION GenerateData(factor INT) RETURNS VOID AS $$
BEGIN
-- ================================
-- Перечисление государственных устройств
INSERT INTO Government(value)
SELECT unnest(ARRAY['Анархия', 'Коммунизм', 'Конфедерация', 'Олигархия', 'Демократия', 'Диктатура', 'Феодализм']);

-- ================================
-- Капитаны со случайными рейтингами
WITH Names AS (
  SELECT unnest(ARRAY['Громозека', 'Ким', 'Буран', 'Зелёный', 'Горбовский', 'Ийон Тихий', 'Форд Префект', 'Комов', 'Каммерер', 'Гагарин', 'Титов', 'Леонов', 'Крикалев', 'Армстронг', 'Олдрин']) AS name
), Ratings AS (
  select enumsortorder AS rating_num, enumlabel::Rating AS rating_value
  from pg_catalog.pg_enum
  WHERE enumtypid = 'rating'::regtype ORDER BY enumsortorder
),
NameRating AS (
  SELECT name, (0.5 + random() * (SELECT MAX(rating_num) FROM Ratings))::int
  AS rating_num FROM Names
)
INSERT INTO Commander(name, rating)
SELECT name, rating_value FROM NameRating JOIN Ratings USING(rating_num);

-- ================================
-- Перечисление планет со случайными расстояниями и правительствами
WITH PlanetNames AS (
  SELECT unnest(ARRAY[
    'Tibedied', 'Qube', 'Leleer', 'Biarge', 'Xequerin', 'Tiraor', 'Rabedira', 'Lave',
    'Zaatxe', 'Diusreza', 'Teaatis', 'Riinus', 'Esbiza', 'Ontimaxe', 'Cebetela', 'Ceedra',
    'Rizala', 'Atriso', 'Teanrebi', 'Azaqu', 'Retila', 'Sotiqu', 'Inleus', 'Onrira', 'Ceinzala',
    'Biisza', 'Legees', 'Quator', 'Arexe', 'Atrabiin', 'Usanat', 'Xeesle', 'Oreseren', 'Inera',
    'Inus', 'Isence', 'Reesdice', 'Terea', 'Orgetibe', 'Reorte', 'Ququor', 'Geinona',
    'Anarlaqu', 'Oresri', 'Esesla', 'Socelage', 'Riedquat', 'Gerege', 'Usle', 'Malama',
    'Aesbion', 'Alaza', 'Xeaqu', 'Raoror', 'Ororqu', 'Leesti', 'Geisgeza', 'Zainlabi',
    'Uscela', 'Isveve', 'Tioranin', 'Learorce', 'Esusti', 'Ususor', 'Maregeis', 'Aate',
    'Sori', 'Cemave', 'Arusqudi', 'Eredve', 'Regeatge', 'Edinso', 'Ra', 'Aronar',
    'Arraesso', 'Cevege', 'Orteve', 'Geerra', 'Soinuste', 'Erlage', 'Xeaan', 'Veis',
    'Ensoreus', 'Riveis', 'Bivea', 'Ermaso', 'Velete', 'Engema', 'Atrienxe', 'Beusrior',
    'Ontiat', 'Atarza', 'Arazaes', 'Xeeranre', 'Quzadi', 'Isti', 'Digebiti', 'Leoned',
    'Enzaer', 'Teraed'
  ]) AS name
)
INSERT INTO Planet(name, distance, government_id)
SELECT name, (random() * 1000)::numeric(5,2), (0.5 + random() * (SELECT COUNT(*) FROM Government))::int
FROM PlanetNames;

-- ================================
-- Стоимость билета увеличивается с увеличением расстояния и повышением класса корабля
WITH Planets AS (
  SELECT id, distance FROM Planet
), Classes AS (
  SELECT generate_series(1,3) AS spacecraft_class
)
INSERT INTO Price (planet_id, spacecraft_class, price)
SELECT id, spacecraft_class, (random() * 1000 + distance + 300*(4 - spacecraft_class))::INT
FROM Planets CROSS JOIN Classes;

-- ================================
-- Перечисление кораблей со случайными классами и вместимостью
WITH Names AS (
  SELECT unnest(ARRAY[
      'Кедр', 'Орел', 'Сокол', 'Беркут', 'Ястреб', 'Чайка', 'Рубин', 'Алмаз', 'Аргон', 'Амур', 'Байкал', 'Антей', 'Буран'
  ]) AS name
)
INSERT INTO Spacecraft(name, capacity, class)
SELECT name, (3+random()*20)::INT, (0.5+random()*3)::INT
FROM Names;

-- ================================
-- Случайные полеты
WITH MaxValues AS (
  SELECT (SELECT MAX(id) FROM Spacecraft) AS spacecraft,
  (SELECT MAX(id) FROM Commander) AS commander,
  (SELECT MAX(id) FROM Planet) AS planet
),
Flights AS (
  SELECT generate_series(1, 500*factor) AS id
)
INSERT INTO Flight(id, spacecraft_id, commander_id, planet_id, date)
SELECT id, (0.5 + random()*spacecraft)::INT,
    (0.5 + random()*commander)::INT,
    (0.5 + random()*planet)::INT,
    ('2084-01-01'::DATE + random()*365*5 * INTERVAL '1 day')::DATE
FROM MaxValues CROSS JOIN Flights;

-- ================================
-- Случайные пассажиры
WITH Paxes AS(
  SELECT generate_series(1, 100*factor) AS id
), Races AS (
  select enumsortorder AS race_num, enumlabel::Race AS race_value
  from pg_catalog.pg_enum
  WHERE enumtypid = 'race'::regtype ORDER BY enumsortorder
), PaxRace AS (
  SELECT id, 'Pax' || id::TEXT AS name, (0.5 + random() * (SELECT MAX(race_num) FROM Races))::int
  AS race_num FROM Paxes
)
INSERT INTO Pax(id, name, race)
SELECT id, name, race_value FROM PaxRace JOIN Races USING(race_num);

-- ================================
-- Случайные бронирования
WITH Bookings AS (
  SELECT generate_series(1, 2000*factor) AS id
),
MaxValues AS (
  SELECT (SELECT MAX(id) FROM Pax) AS pax,
  (SELECT MAX(id) FROM Flight) AS flight
)
INSERT INTO Booking(ref_num, pax_id, flight_id)
SELECT substring(md5(id::TEXT)::TEXT for sqrt(factor)::INT), (0.5 + random() * pax)::INT, (0.5 + random() * flight)::INT
FROM Bookings CROSS JOIN MaxValues;

END;
$$ LANGUAGE plpgsql;

SELECT GenerateData(100);
