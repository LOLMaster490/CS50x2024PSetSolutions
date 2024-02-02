SELECT title FROM movies WHERE id IN
(SELECT movies.id FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON people.id = stars.person_id WHERE people.id IN (SELECT id FROM people WHERE name = 'Jennifer Lawrence'))
AND id IN
(SELECT movies.id FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON people.id = stars.person_id WHERE people.id IN (SELECT id FROM people WHERE name = 'Bradley Cooper'));
