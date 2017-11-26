CREATE EXTENSION HSTORE;
-- Справочник политических строев
CREATE TABLE Government(id SERIAL PRIMARY KEY, value TEXT UNIQUE);

-- Планета, её название, расстояние до Земли, политический строй
CREATE TABLE Planet(
  id SERIAL PRIMARY KEY,
  name TEXT UNIQUE,
  distance NUMERIC(5,2),
  government_id INT REFERENCES Government,
  wiki HSTORE,
  wiki_jsonb JSONB);

-- Значения рейтинга пилотов
CREATE TYPE Rating AS ENUM('Harmless', 'Poor', 'Average', 'Competent', 'Dangerous', 'Deadly', 'Elite');

-- Пилот корабля
CREATE TABLE Commander(
  id SERIAL PRIMARY KEY,
  name TEXT UNIQUE,
  rating Rating);

-- Полет на планету в означеную дату, выполняемый кораблем, пилотируемый капитаном
CREATE TABLE Flight(id INT PRIMARY KEY,
  commander_id INT REFERENCES Commander,
  planet_id INT REFERENCES Planet,
  date DATE
);

CREATE TABLE PlanetTags(
  planet_id INT REFERENCES Planet,
  name TEXT,
  value TEXT);

CREATE TABLE CommanderAchievements(
  commander_id INT PRIMARY KEY REFERENCES Commander,
  data JSONB
);

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
SELECT name, rating_value
FROM NameRating JOIN Ratings USING(rating_num);

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
-- Случайные полеты
WITH MaxValues AS (
  SELECT
    (SELECT MAX(id) FROM Commander) AS commander,
    (SELECT MAX(id) FROM Planet) AS planet
),
Flights AS (
  SELECT generate_series(1, 5000) AS id
)
INSERT INTO Flight(id, commander_id, planet_id, date)
SELECT id,
    (0.5 + random()*commander)::INT,
    (0.5 + random()*planet)::INT,
    ('2084-01-01'::DATE + random()*365*5 * INTERVAL '1 day')::DATE
FROM MaxValues CROSS JOIN Flights;


-- ===================================
-- Просто фичи планет
INSERT INTO planettags
WITH Features AS (
  SELECT key as name, value::NUMERIC(3,2) AS feature_prob FROM each(
    'fuel => 0.7, food => 0.7, water => 0.5, gold => 0.01, minerals => 0.8, gravitsapa => 0.1, danger => 0.2'
  )
),
Probs AS (
  SELECT Features.name,
  CASE WHEN random() <= Features.feature_prob THEN true ELSE false END AS has_feature,
  Planet.id,
  random() AS prob FROM Features CROSS JOIN Planet
)
SELECT id AS planet_id, name,
       CASE WHEN prob >= 0.5 THEN '1' ELSE '0' END as value
FROM Probs WHERE has_feature;


-- =====================================
-- Причины опасности
INSERT INTO planettags
WITH DangerousPlanets AS (
  SELECT planet_id FROM planettags
  WHERE name = 'danger' AND value = '1'
),
Features AS (
  SELECT key as name,
  value::NUMERIC(3,2) AS feature_prob FROM each(
    'dinosaurs => 0.1, weapons => 0.6, pirates => 0.3, earthquakes => 0.2, crime => 0.6, mosquitoes => 0.6'
  )
),
Probs AS (
  SELECT Features.name,
  DP.planet_id,
  CASE WHEN random() <= Features.feature_prob THEN true ELSE false END AS has_feature
  FROM Features CROSS JOIN DangerousPlanets DP
)
SELECT planet_id, name, '1' as value
FROM Probs WHERE has_feature;

-- ========================================
-- Превращаем EAV в HSTORE
WITH kv AS (
  SELECT planet_id,
         ARRAY[name, value] AS kv
  FROM PlanetTags
),
T AS (
SELECT planet_id AS id, hstore(array_agg(kv)) AS tags FROM kv GROUP BY planet_id
)
UPDATE Planet AS P SET wiki = T.tags
FROM T WHERE T.id=P.id;

-- ==========================================
-- Добавляем немного опасности в безопасные планеты
WITH SafePlanets AS (
  SELECT id AS planet_id FROM Planet
  WHERE NOT wiki @> 'danger => 1'
),
Features AS (
  SELECT key as name,
  value::NUMERIC(3,2) AS feature_prob FROM each(
    'dinosaurs => 0.3, weapons => 0.1, pirates => 0.1, earthquakes => 0.1, crime => 0.5, mosquitoes => 0.9'
  )
),
Probs AS (
  SELECT Features.name,
  P.planet_id,
  CASE WHEN random() <= Features.feature_prob THEN true ELSE false END AS has_feature,
  random() AS prob FROM Features CROSS JOIN SafePlanets P
)
UPDATE Planet AS P SET wiki = wiki || (Probs.name || '=>' ||
   CASE WHEN prob >= 0.5 THEN '1' ELSE '0' END)::HSTORE
FROM Probs WHERE Probs.planet_id=P.id AND has_feature;

-- ===========================================
-- Ачивки
INSERT INTO CommanderAchievements(commander_id, data)
SELECT id, ('{"rating": "' || rating::TEXT || '", "selfies": []}')::JSONB
FROM Commander;

UPDATE Planet SET wiki_jsonb = jsonb_build_object('features', hstore_to_jsonb(wiki));
UPDATE Planet SET wiki_jsonb = wiki_jsonb || '{"log": []}'::JSONB;

-- ===========================================
-- Журналы посещений
WITH Records AS (
  SELECT P.id AS planet_id,
      format('{"commander": "%s", "message": "%s"}', C.name, 'Cute dino!')::JSONB AS log_record
  FROM Flight F JOIN Planet P ON F.planet_id=P.id
  JOIN Commander C ON C.id = F.commander_id
  WHERE P.wiki_jsonb->'features'->>'dinosaurs' = '1'
  AND random()>0.99
)
UPDATE Planet AS P SET wiki_jsonb =
 jsonb_set(wiki_jsonb, '{log}', wiki_jsonb->'log' || log_record)
FROM Records R
WHERE R.planet_id = P.id;

-- И еще раз
WITH Records AS (
  SELECT P.id AS planet_id,
      format('{"commander": "%s", "message": "%s"}', C.name, 'Cute dino!')::JSONB AS log_record
  FROM Flight F JOIN Planet P ON F.planet_id=P.id
  JOIN Commander C ON C.id = F.commander_id
  WHERE P.wiki_jsonb->'features'->>'dinosaurs' = '1'
  AND random()>0.99
)
UPDATE Planet AS P SET wiki_jsonb =
 jsonb_set(wiki_jsonb, '{log}', wiki_jsonb->'log' || log_record)
FROM Records R
WHERE R.planet_id = P.id;

-- И еще
WITH Records AS (
  SELECT P.id AS planet_id,
      format('{"commander": "%s", "message": "%s"}', C.name, 'Cute dino!')::JSONB AS log_record
  FROM Flight F JOIN Planet P ON F.planet_id=P.id
  JOIN Commander C ON C.id = F.commander_id
  WHERE P.wiki_jsonb->'features'->>'dinosaurs' = '1'
  AND random()>0.99
)
UPDATE Planet AS P SET wiki_jsonb =
 jsonb_set(wiki_jsonb, '{log}', wiki_jsonb->'log' || log_record)
FROM Records R
WHERE R.planet_id = P.id;
