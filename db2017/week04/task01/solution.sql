SELECT Conference.name, ConferenceEvent.id, ConferenceEvent.year, COUNT(Paper.id) as total_papers, AVG(Paper.accepted::INT) as acceptance_ratio FROM ConferenceEvent
JOIN Paper ON (Paper.event_id = ConferenceEvent.id)
JOIN Conference on (Conference.id = ConferenceEvent.conference_id)
GROUP BY ConferenceEvent.id, Conference.name
HAVING COUNT(Paper.id) > 5 and AVG(Paper.accepted::INT) > 0.75;
