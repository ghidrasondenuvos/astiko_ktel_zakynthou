import csv

# Συγχρονισμός με το δικό σου ΑΜ για τον έλεγχο των δεδομένων
filename = "courses_1100736.csv"

try:
    with open(filename, newline='', encoding="utf-8-sig") as csvfile:
        reader = csv.DictReader(csvfile)
        print("Ενημερωμένες Στήλες Μαθημάτων:", reader.fieldnames)
        print("\n--- Περιεχόμενο Αρχείου (Γραμμή ανά Γραμμή) ---\n")
        for i, row in enumerate(reader, start=1):
            print(f"{i}. {row}")
except FileNotFoundError:
    print(f"⚠️ Το αρχείο '{filename}' δεν έχει δημιουργηθεί ακόμα.")
    print("👉 Παρακαλώ τρέξτε πρώτα το 'course_manager.py' και πατήστε το κουμπί 'Χειροκίνητη Συλλογή'.")