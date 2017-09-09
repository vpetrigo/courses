SELECT Commander.name, Spacecraft.name, start_date 
FROM Flight 
JOIN Spacecraft ON (spacecraft_id = Spacecraft.id)
JOIN Commander ON (commander_id = Commander.id) WHERE commander_id = 6;
