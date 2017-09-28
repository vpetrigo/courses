SELECT Planet.name AS planet, PoliticalSystem.value AS psystem,
       rank() OVER _local AS local_rank, rank() OVER _global AS global_rank
FROM Planet
JOIN PoliticalSystem ON (PoliticalSystem.id = Planet.psystem_id)
LEFT JOIN Flight ON (Flight.planet_id = Planet.id)
GROUP BY Planet.id, PoliticalSystem.value
WINDOW _local AS (PARTITION BY PoliticalSystem.value ORDER BY COUNT(Flight.id) DESC),
_global AS (ORDER BY COUNT(Flight.id) DESC);
