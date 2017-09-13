DECLARE
    avg_score integer;
    score_count integer;
-- YOUR CODE HERE
BEGIN
    IF EXISTS(SELECT * FROM PaperReviewing
              JOIN Paper ON (PaperReviewing.paper_id = Paper.id)
              JOIN Reviewer ON (PaperReviewing.reviewer_id = Reviewer.id)
              WHERE paper_id = _paper_id and reviewer_id = _reviewer_id and accepted IS NULL)
       AND _score BETWEEN 1 AND 7 THEN
           UPDATE PaperReviewing SET score = _score WHERE paper_id = _paper_id and reviewer_id = _reviewer_id;
       
       SELECT COUNT(paper_id), AVG(score) INTO score_count, avg_score FROM PaperReviewing WHERE paper_id = _paper_id AND score IS NOT NULL;
    
        IF score_count = 3 THEN
            UPDATE Paper SET accepted = (avg_score > 4) WHERE id = _paper_id;
        END IF;
    ELSE
        RAISE SQLSTATE 'DB017';
    END IF;
END;
