CREATE OR REPLACE FUNCTION GetPaxCount(_planet_id INT, _class INT) RETURNS BIGINT AS $$
SELECT COUNT(Pax.id)
FROM Planet P 
JOIN Flight F     ON P.id=F.planet_id
JOIN Booking B    ON B.flight_id = F.id
JOIN Spacecraft S ON F.spacecraft_id = S.id
JOIN Pax          ON B.pax_id = Pax.id
WHERE S.class = _class AND P.id = _planet_id;
$$ LANGUAGE SQL;

SELECT Price.planet_id, 
       Price.spacecraft_class, 
       Price.price * GetPaxCount(Price.planet_id, Price.spacecraft_class) FROM Price;
