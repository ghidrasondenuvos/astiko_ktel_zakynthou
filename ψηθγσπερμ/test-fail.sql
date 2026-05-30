CREATE TABLE Products (pid int, p_name varchar(30), price float);

-- ΛΑΘΟΣ 1: Ασύμβατος τύπος δεδομένων (Σύγκριση INT με String)
SELECT * FROM Products WHERE pid = 'error_id';

-- ΛΑΘΟΣ 2: Χρήση στήλης που δεν υπάρχει
SELECT category FROM Products;

-- ΛΑΘΟΣ 3: Χρήση πίνακα που δεν έχει δημιουργηθεί (προκαλεί σφάλμα στον FROM)
SELECT * FROM NonExistentTable;