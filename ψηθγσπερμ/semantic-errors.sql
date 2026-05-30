-- 1. Σφάλμα: Διπλή δημιουργία πίνακα (Ερώτημα 2α)
CREATE TABLE T1 (id int);
CREATE TABLE T1 (name varchar(10));

-- 2. Σφάλμα: Χρήση ανύπαρκτου πίνακα (Ερώτημα 2β)
SELECT * FROM MissingTable;

-- 3. Σφάλμα: Στήλη που δεν υπάρχει (Ερώτημα 2γ/δ)
SELECT non_existent_col FROM T1;

-- 4. Σφάλμα: Ασύμβατοι τύποι δεδομένων (Ερώτημα 2ε)
-- (Έστω ότι το id είναι int)
SELECT * FROM T1 WHERE id = 'string_value';

-- 5. Σφάλμα: LIMIT <= 0
SELECT * FROM T1 LIMIT 0;