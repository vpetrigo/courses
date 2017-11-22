WITH danger_tags AS (
 SELECT unnest(akeys(slice(wiki, ARRAY['dinosaurs', 'weapons', 'pirates',
   'earthquakes', 'crime', 'mosquitoes']))) AS danger_tag
 FROM planet WHERE wiki->'danger' = '1'
 AND wiki ?| ARRAY['dinosaurs', 'weapons', 'pirates', 'earthquakes', 'crime', 'mosquitoes']
),
max_count AS (
 SELECT danger_tag AS tag, COUNT(*) AS count FROM danger_tags GROUP BY tag
)
SELECT tag, count FROM max_count WHERE count = (SELECT MAX(count) from max_count);
