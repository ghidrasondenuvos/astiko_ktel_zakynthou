import pandas as pd
import matplotlib.pyplot as plt
import os

# Συγχρονισμός με το δικό σου ΑΜ
CSV_FILENAME = "courses_1100736.csv"

if not os.path.exists(CSV_FILENAME) or os.path.getsize(CSV_FILENAME) == 0:
    print("Το αρχείο δεδομένων είναι κενό ή δεν βρέθηκε.")
    exit()

df = pd.read_csv(CSV_FILENAME)

df["Διάρκεια"] = pd.to_numeric(df["Διάρκεια"], errors="coerce").fillna(0)
df["Κόστος"] = pd.to_numeric(df["Κόστος"], errors="coerce").fillna(0)

fig = plt.figure(figsize=(15, 10))
fig.suptitle("Στατιστική Ανάλυση & Οπτικοποίηση Εκπαιδευτικών Μαθημάτων", fontsize=16, fontweight="bold")

# --- 1. Γράφημα: Bar Chart ---
ax1 = plt.subplot(2, 2, 1)
df_longest = df.sort_values(by="Διάρκεια", ascending=False).head(5)
bars = ax1.bar(df_longest["Τίτλος μαθήματος"], df_longest["Διάρκεια"], color="#4CAF50", edgecolor="black")
ax1.set_title("1. Top 5 Μαθήματα σε Διάρκεια", fontsize=11, fontweight="bold")
ax1.set_xlabel("Όνομα Μαθήματος")
ax1.set_ylabel("Διάρκεια (ώρες)")
ax1.set_xticklabels(df_longest["Τίτλος μαθήματος"], rotation=20, ha="right", fontsize=8)
ax1.grid(axis="y", linestyle="--", alpha=0.5)

# --- 2. Γράφημα: Pie Chart ---
ax2 = plt.subplot(2, 2, 2)
diff_counts = df["Επίπεδο δυσκολίας"].value_counts()
ax2.pie(diff_counts, labels=diff_counts.index, autopct="%1.1f%%", colors=["#ff9999","#66b3ff","#99ff99"], startangle=140, 
        wedgeprops={"edgecolor":"black", "linewidth": 1})
ax2.set_title("2. Κατανομή Επιπέδου Δυσκολίας", fontsize=11, fontweight="bold")

# --- 3. Γράφημα: Line Plot ---
ax3 = plt.subplot(2, 1, 2)
df_trend = df_longest.sort_values(by="Διάρκεια")
ax3.plot(df_trend["Διάρκεια"], df_trend["Κόστος"], marker="o", linestyle="-", color="#FF9800", linewidth=2, label="Τάση Κόστος")
ax3.set_title("3. Συσχέτιση Κόστους και Διάρκειας (Στα 5 μεγαλύτερα μαθήματα)", fontsize=11, fontweight="bold")
ax3.set_xlabel("Διάρκεια μαθήματος (ώρες)")
ax3.set_ylabel("Κόστος μαθήματος ($)")

for _, row in df_trend.iterrows():
    ax3.annotate(row["Τίτλος μαθήματος"], (row["Διάρκεια"], row["Κόστος"]), textcoords="offset points", xytext=(0,10), ha="center", fontsize=8, fontweight="bold")

ax3.grid(True, linestyle="--", alpha=0.5)
ax3.legend()

plt.tight_layout(rect=[0, 0, 1, 0.95])
plt.show()