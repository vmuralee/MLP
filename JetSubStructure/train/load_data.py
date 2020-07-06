import ROOT
from root_numpy import root2array, rec2array, array2root, tree2array
import pandas as pd
from sklearn.utils import shuffle

def load_data(inputPath,InTree):
    var_list = ['qpTD','qMulti','JetPt']
    my_cols_list = var_list + ['target']
    data = pd.DataFrame(columns=my_cols_list)
    file_ = ROOT.TFile(inputPath+'/TrainingFile.root')
    for t in InTree:
        tree = file_.Get(t)
        tree_arr = tree2array(tree)
        tree_df = pd.DataFrame(tree_arr,columns=var_list)
        if(t == 'TreeQ'):tree_df['target']=1
        if(t == 'TreeG'):tree_df['target']=0
        tmp_df = tree_df.loc[tree_df['JetPt']<=80]
        tmp_df = tmp_df.loc[tmp_df['JetPt']>40]
        data = data.append(tmp_df,ignore_index=True,sort=False)
    for _ in range(8):data = shuffle(data)
    return data

# print(load_data('../data',['TreeQ','TreeG']))




