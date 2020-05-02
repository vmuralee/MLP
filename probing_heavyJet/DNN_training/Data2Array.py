# Created by Vinaya Krishnan
# vinaya.krishna@cern.ch

import ROOT
from root_numpy import root2array, rec2array, array2root, tree2array
import pandas as pd
from sklearn.utils import shuffle
from sklearn.preprocessing import OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import StandardScaler

class Data2Array:
    def __init__(self,path,filenames,var):
        self.path = path
        self.filenames = filenames
        self.var = var
        for filename in self.filenames:
            print(f"loading data from {self.path}/{filename}")
    def variable_list(self):
        variables = self.var
        return variables
    def getTree(self,filename):
        cols_list = self.var+['target']
        file_ = ROOT.TFile(self.path+'/'+filename)
        if("SMbkg" in filename):
            treename = "TreeB"
        else:
            treename = "TreeS"
        tree = file_.Get(treename)
        tree_arr = tree2array(tree)
        tree_df = pd.DataFrame(tree_arr,columns=cols_list)
        tree_df = tree_df.loc[tree_df['invmass']>1900]
        tree_df = tree_df.loc[tree_df['invmass']<2200]
        # tree_df = tree_df.loc[tree_df['ptJ1']>800]
        # tree_df = tree_df.loc[tree_df['ptJ2']>800]
        if("gg" in filename):tree_df['target']='0'
        if("ug" in filename):tree_df['target']='1'
        if("qq" in filename):tree_df['target']='2'
        if("SMbkg" in filename):tree_df['target']='3'
        return tree_df
    def load_df(self):
        cols_list = self.var+['target']
        filenames = self.filenames
        data = pd.DataFrame(columns=cols_list)
        for filename in filenames:
            tmp_df = self.getTree(filename)
            data = data.append(tmp_df,ignore_index=True,sort=False)
        for _ in range(8):data = shuffle(data)
        return data

    def save_csv(self,data,csv_filename):
        return data.to_csv(csv_filename+'.csv')

    def cat_encoder(self,data_cat):
        encoder = OneHotEncoder()
        data_hot = encoder.fit_transform(data_cat)
        return data_hot
    
        
