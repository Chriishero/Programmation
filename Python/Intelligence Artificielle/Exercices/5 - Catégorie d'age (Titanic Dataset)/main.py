"""
Catégorie 0 : < 20 ans
Catégorie 1 : 20 - 30 ans
Catégorie 2 : 30 - 40 ans
Catégorie 3 : > 40 ans

On peut aussi utliser 'data.loc()'
"""

import numpy as np
import pandas as pd

data  = pd.read_excel("titanic.xls")

data[data['age'] < 20] = 0
data[(data['age'] >= 20) & (data['age'] <= 30)] = 1
data[(data['age'] > 30) & (data['age'] <= 40)] = 2
data[data['age'] > 40] = 3
data = data.dropna(axis=0)

print(data['age'])
print(data['age'].value_counts())