SELECT COUNT(p_id) + MAX(flight_cnt)
FROM (
    SELECT Planet.id as p_id, COUNT(Flight.id) as flight_cnt
    FROM Planet
    JOIN Flight
    ON (Flight.planet_id = Planet.id)
    WHERE Planet.galaxy = 2
    GROUP BY Planet.id
) Flight_res;
