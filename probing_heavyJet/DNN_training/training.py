import os
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
from sklearn.metrics import roc_curve
from sklearn.preprocessing import OneHotEncoder
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from sklearn.impute import SimpleImputer

parser = argparse.ArgumentParser(description='Training DNN model')
parser.add_argument('--cat',type=str,help='select categories',default='qg')
parser.add_argument('--path',type=str,help='pathe of samples',default='../Ntuples')
parser.add_argument('--JSS',type=bool,help='add JSS parameter',default=False)
args = parser.parse_args()
if(args.cat not in ['qq','qg','gg']):
    print('Please choose either of qq,qg or gg')
    exit(-1)

cat_files = dict({'qq':['pp2jj_SMbkg-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root','pp2coloron2_qq-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root'],
                  'qg':['pp2jj_SMbkg-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root','pp2ExUp2_ug-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root'],
                  'gg':['pp2jj_SMbkg-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root','pp2octet2_gg-Nev2e6-ptJetMin700-antiktR0.4-zcut0.1-beta1.0.root']
})
filenames = cat_files[args.cat]

labels = ['ptJ1','ptJ2','invmass','DRJ1J2','etaJ1','etaJ2']
if(args.JSS):
    print('Using JSS paramets')
    labels = labels+['pTDJ1','pTDJ2','LHAJ1','LHAJ2','e05J1','e05J2','s2J1','s2J2','pmJ1','pmJ2','tmJ1','tmJ2','widthJ1','widthJ2','girthJ1','girthJ2']

data = Data2Array(args.path,filenames,labels)
data_ar = data.load_df()

# Export to csv file
savefileAs = 'dijet_data_'+args.cat
if(args.JSS):
    savefileAs = 'dijet_data_JSS_'+args.cat
data.save_csv(data_ar,savefileAs)


#Creating Training,Test and Validation samples
traindataset_full,testdataset = train_test_split(data_ar,test_size=0.1,random_state=42)
traindataset,valdataset = train_test_split(traindataset_full,test_size=0.2,random_state=42)
trainData = copy.deepcopy(traindataset)
valData = copy.deepcopy(valdataset)


X_train,X_val = trainData.drop('target',axis=1).to_numpy(dtype='float64'),valData.drop('target',axis=1).to_numpy(dtype='float64')
y_train,y_val = trainData['target'].to_numpy(dtype='float64'),valData['target'].to_numpy(dtype='float64')
X_test,y_test = testdataset.drop('target',axis=1).to_numpy(dtype='float64'),testdataset['target']

#TransForming Data
num_pipeline = Pipeline([
    ('imputer',SimpleImputer(strategy="median")),
    ('std_scaler',StandardScaler()),
])
encoder = OneHotEncoder()

X_train_tr,X_val_tr = num_pipeline.fit_transform(X_train),num_pipeline.fit_transform(X_val)
y_train_tr,y_val_tr = encoder.fit_transform(trainData[['target']]).toarray(),encoder.fit_transform(valData[['target']]).toarray()

print(X_train_tr.shape,'  ',y_train_tr.shape)

#Creating DNN model
model = keras.models.Sequential([
    keras.layers.Flatten(input_shape=[len(labels)]),
    keras.layers.Dense(100,activation='relu'),
    keras.layers.Dense(200,activation='relu'),
    keras.layers.Dense(2,activation='sigmoid')
])

model.summary()
print(y_train_tr.shape)

model.compile(loss='sparse_categorical_crossentropy',optimizer='adam',metrics=['accuracy'])
#model.fit(X_train_tr,y_train,epochs=10,validation_data=(X_val_tr,y_val))
checkpoint_cb = keras.callbacks.ModelCheckpoint("keras_model.h5")
history = model.fit(X_train_tr,y_train,epochs=100,validation_data=(X_val_tr,y_val),callbacks=[checkpoint_cb])
model.save("keras_model.h5")

# #TensorBoard Visulaisation

# root_logdir = os.path.join(os.curdir,"my_logs")
# def get_run_logdir():
#     import time
#     run_id = time.strftime("run_%Y_%m_%d-%H_%M_%S")
#     return os.path.join(root_logdir,run_id)

# run_logdir = get_run_logdir()
# tensorboard_cb = keras.callbacks.TensorBoard(run_logdir)


# ROC ploting

pd.DataFrame(history.history).plot(figsize=(8,5))
plt.grid(True)
plt.gca().set_ylim(0,1)
plt.show()


#Find Best parameter

# gb = GradientBoostingRegressor(n_estimators=100)
# gb.fit(X_train, y_train)
# plt.bar(range(X_train.shape[1]), gb.feature_importances_)
# plt.xticks(range(X_train.shape[1]), labels)
# plt.show()
