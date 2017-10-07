CREATE TABLE Location(id SERIAL, value TEXT);
CREATE TABLE Conference(id SERIAL, value TEXT);
CREATE TABLE Paper(id SERIAL, title TEXT, conference TEXT, location TEXT);

COPY Location FROM '/workspace/task2-location.csv' CSV;
COPY Conference FROM '/workspace/task2-conference.csv' CSV;

-- Генерирует 50000 случайных статей, поданных на 100 разных конференций
-- Данные генерируются так, что фактически выполняется зависимость Conference->Location
CREATE OR REPLACE FUNCTION GeneratePapers()
RETURNS integer AS $$
declare
  WORD1 TEXT[] := ARRAY['Creating', 'Destroying', 'Feeding', 'Constructing'];
  WORD2 TEXT[] := ARRAY['red', 'black', 'yellow', 'green', 'white', 'transparent'];
  WORD3 TEXT[] := ARRAY['round', 'square', 'triangle', 'straight', 'curly'];
  WORD4 TEXT[] := ARRAY['apples', 'horses', 'submarines', 'oranges', 'cats'];
  WORD5 TEXT[] := ARRAY['with', 'without', 'covered by'];
  WORD6 TEXT[] := ARRAY['iron', 'wood', 'wool', 'silk', 'proteins'];
  paper_title TEXT;
BEGIN
  CREATE TEMP TABLE ConferenceLocation ON COMMIT DROP AS
    SELECT Conference.*, ''::TEXT  AS location
    FROM Conference;

  FOR i IN 1..100 LOOP
    UPDATE ConferenceLocation SET location = (SELECT value FROM Location WHERE id=(SELECT (random()*50 + 0.5)::int)) WHERE id=i;
  END LOOP;
  FOR i IN 1..50000 LOOP
    paper_title := array_to_string(ARRAY[
        WORD1[(random()*4+0.5)::int],
        WORD2[(random()*6+0.5)::int],
        WORD3[(random()*5+0.5)::int],
        WORD4[(random()*5+0.5)::int],
        WORD5[(random()*3+0.5)::int],
        WORD6[(random()*5+0.5)::int]], ' ');
    INSERT INTO Paper(title, conference, location) SELECT paper_title, value, location FROM ConferenceLocation WHERE id=(SELECT (random()*100 + 0.5)::int);
  END LOOP;
  RETURN (SELECT COUNT(*) FROM Paper);
END;
$$ LANGUAGE plpgsql;

SELECT * FROM GeneratePapers();
