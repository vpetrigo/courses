CREATE INDEX flight_date_idx ON Flight(date);
CREATE INDEX booking_flight_idx ON Booking(flight_id);
----
WITH spec_date_flight AS (
    SELECT F.id, C.name
    FROM Flight F
    JOIN Commander C ON F.commander_id = C.id
    WHERE (F.date BETWEEN '2084-04-01' AND '2084-05-01') AND name = _commander_name
),
men_only AS (
    SELECT id AS men_id FROM Pax WHERE race = 'Men'
),
booking_for_flight AS (
    SELECT S.id, B.pax_id, S.name
    FROM Booking B JOIN spec_date_flight S ON B.flight_id = S.id
)
SELECT id, name, COUNT(*)::INT AS pax_count 
FROM booking_for_flight bff JOIN men_only mo ON mo.men_id = bff.pax_id 
GROUP BY id, name HAVING (COUNT(*) > _pax_count);
