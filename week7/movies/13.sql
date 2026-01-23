-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred

SELECT p1.name FROM people p1
JOIN stars s1 ON s1.person_id = p1.id
WHERE s1.movie_id IN
( SELECT s2.movie_id FROM stars s2
  JOIN people p2 ON s2.person_id = p2.id
  WHERE p2.name = 'Kevin Bacon' AND p2.birth = 1958
)
AND p1.name != 'Kevin Bacon' ;
