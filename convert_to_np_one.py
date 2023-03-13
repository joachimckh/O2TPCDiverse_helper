import sys
import numpy as np
import pandas as pd

import json

import argparse

import uuid
from pathlib import Path
import glob



def main(args):

    Path(args.path + '/' + args.out).mkdir(parents=True, exist_ok=True)


    file_list = ['iniTrack', 'iniTrackRef', 'mcTrack', 'movTrackRef']
    #for i in file_list:
    for i in range(4):

        files = glob.glob(args.path + "/*/{}.txt".format(file_list[i]),recursive=True)

        temp=[]
        for f in files:
            temp.append(pd.read_csv(f, header=None,sep=' ',index_col=0).iloc[:,0:-1])#names=data_names)
            #temp = df.iloc[:,0:-1] # remove NaN

        df = pd.concat(temp)


        out = df.to_numpy()
        np.save(args.path + '/' + args.out + '/' + '{}.npy'.format(file_list[i]),out)

















if __name__=='__main__':

    parser = argparse.ArgumentParser()

    parser.add_argument("--path",
                        default="/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/data_files",
                        required=False,
                        help="track file path"
                        )

    parser.add_argument("--out",
                        default='numpy_data',
                        required=False,
                        help="Where to save rewritten files, only put one folder name as the folder will be written to --path"
                        )



    args = parser.parse_args()

    main(args)


    print("Data converted successfully to np files")
