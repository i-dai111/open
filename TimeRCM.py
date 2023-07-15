import random

!pip install scipy

!pip install tslearn
!pip install fastdtw

from fastdtw import fastdtw
from scipy.spatial.distance import euclidean

import numpy as np
from scipy.spatial.distance import euclidean
from fastdtw import fastdtw


import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from tslearn.metrics import dtw
import matplotlib.pyplot as plt
from tslearn.clustering import TimeSeriesKMeans

import inspect
import numpy

#Timeseries式のRCMを作る

from google.colab import drive
drive.mount('/content/drive')

import numpy as np
import pandas as pd
seed = 111
input_path = "/content/drive/My Drive/data.csv"
df = pd.read_csv(input_path, header=0)
df.head(5)

X_train = df.loc[:, df.columns != 'time']

distance, path = fastdtw(X_train[0:1].values, X_train[1:2].values, dist=euclidean)

print(distance)
print(path)

import numpy as np
from scipy.spatial.distance import euclidean
from fastdtw import fastdtw
from matplotlib import pyplot as plt
# 異なる2種類のデータを定義
x = X_train[0:1].values.reshape(-1, 1)
y = X_train[4:5].values.reshape(-1, 1)
# DTWを計算
distance, path = fastdtw(x, y, dist=euclidean)
print("DTW距離:", distance)
plt.plot(x, label='x')
plt.plot(y, label='y')
# 各点がどのように対応しているかを図示する
for x_, y_ in path:
  plt.plot([x_, y_], [x[x_], y[y_]], color='gray', linestyle='dotted', linewidth=1)
plt.legend()
plt.title('Our two temporal sequences')
plt.show()

a,b=X_train.values.shape
for i in range(a):
  for j in range(a-i-1):
    x = X_train[i:i+1].values.reshape(-1, 1)
    y = X_train[a-j-1:a-j].values.reshape(-1, 1)
    distance, path = fastdtw(x, y, dist=euclidean)
    print("DTW距離:", distance)
    plt.plot(x, label='x')
    plt.plot(y, label='y')
    # 各点がどのように対応しているかを図示する
    for x_, y_ in path:
      plt.plot([x_, y_], [x[x_], y[y_]], color='gray', linestyle='dotted', linewidth=1)
    plt.legend()
    plt.title('Our two temporal sequences')
    plt.show()

#C=3としてデータの中からランダムにクラスタ中心を選ぶ
#（kmeans++はあとで）

center=np.arange(a)
np.random.shuffle(center)
C=3
#print(center)
dd=np.empty(a)
for i in range(a):
  x=X_train[center[0]:center[0]+1].values.reshape(-1, 1)
  y=X_train[i:i+1].values.reshape(-1, 1)
  distance, path = fastdtw(x, y, dist=euclidean)
  dd[i]=distance**2
#print(dd)
p=np.empty(a)
for i in range(a):
  p[i]=dd[i]/dd.sum()
#print(p)
CENTER=np.random.choice(np.arange(a),p=p)
#print(p[CENTER])
center=center[center!=CENTER]
center=np.insert(center,1,CENTER)
#print(center)

count=1
for k in range(C-2):
  count+=count
  dd=np.full(a,10000000000)
  for i in range(a):
    for j in range(count):
      x=X_train[center[j]:center[j]+1].values.reshape(-1, 1)
      y=X_train[i:i+1].values.reshape(-1, 1)
      distance, path = fastdtw(x, y, dist=euclidean)
      print(distance)
      if(dd[i]>=distance**2):
        dd[i]=distance**2
  for i in range(a):
    p[i]=dd[i]/dd.sum()
  print(p)
  CENTER=np.random.choice(np.arange(a),p=p)
  print(p[CENTER])
  center=center[center!=CENTER]
  center=np.insert(center,count,CENTER)
print(dd)
print(center)

print(center)

d=np.empty((C,a))
for i in range(C):
  for j in range(a):
    x = X_train[center[i]:center[i]+1].values.reshape(-1, 1)
    y = X_train[j:j+1].values.reshape(-1, 1)
    distance, path = fastdtw(x, y, dist=euclidean)
    d[i,j]=distance


dimin = d.min(0)
u = (d <= dimin).astype(float)
alpha = 1.5
beta = 0.0
upp = (d <= alpha * dimin + beta).astype(float)

un = upp / upp.sum(0)

b = un @ X_train.values / un.sum(1)[:, np.newaxis]
print(b)

print(upp)

print(a)
print(b)



plt.figure(figsize=(15,10))
y=np.array([1,2,3,4,5,6,7,8,9,10,11,12])
for i in range(a):
  XX=X_train[i:i+1].values
  plt.plot(y,np.ravel(XX),color=(upp[0][i]*0.8+upp[1][i]*0.1+upp[2][i]*0.1,upp[1][i]*0.8+upp[0][i]*0.1+upp[2][i]*0.1,upp[2][i]*0.8+upp[1][i]*0.1+upp[0][i]*0.1))


plt.show()