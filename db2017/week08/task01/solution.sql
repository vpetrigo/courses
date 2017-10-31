DROP INDEX IF EXISTS idx_booking_flight_id;
DROP INDEX IF EXISTS idx_flight_planet_spacecraft;

CREATE INDEX idx_booking_flight_id ON Booking(flight_id);
CREATE INDEX idx_flight_planet_spacecraft ON Flight(planet_id, spacecraft_id);
----
SELECT COUNT(1)
FROM Flight F JOIN Spacecraft S ON F.spacecraft_id = S.id
JOIN Planet P ON F.planet_id = P.id
JOIN Booking B ON F.id = B.flight_id
WHERE S.capacity<_capacity AND S.class=1
AND P.name=_planet_name;
