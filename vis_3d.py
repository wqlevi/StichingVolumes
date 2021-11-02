import numpy as np
import nibabel as nb
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('--input',type=str,default='example.dat',help='input datasheet(e.g. .dat, .txt, or .csv)')
opt = parser.parse_args()
#arr = np.loadtxt('example_crop.dat', delimiter=",").reshape(128,128,128)
arr = np.loadtxt(opt.input, delimiter=",").reshape(640,698,512)
print(f"loaded array with shape:\t{arr.shape}")
nii = nb.Nifti1Image(arr,np.eye(4))
nb.save(nii,'example_crop.nii')

