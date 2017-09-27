-- Stepik Course.
-- database sample for task 5.3
 
DROP TABLE IF EXISTS Flight;
DROP TABLE IF EXISTS Planet;
DROP TABLE IF EXISTS PoliticalSystem;
 
-- Справочник политических строев
CREATE TABLE PoliticalSystem(
  id SERIAL PRIMARY KEY,
  VALUE TEXT UNIQUE
  );
 
-- Планета, её название, расстояние до Земли, политический строй
CREATE TABLE Planet(
  id SERIAL PRIMARY KEY,
  NAME TEXT UNIQUE,
  distance NUMERIC(5,2),
  psystem_id INT REFERENCES PoliticalSystem
  );
 
-- Полет на планету в означенную дату
CREATE TABLE Flight(
  id SERIAL INT PRIMARY KEY,
  planet_id INT REFERENCES Planet,
  DATE DATE
  );
 
 
-- Table PoliticalSystem
INSERT INTO PoliticalSystem (VALUE) VALUES ('Anarchy');
INSERT INTO PoliticalSystem (VALUE) VALUES ('Monarchy');
INSERT INTO PoliticalSystem (VALUE) VALUES ('Parliamentary republic');
INSERT INTO PoliticalSystem (VALUE) VALUES ('Democracy');
 
-- Table Planet
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Bioflex',      89.08,  1);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Goldenflex',  131.70,  2);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Opeholding',   90.44,  2);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Tanzone',      52.83,  3);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Flexplus',    105.87,  3);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Volholdings',   5.99,  3);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Hotla',       195.26,  4);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Trioline',     15.58,  4);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Stimex',      164.43,  4);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Hotanbam',    126.37,  3);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Rancare',      57.87,  1);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Doubleice',   131.20,  3);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Geocom',      114.40,  4);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Techiplus',   164.72,  2);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Carehigh',    172.01,  2);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Medredfan',   130.84,  3);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Dandindox',    13.37,  4);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Kanron',        3.10,  3);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Tanway',       75.28,  1);
INSERT INTO planet (NAME, distance, psystem_id) VALUES ('Vilakix',      40.57,  4);
 
-- Table Flight
INSERT INTO flight (planet_id, DATE) VALUES (2,   '2047-10-28');
INSERT INTO flight (planet_id, DATE) VALUES (5,   '2047-12-16');
INSERT INTO flight (planet_id, DATE) VALUES (13,  '2048-02-20');
INSERT INTO flight (planet_id, DATE) VALUES (6,   '2048-03-02');
INSERT INTO flight (planet_id, DATE) VALUES (12,  '2048-03-20');
INSERT INTO flight (planet_id, DATE) VALUES (9,   '2048-03-26');
INSERT INTO flight (planet_id, DATE) VALUES (14,  '2048-05-01');
INSERT INTO flight (planet_id, DATE) VALUES (3,   '2048-05-22');
INSERT INTO flight (planet_id, DATE) VALUES (6,   '2048-05-28');
INSERT INTO flight (planet_id, DATE) VALUES (6,   '2048-06-04');
INSERT INTO flight (planet_id, DATE) VALUES (4,   '2048-06-17');
INSERT INTO flight (planet_id, DATE) VALUES (2,   '2048-08-10');
INSERT INTO flight (planet_id, DATE) VALUES (4,   '2048-08-18');
INSERT INTO flight (planet_id, DATE) VALUES (6,   '2048-09-03');
INSERT INTO flight (planet_id, DATE) VALUES (5,   '2048-10-08');
INSERT INTO flight (planet_id, DATE) VALUES (8,   '2048-10-20');
INSERT INTO flight (planet_id, DATE) VALUES (9,   '2048-11-23');
INSERT INTO flight (planet_id, DATE) VALUES (7,   '2048-12-17');
INSERT INTO flight (planet_id, DATE) VALUES (13,  '2048-12-23');
INSERT INTO flight (planet_id, DATE) VALUES (19,  '2048-12-28');
INSERT INTO flight (planet_id, DATE) VALUES ( 3,  '2049-02-28');
INSERT INTO flight (planet_id, DATE) VALUES (11,  '2049-03-28');
INSERT INTO flight (planet_id, DATE) VALUES ( 5,  '2049-03-29');
INSERT INTO flight (planet_id, DATE) VALUES ( 1,  '2049-04-15');
INSERT INTO flight (planet_id, DATE) VALUES (10,  '2049-04-16');
INSERT INTO flight (planet_id, DATE) VALUES (10,  '2049-04-16');
INSERT INTO flight (planet_id, DATE) VALUES (15,  '2049-04-17');
INSERT INTO flight (planet_id, DATE) VALUES ( 2,  '2049-04-17');
INSERT INTO flight (planet_id, DATE) VALUES ( 5,  '2049-04-18');
INSERT INTO flight (planet_id, DATE) VALUES (10,  '2049-04-19');
