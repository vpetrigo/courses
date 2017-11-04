CREATE INDEX idx_booking_flight_id ON Booking(flight_id);
CREATE INDEX idx_flight_date_commander_id ON Flight(date, commander_id);
----
SELECT F.id AS flight_id, C.name AS commander_name, COUNT(*)::INT AS pax_count
FROM Commander C
JOIN Flight F ON F.commander_id	= C.id
JOIN Booking B ON B.flight_id = F.id
JOIN Pax P ON P.id = B.pax_id
WHERE P.race = 'Men' AND F.date BETWEEN '2084-04-01' AND '2084-05-01' AND C.name = _commander_name
GROUP BY F.id, C.name HAVING COUNT(*) > _pax_count;
