--
----
SELECT P.planet_id, P.spacecraft_class, P.price * COUNT(*)
    FROM Price P JOIN Flight F USING(planet_id)
    JOIN Booking B ON B.flight_id = F.id
    JOIN Spacecraft S ON S.id=F.spacecraft_id AND S.class=P.spacecraft_class
    GROUP BY P.planet_id, P.spacecraft_class, P.price;
