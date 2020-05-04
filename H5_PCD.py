# -*- coding: utf-8 -*-
"""
Created on Sat May  2 21:35:08 2020

@author: sgl
"""
import os
import sys
import h5py
import numpy as np 
import json

# step1:load data
f = h5py.File('ply_data_test0.h5','r') 
for key in f.keys():
    print(f[key].name)   # print all key in h5 files

data = f['data'][:]   # xyz data (2048, 2048, 3)
label = f['label'][:]   # class label (2048, 1)
pid = f['pid'][:]   # part label (2048,2048)

# step2: analytic character
data_stack = data.reshape((-1,3))
max_val = np.amax(data,axis=1)
min_val = np.amin(data,axis=1)

static_data = np.hstack((max_val,-1*min_val))
static_max = np.amax(static_data,axis=1)
static = [0 for _ in range(10)]
for i,val in enumerate(static_max):
    static[int(val*10)] += 1

# step3: generate .pcd files
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.dirname(os.path.dirname(BASE_DIR))
sys.path.append(BASE_DIR)
sys.path.append(ROOT_DIR)
ROOT_DIR = os.path.join(ROOT_DIR, 'Desktop/ShapeNet可视化与特性研究')    

g_class2color = json.load(open('part_color_mapping.json', 'r'))
for i in range(0,10):    
    path = os.path.join(ROOT_DIR,'shape_'+str(i)+'.pcd')
    if os.path.exists(path):
        os.remove(path)
    Output_Data = open(path, 'a')
    # headers
    Output_Data.write('# .PCD v0.7 - Point Cloud Data file format\nVERSION 0.7\nFIELDS x y z rgba\nSIZE 4 4 4 4\nTYPE F F F U\nCOUNT 1 1 1 1')
    string = '\nWIDTH ' + str(data.shape[1])
    Output_Data.write(string)
    Output_Data.write('\nHEIGHT 1\nVIEWPOINT 0 0 0 1 0 0 0')
    string = '\nPOINTS ' + str(data.shape[1])
    Output_Data.write(string)
    Output_Data.write('\nDATA ascii')
    
    # pack RGB
    RGB = []
    for j in range(data.shape[0]):
        R=int(g_class2color[int(pid[i,j])][0]*255)
        G=int(g_class2color[int(pid[i,j])][1]*255)
        B=int(g_class2color[int(pid[i,j])][2]*255)
        value = (int(R) << 16 | int(G) << 8 | int(B))
        string = ('\n' + str(data[i,j,0]) + ' ' + str(data[i,j,1]) + ' ' +str(data[i,j,2]) + ' ' + str(value))
        Output_Data.write(string)
    
    Output_Data.close()