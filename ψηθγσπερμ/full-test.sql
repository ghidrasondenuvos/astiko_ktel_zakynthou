-- Δημιουργία πινάκων
CREATE TABLE Students (id int, name varchar(50), gpa float);
CREATE TABLE Courses (cid int, title varchar(100), credits int);

-- SELECT με JOIN, AS, WHERE, GROUP BY, ORDER BY, LIMIT
SELECT S.name, C.title 
FROM Students AS S 
JOIN Courses AS C ON S.id = C.cid 
WHERE S.gpa >= 3.0 
  AND S.id NOT IN (1, 2, 3) 
  AND (S.name = 'Alice' OR S.name = 'Bob')
GROUP BY S.name, C.title 
ORDER BY S.gpa 
LIMIT 10;