import ROOT
import tensorflow as tf
from tensorflow import keras
from sklearn.model_selection import train_test_split
import numpy as np
import copy
import pandas as pd
import matplotlib.pyplot as plt
from Data2Array import Data2Array
import argparse

parser = argparse.ArgumentParser(description='Training DNN model')
parser.add_argument('--train',type=bool,help='Do Training',default=True)
parser.add_argument('--JSS',type=bool,help='add JSS parameter',default=False)
parser.add_argument('--path',type=str,help='pathe of samples',default='../Ntuples')
args = parser.parse_args()

filenames = ['pp2jj_SMbkg-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root',
             'pp2octet2_gg-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root',
             'pp2coloron2_qq-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root',
             'pp2ExUp2_ug-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root']

labels = ['ptJ1','ptJ2','etaJ1','etaJ2','DRJ1J2','invmass']
if(args.JSS==True):
    labels+['LHAJ1','LHAJ2','widthJ1','widthJ2','girthJ1','girthJ2','pTDJ1','pTDJ2']
data = Data2Array(args.path,filenames,labels)
data_ar = data.load_data()

#Creating Training,Test and Validation samples
traindataset_full,testdataset = train_test_split(data_ar,test_size=0.1,random_state=42)
traindataset,valdataset = train_test_split(traindataset_full,test_size=0.2,random_state=42)
trainData = copy.deepcopy(traindataset)
valData = copy.deepcopy(valdataset)

y_train,y_val = trainData['target'].to_numpy(dtype='float64'),valData['target'].to_numpy(dtype='float64')
X_train,X_val = trainData.drop('target',axis=1).to_numpy(dtype='float64'),valData.drop('target',axis=1).to_numpy(dtype='float64')
X_test,y_test = testdataset.drop('target',axis=1).to_numpy(dtype='float64'),testdataset['target'].to_numpy(dtype='float64')


#Creating DNN model
model = keras.models.Sequential([
    keras.layers.Flatten(input_shape=[len(labels)]),
    keras.layers.Dense(60,activation='relu'),
    keras.layers.Dense(30,activation='relu'),
    keras.layers.Dense(3,activation='softmax')
])
model.summary()

model.compile(loss='sparse_categorical_crossentropy',optimizer=keras.optimizer.SGD(lr=0.4),metrics=['accuracy'])

