import gradio as gr
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import joblib

try:
    model_regresie = joblib.load("model_preturi_avion.pkl")
    coloane_model = joblib.load("coloane_model.pkl")
except FileNotFoundError:
    print("Eroare: Nu am gasit fisierele .pkl.")
    exit()

companii_reale = [col.replace("nume_companie_", "") for col in coloane_model if col.startswith("nume_companie_")]
orase_reale = [col.replace("oras_sosire_", "") for col in coloane_model if col.startswith("oras_sosire_")]

durate_medii_zbor = {
    "VIE": 105,
    "FCO": 140,
    "FRA": 155,
    "CDG": 185,
    "BCN": 200,
    "AMS": 375,
    "LHR": 300
}

def interfata_predictie(nume_companie, oras_sosire, numar_escale, ora_plecare, zile_pana_la_plecare, este_weekend, pret_real_optional):

    date_numeric = pd.DataFrame(0, index=[0], columns=coloane_model)

    if 'zile_pana_la_plecare' in date_numeric.columns:
        date_numeric['zile_pana_la_plecare'] = int(zile_pana_la_plecare)

    if 'ora_plecare' in date_numeric.columns:
        date_numeric['ora_plecare'] = int(ora_plecare)

    if 'numar_escale' in date_numeric.columns:
        date_numeric['numar_escale'] = int(numar_escale)

    if 'este_weekend' in date_numeric.columns:
        date_numeric['este_weekend'] = 1 if este_weekend == "Da" else 0

    if 'durata_minute' in date_numeric.columns:
        date_numeric['durata_minute'] = durate_medii_zbor.get(oras_sosire, 140)

    col_companie = f"nume_companie_{nume_companie}"
    col_sosire = f"oras_sosire_{oras_sosire}"
    col_plecare = "oras_plecare_OTP"

    if col_companie in date_numeric.columns:
        date_numeric[col_companie] = 1
    if col_sosire in date_numeric.columns:
        date_numeric[col_sosire] = 1
    if col_plecare in date_numeric.columns:
        date_numeric[col_plecare] = 1

    pret_prezis = model_regresie.predict(date_numeric)[0]
    text_rezultat = f"Pretul estimat de model: {pret_prezis:.2f} EUR"

    fig, ax = plt.subplots(figsize=(6, 4))

    if pret_real_optional:
        try:
            pret_real = float(pret_real_optional)
            reziduu = pret_real - pret_prezis
            text_rezultat += f"\nPret de pe site: {pret_real:.2f} EUR\nReziduu (Eroare): {reziduu:.2f} EUR"

            sns.barplot(x=['Pret Prezis', 'Pret Real de pe Site'], y=[pret_prezis, pret_real], ax=ax, color='cornflowerblue')
            ax.set_ylabel('Pret (EUR)')
            ax.set_title(f'Analiza Reziduu curent: {reziduu:.2f} EUR')
        except ValueError:
            text_rezultat += "\nTe rog introdu un numar valid in campul de pret real."
    else:
        sns.barplot(x=['Pret Estimat'], y=[pret_prezis], ax=ax, color='teal')
        ax.set_ylabel('Pret (EUR)')
        ax.set_title(f'Predictie adaptata pentru {oras_sosire} ({durate_medii_zbor.get(oras_sosire, 140)} min)')

    plt.tight_layout()
    return text_rezultat, fig

interfata = gr.Interface(
    fn=interfata_predictie,
    inputs=[
        gr.Dropdown(choices=companii_reale, label="Compania Aeriana"),
        gr.Dropdown(choices=orase_reale, label="Aeroport Destinatie (Cod IATA)"),
        gr.Dropdown(choices=["0", "1"], label="Numar Escale"),
        gr.Slider(minimum=0, maximum=23, step=1, label="Ora de Plecare (0-23)"),
        gr.Number(label="Zile ramase pana la zbor", value=14),
        gr.Radio(choices=["Da", "Nu"], label="Zborul este in Weekend?"),
        gr.Textbox(label="Pret Real de pe site (Optional pentru reziduuri)", placeholder="Ex: 120")
    ],
    outputs=[
        gr.Textbox(label="Rezultat Predictie"),
        gr.Plot(label="Vizualizare Grafica Regresie")
    ],
    title="Predictie a Preturilor pentru Bilete de Avion",
    description="Modelul foloseste durate corelate istoric cu destinatia aleasa pentru a evita predictiile blocate.",
    flagging_mode="never"
)

if __name__ == "__main__":
    interfata.launch(share=False)