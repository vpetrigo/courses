select conference from paper where paper.conference not in (select value from conference) union select conference from paper group by conference having count(distinct location) > 1;
