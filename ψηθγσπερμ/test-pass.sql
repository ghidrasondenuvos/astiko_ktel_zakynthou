-- Δημιουργία πινάκων για τις δοκιμές
CREATE TABLE Students (id int, name varchar(50), gpa float);
CREATE TABLE Courses (id int, course_name varchar(50));

-- Επιτυχημένο ερώτημα SELECT
SELECT S.name, C.course_name 
FROM Students AS S 
JOIN Courses AS C ON S.id = C.id 
WHERE S.gpa >= 3.0 AND S.name IN ('Alice', 'Bob') 
GROUP BY S.name, C.course_name 
ORDER BY S.gpa 
LIMIT 10;