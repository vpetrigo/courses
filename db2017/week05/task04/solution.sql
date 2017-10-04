WITH week_delta AS (
    SELECT *, share_price - first_value(share_price) OVER _week AS delta
    FROM StockQuotes
    WINDOW _week AS (PARTITION BY company ORDER BY week ROWS 1 PRECEDING)
),
stock_index AS (
    SELECT *, AVG(delta) OVER (PARTITION BY week) AS stock_index
    FROM week_delta
),
company_streak AS (
    SELECT *, SUM((delta > stock_index)::INT) OVER _success_week AS streak
    FROM stock_index
    WINDOW _success_week AS (PARTITION BY company ORDER BY week ROWS 2 PRECEDING)
)
SELECT company, COUNT(*) FROM company_streak WHERE streak = 3 GROUP BY company;
