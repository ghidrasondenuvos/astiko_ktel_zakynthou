import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

CSV_FILENAME = "courses_1100736.csv"

if not os.path.exists(CSV_FILENAME) or os.path.getsize(CSV_FILENAME) == 0:
    print("Το αρχείο δεδομένων είναι κενό ή δεν βρέθηκε. Παρακαλώ εκτελέστε πρώτα τη συλλογή.")
    exit()

try:
    df = pd.read_csv(CSV_FILENAME)
except Exception as e:
    print(f"Σφάλμα κατά την ανάγνωση του αρχείου: {str(e)}")
    exit()

df["Διάρκεια"] = pd.to_numeric(df["Διάρκεια"], errors="coerce").fillna(0)
df["Κόστος"] = pd.to_numeric(df["Κόστος"], errors="coerce").fillna(0)

# Εξαίρεση των ανενεργών μαθημάτων
df = df[~df["Τίτλος μαθήματος"].astype(str).str.contains("ΑΝΕΝΕΡΓΟ", na=False)]

if df.empty:
    print("Δεν υπάρχουν έγκυρα δεδομένα για οπτικοποίηση.")
    exit()

# Εφαρμογή της παλέτας Base16 Icy Dark
plt.rcParams['backend'] = 'TkAgg'
plt.rcParams['font.family'] = 'monospace'
plt.rcParams['text.color'] = '#b3ebf2'       
plt.rcParams['axes.labelcolor'] = '#16c1d9'   
plt.rcParams['xtick.color'] = '#109cb0'       
plt.rcParams['ytick.color'] = '#109cb0'       
plt.rcParams['figure.facecolor'] = '#021012'  
plt.rcParams['axes.facecolor'] = '#021012'    

fig = plt.figure(figsize=(12, 6.5))
fig.suptitle("Στατιστική ανάλυση εκπαιδευτικών μαθημάτων", fontsize=12, fontweight="bold", color="#16c1d9")

# Απομόνωση των 5 μεγαλύτερων μαθημάτων βάσει διάρκειας
df_longest = df.sort_values(by="Διάρκεια", ascending=False).head(5).copy()
df_longest["Καθαρός Τίτλος"] = df_longest["Τίτλος μαθήματος"].apply(lambda x: str(x)[:18] + "..." if len(str(x)) > 18 else str(x))

# --- 1. Γράφημα: Κατακόρυφο Bar Chart
# Άξονας Χ: Ονόματα μαθημάτων, Άξονας Υ: Διάρκεια σε ώρες
ax1 = plt.subplot(2, 2, 1)
x_positions = np.arange(len(df_longest))

bars = ax1.bar(x_positions, df_longest["Διάρκεια"], color="#00bcd4", edgecolor="#16c1d9", linewidth=1, width=0.45)
ax1.set_title("Top 5 μαθήματα σε διάρκεια", fontsize=9, fontweight="bold", color="#109cb0")
ax1.set_ylabel("Διάρκεια σε ώρες", fontsize=8)

# Στοίχιση των ονομάτων στον άξονα Χ με σωστή κλίση
ax1.set_xticks(x_positions)
ax1.set_xticklabels(df_longest["Καθαρός Τίτλος"], fontsize=8, rotation=22, ha="right")
ax1.grid(axis="y", linestyle="--", color="#052e34", alpha=0.5)

if not df_longest["Διάρκεια"].empty:
    ax1.set_ylim(0, df_longest["Διάρκεια"].max() * 1.15)

# --- 2. Γράφημα: Pie Chart ---
ax2 = plt.subplot(2, 2, 2)
diff_counts = df["Επίπεδο δυσκολίας"].value_counts()
icy_colors = ["#16c1d9", "#4dd0e1", "#80deea", "#26c6da"]

wedges, texts, autotexts = ax2.pie(diff_counts, labels=diff_counts.index, autopct="%1.1f%%", colors=icy_colors[:len(diff_counts)], startangle=140, 
        textprops={'fontsize': 8, 'color': '#b3ebf2'}, wedgeprops={"edgecolor":"#021012", "linewidth": 1})
ax2.set_title("Κατανομή επιπέδου δυσκολίας", fontsize=9, fontweight="bold", color="#109cb0")

for autotext in autotexts:
    autotext.set_color('black')
    autotext.set_weight('bold')

# --- 3. Γράφημα: Line Plot 
# Συσχέτιση Κόστους και Διάρκειας για τα 5 μεγαλύτερα επί πληρωμή μαθήματα
ax3 = plt.subplot(2, 1, 2)
df_paid = df[df["Κόστος"] > 0].sort_values(by="Διάρκεια", ascending=False).head(5).copy()

if len(df_paid) >= 2:
    # Ταξινόμηση κατά διάρκεια (αύξουσα) για να σχεδιαστεί η γραμμή ομαλά από αριστερά προς τα δεξιά
    df_paid = df_paid.sort_values(by="Διάρκεια")
    df_paid["Καθαρός Τίτλος"] = df_paid["Τίτλος μαθήματος"].apply(lambda x: str(x)[:20] + "..." if len(str(x)) > 20 else str(x))
    
    ax3.plot(df_paid["Διάρκεια"], df_paid["Κόστος"], marker="o", linestyle="-", color="#4dd0e1", linewidth=1.6, label="Τάση κόστους")
    ax3.set_title("Συσχέτιση κόστους και διάρκειας στα μεγαλύτερα μαθήματα με πληρωμή", fontsize=9, fontweight="bold", color="#109cb0")
    ax3.set_xlabel("Διάρκεια μαθήματος σε ώρες", fontsize=8)
    ax3.set_ylabel("Κόστος σε δολάρια", fontsize=8)

    x_min, x_max = df_paid["Διάρκεια"].min(), df_paid["Διάρκεια"].max()
    y_min, y_max = df_paid["Κόστος"].min(), df_paid["Κόστος"].max()

    x_buffer = (x_max - x_min) * 0.15 if x_max != x_min else 6.0
    y_buffer = (y_max - y_min) * 0.15 if y_max != y_min else 12.0

    ax3.set_xlim(max(0, x_min - x_buffer), x_max + x_buffer)
    ax3.set_ylim(max(0, y_min - y_buffer), y_max + y_buffer)

    for _, row in df_paid.iterrows():
        ax3.annotate(row["Καθαρός Τίτλος"], (row["Διάρκεια"], row["Κόστος"]), textcoords="offset points", xytext=(0,8), ha="center", fontsize=7, color="#b3ebf2")
else:
    ax3.text(0.5, 0.5, "Απαιτούνται τουλάχιστον 2 επί πληρωμή μαθήματα στη βάση για τη σχεδίαση του Line Plot.", ha='center', va='center', fontsize=9, color='#b3ebf2')
    ax3.set_title("Συσχέτιση κόστους και διάρκειας στα μεγαλύτερα μαθήματα με πληρωμή", fontsize=9, fontweight="bold", color="#109cb0")

ax3.grid(True, linestyle="--", color="#052e34", alpha=0.5)
ax3.legend(fontsize=8, facecolor="#052e34", edgecolor="#095b67")

plt.tight_layout(pad=2.2)
plt.show()