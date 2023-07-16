# ライブラリのインポート

import numpy as np
import scipy.spatial.distance as dist
import matplotlib.pyplot as plt
from sklearn import metrics
import matplotlib.pyplot as plt
from sklearn.metrics import roc_auc_score
import random
from numpy.random import *

# RCM法の準備

#クラスター数2、初めのクラスター中心はランダムに決める

C=2
X=np.array([[0,0,1],[1,0,1],[1,1,0]])



関数化されたRCM法

def rcm(X,C,alpha,beta):
  n,m=X.shape
  b = X[np.random.permutation(n)[:C]]
  u_old = np.zeros((C, n))
  for i in range(10):
    for step in range(100):
      d = dist.cdist(b, X)
      print(d)
      dimin = d.min(0)
      upp = (d <= alpha * dimin + beta).astype(float)
      un = upp / upp.sum(0)
      if np.abs(un - u_old).max() <= 1e-5:
        break
      u_old=un.copy()
      b = un @ X / un.sum(1)[:, np.newaxis]
    if i==0:
      uppa=upp
    else:
      uppa = np.array(uppa)+np.array(upp)
  uppa = uppa/10
  un = uppa / uppa.sum(0)
  b = un @ X / un.sum(1)[:, np.newaxis]
  #print(d)
  return upp,un,b

upp,un,b=rcm(X,C,1.6,0.0)


上エリアメンバシップ

正規化メンバシップ行列

クラスター中心

print(upp)

print(un)

print(b)

#推薦度の関数と閾値ηで推薦するかの関数

def rec(u,b):
  r=np.dot(u.T,b)
  return r

def ref(r,eta):
  x=np.where(r<eta,0,1)
  return x

r=rec(un,b)
print(r)

#今までの関数を組み合わせてできた関数化されたRCM-CF法

def rcmcf(X,C,alpha,beta,eta):
  upp,un,b=rcm(X,C,alpha,beta)
  r=rec(un,b)
  x=ref(r,eta)
  return x

#β=0としてαを変更する

#η=0.5とする

beta=0
eta=0.5

for i in range(10):
  alpha=1.0+i*0.5
  print("α=",round(alpha,1))
  print(rcmcf(X,C,alpha,beta,eta))

#α=1.0,η=0.5のとき

alpha=1.0
eta=0.5
for i in range(10):
  beta=0.0+i*0.5
  print("β=",round(beta,1))
  print(rcmcf(X,C,alpha,beta,eta))

# 実データを用いる

#tがテストデータ、gがトレーニングデータである。

from google.colab import drive

drive.mount('/content/drive')

import pandas as pd

tdata= pd.read_csv('drive/My Drive/needs_scan_panel_test.csv',header=None)
t=tdata.values

gdata = pd.read_csv('drive/My Drive/needs_scan_panel_training.csv',header=None)
g=gdata.values

print(t)

#データ、クラスター数、α、βの値から推薦度を返す関数rcmrec

def rcmrec(X,C,alpha,beta):
  upp,un,b=rcm(X,C,alpha,beta)
  r=rec(un,b)
  return r

#fがトレーニングデータの推薦度、fgとftはそれぞれトレーニングデータとテストデータの対応している推薦度である。

f=rcmrec(g,2,1.0,0.0)
ft=np.empty(1000)
fg=f[t[:,0],t[:,1]]
ft=t[:,2]

fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
auc = metrics.auc(fpr, tpr)
plt.plot(fpr, tpr, label='ROC curve (area = %.2f)'%auc)
plt.legend()
plt.title('ROC curve (C=2)')
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.grid(True)

# HCM法の結果

def hcm(X, C):
  n, m = X.shape
  b = X[np.random.permutation(n)[:C]]
  u_old = np.zeros((C, n))
  for step in range(100):
    d = dist.cdist(b, X)
    u = np.zeros((C, n))
    u[d.argmin(0), range(n)] = 1
    if np.abs(u - u_old).max() <= 1e-5:
      break
    u_old = u.copy()
    b = u @ X / u.sum(1)[:, np.newaxis]
  return u, b

