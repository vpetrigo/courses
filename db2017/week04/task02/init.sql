DROP TABLE IF EXISTS Conference;
DROP TABLE IF EXISTS ConferenceEvent;
DROP TABLE IF EXISTS Paper;
DROP TABLE IF EXISTS Reviewer;
DROP TABLE IF EXISTS PaperReviewing;

-- Внешние ключи закомментированы намеренно.

CREATE TABLE Conference(
  id INT PRIMARY KEY, name TEXT UNIQUE);

CREATE TABLE ConferenceEvent(
  id SERIAL PRIMARY KEY,
 conference_id INT, -- REFERENCES Conference,
 year INT,
 UNIQUE(conference_id, year));

CREATE TABLE Paper(
  id INT PRIMARY KEY,
  event_id INT, -- REFERENCES ConferenceEvent,
  title TEXT,
  accepted BOOLEAN
);

CREATE TABLE Reviewer(
  id INT PRIMARY KEY,
  email TEXT UNIQUE,
  name TEXT
);

CREATE TABLE PaperReviewing(
  paper_id INT, -- REFERENCES Paper,
  reviewer_id INT, -- REFERENCES Reviewer,
  score INT,
  UNIQUE(paper_id, reviewer_id)
);

INSERT INTO Conference(id, name) VALUES (1, 'SIGMOD'), (2, 'VLDB');
INSERT INTO ConferenceEvent(conference_id, year) VALUES (1, 2015), (1, 2016), (2, 2016);
INSERT INTO Reviewer(id, email, name) VALUES
  (1, 'jennifer@stanford.edu', 'Jennifer Widom'),
  (2, 'donald@ethz.ch', 'Donald Kossmann'),
  (3, 'jeffrey@stanford.edu', 'Jeffrey Ullman'),
  (4, 'jeff@google.com', 'Jeffrey Dean'),
  (5, 'michael@mit.edu', 'Michael Stonebraker');

INSERT INTO Paper(id, event_id, title) VALUES
  (1, 1, 'Paper1'),
  (2, 2, 'Paper2'),
  (3, 2, 'Paper3'),
  (4, 3, 'Paper4');

INSERT INTO PaperReviewing(paper_id, reviewer_id) VALUES
  (1, 1), (1, 4), (1, 5),
  (2, 1), (2, 2), (2, 4),
  (3, 3), (3, 4), (3, 5),
  (4, 2), (4, 3), (4, 4);
