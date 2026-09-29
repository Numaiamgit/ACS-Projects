import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error, r2_score
import joblib

train_df = pd.read_csv("train.csv")
test_df = pd.read_csv("test.csv")

def adauga_coloana_weekend(df):
    data_baza = datetime(2026, 5, 27)
    este_weekend = []
    for zile in df["zile_pana_la_plecare"]:
        if pd.isna(zile):
            este_weekend.append(0)
            continue
        data_zbor = data_baza + pd.Timedelta(days=int(zile))
        if data_zbor.weekday() in [4, 5, 6]:
            este_weekend.append(1)
        else:
            este_weekend.append(0)
    df["este_weekend"] = este_weekend
    return df

train_df = adauga_coloana_weekend(train_df)
test_df = adauga_coloana_weekend(test_df)

train_df['durata_minute'].fillna(train_df['durata_minute'].mean(), inplace=True)
test_df['durata_minute'].fillna(test_df['durata_minute'].mean(), inplace=True)

train_df['pret_bilet'].fillna(train_df['pret_bilet'].mean(), inplace=True)
test_df['pret_bilet'].fillna(test_df['pret_bilet'].mean(), inplace=True)

train_df['zile_pana_la_plecare'].fillna(train_df['zile_pana_la_plecare'].mean(), inplace=True)
test_df['zile_pana_la_plecare'].fillna(test_df['zile_pana_la_plecare'].mean(), inplace=True)

train_df['numar_escale'].fillna(train_df['numar_escale'].mode()[0], inplace=True)
test_df['numar_escale'].fillna(test_df['numar_escale'].mode()[0], inplace=True)

train_df['nume_companie'].fillna(train_df['nume_companie'].mode()[0], inplace=True)
test_df['nume_companie'].fillna(test_df['nume_companie'].mode()[0], inplace=True)

train_df['oras_plecare'].fillna(train_df['oras_plecare'].mode()[0], inplace=True)
test_df['oras_plecare'].fillna(test_df['oras_plecare'].mode()[0], inplace=True)

train_df['oras_sosire'].fillna(train_df['oras_sosire'].mode()[0], inplace=True)
test_df['oras_sosire'].fillna(test_df['oras_sosire'].mode()[0], inplace=True)

train_df['ora_plecare'].fillna(train_df['ora_plecare'].mode()[0], inplace=True)
test_df['ora_plecare'].fillna(test_df['ora_plecare'].mode()[0], inplace=True)

train_df['este_weekend'].fillna(train_df['este_weekend'].mode()[0], inplace=True)
test_df['este_weekend'].fillna(test_df['este_weekend'].mode()[0], inplace=True)

train_numeric = pd.get_dummies(train_df, columns=['nume_companie', 'oras_plecare', 'oras_sosire'])
test_numeric = pd.get_dummies(test_df, columns=['nume_companie', 'oras_plecare', 'oras_sosire'])

train_numeric, test_numeric = train_numeric.align(test_numeric, join='left', axis=1, fill_value=0)

X = train_numeric.drop(columns=['pret_bilet'])
y = train_numeric['pret_bilet']

X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=0.2, random_state=42)

model_regresie = RandomForestRegressor(random_state=42, n_estimators=100)
model_regresie.fit(X_train, y_train)

y_pred = model_regresie.predict(X_val)

mse = mean_squared_error(y_val, y_pred)
rmse = np.sqrt(mse)
r2 = r2_score(y_val, y_pred)

print(f"MSE: {mse:.2f}")
print(f"RMSE: {rmse:.2f}")
print(f"R2: {r2:.4f}")

plt.figure(figsize=(8, 6))
plt.scatter(y_val, y_pred, alpha=0.4, color='darkblue')
plt.plot([y_val.min(), y_val.max()], [y_val.min(), y_val.max()], 'r--', lw=2)
plt.title('Valori Reale vs. Valori Prezise pentru Pret Bilet')
plt.xlabel('Pret Real')
plt.ylabel('Pret Prezis de Model')
plt.show()

X_final_test = test_numeric.drop(columns=['pret_bilet'])
predictii_pret_final = model_regresie.predict(X_final_test)

test_df['pret_bilet'] = predictii_pret_final

joblib.dump(model_regresie, "model_preturi_avion.pkl")
joblib.dump(X.columns, "coloane_model.pkl")