import sys
import numpy as np
import pandas as pd

import json

import argparse

import uuid
from pathlib import Path

#sys.path.append('/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/py_dir')

#from tpcutils.data import SeparatedDataHandler, read_nonMC_tracks, read_MC_tracks

def main(args):

    Path(args.path + '/' + args.out).mkdir(parents=True, exist_ok=True)

    file_list = ['iniTrack', 'iniTrackRef', 'mcTrack', 'movTrackRef']
    for i in file_list:
        i = 0
        #path = '/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/data_files/beast_sim1'

        # file names: iniTrack.txt iniTrackRef.txt mcTrack.txt movTrackRef.txt

        df = pd.read_csv(args.path + '/' + file_list[i] + '.txt', header=None,sep=' ',index_col=0)#names=data_names)
        df = df.iloc[:,0:-1] # remove NaN

        meta_dict = {}


        loop_len = len(df)
        meta_dict['tree_length'] = loop_len
        meta_dict['np_row_len'] = 2000 # n Tracks pr file except last file


        unique_id = str(uuid.uuid4())
        meta_dict['uid'] = unique_id

        for rows in range(0,loop_len,meta_dict['np_row_len']):
            temp = df[rows:rows+meta_dict['np_row_len']].to_numpy()
            np.save(args.path + '/' + args.out + '/' + '{}_{}_uid_{}.npy'.format(file_list[i],"%06d" % rows,unique_id), temp)



        with open(args.path + '/' + args.out + '/' + "meta_data_uid_{}.json".format(unique_id), "w") as fp:
            json.dump(meta_dict,fp)














if __name__=='__main__':

    parser = argparse.ArgumentParser()

    parser.add_argument("--path",
                        default="/Users/joachimcarlokristianhansen/st_O2_ML_SC_DS/TPC-analyzer/TPCTracks/data_files/beast_sim1",
                        required=False,
                        help="track file path"
                        )

    parser.add_argument("--out",
                        default='rewritten_data',
                        required=False,
                        help="Where to save rewritten files, only put one folder name as the folder will be written to --path"
                        )



    args = parser.parse_args()

    main(args)


    print("Data converted successfully to np files")
