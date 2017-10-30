DROP TABLE IF EXISTS Booking;
DROP TABLE IF EXISTS Price;
DROP TABLE IF EXISTS Flight;
DROP TABLE IF EXISTS Planet;
DROP TABLE IF EXISTS Government;
DROP TABLE IF EXISTS Commander;
DROP TABLE IF EXISTS Spacecraft;
DROP TABLE IF EXISTS Pax;
DROP TYPE IF EXISTS Race;
DROP TYPE IF EXISTS Rating;

CREATE OR REPLACE FUNCTION GenerateSchema() RETURNS VOID AS $$
BEGIN
-- Справочник политических строев
CREATE TABLE Government(id SERIAL PRIMARY KEY, value TEXT UNIQUE);

-- Планета, её название, расстояние до Земли, политический строй
CREATE TABLE Planet(
  id SERIAL PRIMARY KEY,
  name TEXT UNIQUE,
  distance NUMERIC(5,2),
  government_id INT REFERENCES Government);

-- Значения рейтинга пилотов
CREATE TYPE Rating AS ENUM('Harmless', 'Poor', 'Average', 'Competent', 'Dangerous', 'Deadly', 'Elite');

-- Пилот корабля
CREATE TABLE Commander(
  id SERIAL PRIMARY KEY,
  name TEXT UNIQUE,
  rating Rating);

-- Космический корабль, вместимость пассажиров и класс корабля
CREATE TABLE Spacecraft(
  id SERIAL PRIMARY KEY,
  capacity INT CHECK(capacity > 0),
  name TEXT UNIQUE,
  class INT CHECK(class BETWEEN 1 AND 3));

-- Полет на планету в означеную дату, выполняемый кораблем, пилотируемый капитаном
CREATE TABLE Flight(id INT PRIMARY KEY,
  spacecraft_id INT REFERENCES Spacecraft,
  commander_id INT REFERENCES Commander,
  planet_id INT REFERENCES Planet,
  date DATE
);

-- Стоимость полета до планеты на корабле означенного класса
CREATE TABLE Price(
  planet_id INT REFERENCES Planet,
  spacecraft_class INT CHECK(spacecraft_class BETWEEN 1 AND 3),
  price INT CHECK(price>0),
  UNIQUE(planet_id, spacecraft_class));

-- Раса пассажира
CREATE TYPE Race AS ENUM('Elves', 'Men', 'Trolls');

-- Пассажир
CREATE TABLE Pax(
  id INT PRIMARY KEY,
  name TEXT,
  race Race);

-- Резервирование места на полет
CREATE TABLE Booking(
  ref_num TEXT PRIMARY KEY,
  pax_id INT REFERENCES Pax,
  flight_id INT REFERENCES Flight);
END;
$$ LANGUAGE plpgsql;

SELECT GenerateSchema();