"""
haauc=[0]
for i in range(15):
  u,b=hcm(g,i+1)
  f=rec(u,b)
  ft=np.empty(1000)
  fg=f[t[:,0],t[:,1]]
  ft=t[:,2]
  fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
  auc = metrics.auc(fpr, tpr)
  haauc=np.append(haauc,auc)
haauc=np.delete(haauc,0)
C=list(np.arange(1,15+1))
plt.plot(C,haauc)
plt.show()
"""
haauc=[0]
for i in range(15):
  x=0
  for j in range(5):
    u,b=hcm(g,i+1)
    f=rec(u,b)
    ft=np.empty(1000)
    fg=f[t[:,0],t[:,1]]
    ft=t[:,2]
    fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
    auc = metrics.auc(fpr, tpr)
    x+=auc
  x/=5
  haauc=np.append(haauc,x)
haauc=np.delete(haauc,0)
C=list(np.arange(1,15+1))
plt.plot(C,haauc)
plt.show()


# rcm法単体で見た時のα、βの比較

"""α,βは0.1刻み

αは1.0～1.4で下の行に行くほど値が大きくなる

βは0.0～0.4で右の行に行くほど値が大きくなる"""


"""平均をとる回数 N"""
N=2
c=30
plt.figure(figsize=(25,20))
count=1
for a in range(5):
  for b in range(5):
    aauc=[0]
    for i in range(c):
      avauc=0
      for j in range(N):
        f=rcmrec(g,i+1,1.0+a*0.1,0.1*b)
        ft=np.empty(1000)
        fg=f[t[:,0],t[:,1]]
        ft=t[:,2]
        fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
        auc = metrics.auc(fpr, tpr)
        avauc+=auc
      avauc/=N
      aauc=np.append(aauc,avauc)
    aauc=np.delete(aauc,0)
    C=list(np.arange(1,c+1))
    plt.subplot(5,5,count)
    plt.title('α=%1.1f'%(a*0.1+1.0))
    plt.plot(C,aauc)
    count=count+1
    """図は多くて３、いろいろな結果をまとめて見れるように"""

rcm法とhcm法との比較

plt.figure(figsize=(25,20))
count=1
for a in range(5):
  for b in range(5):
    aauc=[0]
    for i in range(15):
      x=0
      """"""
      for j in range(10):
        f=rcmrec(g,i+1,1.0+a*0.04,0.1+b*0.04)
        ft=np.empty(1000)
        fg=f[t[:,0],t[:,1]]
        ft=t[:,2]
        fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
        auc = metrics.auc(fpr, tpr)
        x+=auc
      """"""
      x/=10
      aauc=np.append(aauc,x)
    aauc=np.delete(aauc,0)
    C=list(np.arange(1,15+1))
    plt.subplot(5,5,count)
    plt.title('α=%1.1f'%(a*0.1+1.0))
    plt.plot(C,aauc)
    plt.plot(C,haauc)
    count=count+1

"""
α,βは0.04刻み

αは1.0～1.16で下の行に行くほど値が大きくなる

βは0.0～0.16で右の行に行くほど値が大きくなる
"""
plt.figure(figsize=(25,20))
c=200
count=1
for a in range(5):
  for b in range(5):
    aauc=[0]
    for i in range(c):
      x=0
      """"""
      for j in range(5):
        f=rcmrec(g,i+1,1.0+a*0.04,0.1+b*0.04)
        ft=np.empty(1000)
        fg=f[t[:,0],t[:,1]]
        ft=t[:,2]
        fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
        auc = metrics.auc(fpr, tpr)
        x+=auc
      """"""
      x/=5
      aauc=np.append(aauc,x)
    aauc=np.delete(aauc,0)
    C=list(np.arange(1,c+1))
    plt.plot(C,aauc,color=(0.1*a+0.1*b, 1.0-a*0.2, 1.0-b*0.2),label=" ")
    count=count+1
