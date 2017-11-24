TH planets_with_dino AS (
    SELECT id, name, jsonb_array_elements(wiki_jsonb->'log')->>'commander' AS commander_name
    FROM Planet
    WHERE wiki_jsonb#>'{features, dinosaurs}'->>0 = '1'
),
dino_commanders_id AS (
    SELECT C.id AS commander_id, PWD.name, jsonb_build_object('with', 'dino', 'planet', PWD.name) AS selfie FROM Commander C
    JOIN planets_with_dino PWD
    ON PWD.commander_name = C.name
)
SELECT commander_id, jsonb_insert(CA.data, '{selfies, 0}', DCI.selfie)
FROM CommanderAchievements CA
JOIN dino_commanders_id DCI
USING(commander_id);
