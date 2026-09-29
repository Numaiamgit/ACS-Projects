import requests
import pandas as pd
from sklearn.model_selection import train_test_split
from datetime import datetime, timedelta
import time

LISTA_CHEI_KIWI = [
    "e95fd76547mshf87351c3fd82070p191fabjsn6e69a5147fae",
    "bc310d097bmsh0c29bd3303fb649p1a60f3jsn4f3d8bdfa5e6"
]

url = "https://kiwi-com-cheap-flights.p.rapidapi.com/one-way"
data_curenta = datetime.now()

aeroport_plecare = "OTP"
destinatii_capitale = ["LHR", "CDG", "FCO", "BCN", "AMS", "FRA", "VIE"]

data_start = datetime(2026, 6, 20)
data_final = datetime(2026, 8, 23)

date_consecutive = []
zi_index = data_start
while zi_index <= data_final:
    date_consecutive.append(zi_index)
    zi_index += timedelta(days=1)

tabel_preturi = []
cereri_efectuate = 0
index_cheie_curenta = 0

for zi in date_consecutive:
    data_formatata_kiwi = zi.strftime("%d/%m/%Y")
    zile_ramase = (zi - data_curenta).days

    for dest in destinatii_capitale:
        if index_cheie_curenta >= len(LISTA_CHEI_KIWI):
            break

        headers = {
            "X-RapidAPI-Key": LISTA_CHEI_KIWI[index_cheie_curenta],
            "X-RapidAPI-Host": "kiwi-com-cheap-flights.p.rapidapi.com"
        }

        params = {
            "source": aeroport_plecare,
            "destination": dest,
            "date": data_formatata_kiwi,
            "currency": "EUR",
            "adults": "1",
            "cabinClass": "ECONOMY",
            "limit": "30"
        }

        try:
            cereri_efectuate += 1
            raspuns = requests.get(url, headers=headers, params=params, timeout=25)

            if raspuns.status_code == 200:
                date_brute = raspuns.json()
                oferte = date_brute.get("itineraries", [])

                zboruri_zi = 0
                for zbor in oferte:
                    try:
                        pret_real = float(zbor["price"]["amount"])

                        segmente = zbor["sector"]["sectorSegments"]
                        numar_escale = len(segmente) - 1

                        primul_segment = segmente[0]["segment"]
                        companie_nume = primul_segment["carrier"]["name"]

                        ora_local_str = primul_segment["source"]["localTime"]
                        ora_plecare = int(ora_local_str.split("T")[1].split(":")[0])

                        durata_secunde = zbor["sector"]["duration"]
                        durata_minute = float(durata_secunde / 60)

                        tabel_preturi.append({
                            "nume_companie": companie_nume,
                            "oras_plecare": aeroport_plecare,
                            "oras_sosire": dest,
                            "ora_plecare": ora_plecare,
                            "zile_pana_la_plecare": zile_ramase,
                            "durata_minute": durata_minute,
                            "numar_escale": numar_escale,
                            "pret_bilet": pret_real
                        })
                        zboruri_zi += 1
                    except Exception:
                        continue


            elif raspuns.status_code == 429:
                #Limita atinsa (429). Schimb cheia
                index_cheie_curenta += 1
                continue
            else:
                print(f"Eroare API (Cod {raspuns.status_code})")

            time.sleep(1.2)

        except Exception as e:
            print(f"Eroare retea: {e}")
            continue

    if index_cheie_curenta >= len(LISTA_CHEI_KIWI):
        break

print(f"Total randuri: {len(tabel_preturi)}")

if len(tabel_preturi) >= 700:
    df = pd.DataFrame(tabel_preturi).drop_duplicates().reset_index(drop=True)
    train_df, test_df = train_test_split(df, test_size=0.25, random_state=42)
    train_df.to_csv("train.csv", index=False)
    test_df.to_csv("test.csv", index=False)
else:
    print(f"Fail(<700 randuri)")