plt.legend(bbox_to_anchor=(0.5, 0.2), borderaxespad=0)
plt.show()
"""クラスター数固定、その時の最良の結果のみを記録、様々なパラメータで,
それぞれのパラメータの影響がわかるように、ヒートマップ"""

"""同じαβでクラスター数による変化の図
αβを変更して、クラスター数不問で最高の値を求める"""

α＝１で固定、β＝０で固定

plt.figure(figsize=(25,20))
count=1
for a in range(5):
  for b in range(5):
    aauc=[0]
    for i in range(15):
      x=0
      """"""
      for j in range(10):
        f=rcmrec(g,i+1,1.0+a*0.04,0.1+b*0.04)
        ft=np.empty(1000)
        fg=f[t[:,0],t[:,1]]
        ft=t[:,2]
        fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
        auc = metrics.auc(fpr, tpr)
        x+=auc
      """"""
      x/=10
      aauc=np.append(aauc,x)
    aauc=np.delete(aauc,0)
    C=list(np.arange(1,15+1))
    plt.subplot(5,5,count)
    plt.title('α=%1.2f'%(a*0.04+1.0))
    plt.plot(C,aauc)
    plt.plot(C,haauc)
    count=count+1

""""""
課題

クラスター数が同じ場合の時は初めのクラスター中心を同じもので実験できるようにする

クラスター数が２以上あるデータを使い推薦性能の比較を行う

ηの設定
""""""
dd= pd.read_csv('drive/My Drive/ratings_cut.csv',header=None)
np.set_printoptions(precision=6)
d=dd.values
d=d.astype(int)

ddd=np.empty(3)

for i in range(d.shape[0]):
  if(d[i][1]<70000):
    ddd=np.append(ddd,d[i],axis=0)

d=ddd.reshape(-1,3)
d=d.astype(int)

for i in range(d.shape[0]):
  if int(d[i][2])<3.0:
    d[i][2]=0
  else:
    d[i][2]=1
d=np.delete(d,0,0)
print(d)

rng = np.random.default_rng(0)
x=np.arange(d.shape[0])
rng.shuffle(x, axis=0)
xx=x[:2000]

testd=np.arange(3)
print(testd)
for i in range(xx.shape[0]):
  testd=np.append(testd,d[xx[i]],axis=0)
  d[xx[i]][2]=0

print(testd)
testd=testd.reshape(-1,3)
testd=np.delete(testd,0,0)
print(testd)
testd=testd.astype(int)

max=np.max(d)
numbermax=735
data=np.zeros((numbermax,max))
for i in range(d.shape[0]):
  if(d[i][2]!=0):
    data[d[i][0]][d[i][1]-1]=1

print(data)



 f=rcmrec(data,2,1.0,0.1)
 print(f)

N=1
plt.figure(figsize=(25,20))
count=1
for a in range(2):
  for b in range(2):
    aauc=[0]
    for i in range(10):
      avauc=0
      for j in range(N):
        f=rcmrec(data,i+1,1.0+a*0.1,0.1*b)
        ft=np.empty(10000)
        fg=f[testd[:,0],testd[:,1]]
        ft=testd[:,2]
        fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
        auc = metrics.auc(fpr, tpr)
        avauc+=auc
      avauc/=N
      aauc=np.append(aauc,avauc)
    aauc=np.delete(aauc,0)
    C=list(np.arange(1,10+1))
    plt.subplot(5,5,count)
    plt.title('α=%1.1f'%(a*0.1+1.0))
    plt.plot(C,aauc)
    count=count+1


haauc=[0]
for i in range(10):
  x=0
  for j in range(5):
    u,b=hcm(data,i+1)
    f=rec(u,b)
    ft=np.empty(10000)
    fg=f[testd[:,0],testd[:,1]]
    ft=testd[:,2]
    fpr, tpr, thresholds = metrics.roc_curve(ft,fg)
    auc = metrics.auc(fpr, tpr)
    x+=auc
  x/=5
  haauc=np.append(haauc,x)
haauc=np.delete(haauc,0)
C=list(np.arange(1,10+1))
plt.plot(C,haauc)
plt.show()
