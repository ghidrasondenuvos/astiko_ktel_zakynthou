Επιτυχία:

CREATE TABLE Students (id int);
CREATE TABLE Courses (id int); -- Οκ: Διαφορετικά ονόματα

Αποτυχία:

CREATE TABLE Students (id int);
CREATE TABLE Students (name varchar(10)); -- ΣΦΑΛΜΑ: Ο πίνακας Students υπάρχει ήδη!

Επιτυχία:

CREATE TABLE Users (id int);
SELECT id FROM Users; -- Οκ: Ο πίνακας Users έχει δημιουργηθεί

Αποτυχία:

SELECT id FROM UnknownTable; -- ΣΦΑΛΜΑ: Ο πίνακας UnknownTable δεν έχει δημιουργηθεί!

Επιτυχία:

CREATE TABLE Products (pid int, p_name varchar(20)); -- Οκ: Διαφορετικές στήλες

Αποτυχία:

CREATE TABLE Products (pid int, pid float); -- ΣΦΑΛΜΑ: Η στήλη pid ορίζεται δύο φορές!

Επιτυχία:

CREATE TABLE Employees (emp_id int, salary float);
SELECT salary FROM Employees WHERE emp_id = 1; -- Οκ: Οι στήλες υπάρχουν

Αποτυχία:

CREATE TABLE Employees (emp_id int, salary float);
SELECT bonus FROM Employees; -- ΣΦΑΛΜΑ: Η στήλη bonus δεν υπάρχει στον πίνακα Employees!

Επιτυχία (Συμβατότητα):

CREATE TABLE Inventory (item_id int, price float, category varchar(10));
SELECT * FROM Inventory WHERE item_id = 100 AND price = 20.5; -- Οκ: INT=INT, FLOAT=FLOAT
SELECT * FROM Inventory WHERE category IN ('Electronics', 'Books'); -- Οκ: VARCHAR IN (VARCHARs)

Αποτυχία (Ασυμβατότητα):

-- 1. Σφάλμα σύγκρισης INT με STRING
SELECT * FROM Inventory WHERE item_id = 'invalid_id'; 

-- 2. Σφάλμα στο IN (VARCHAR στήλη με INT στη λίστα)
SELECT * FROM Inventory WHERE category IN (1, 2); 