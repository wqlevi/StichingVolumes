import numpy as np
import nibabel as nb
import argparse

parser = argparse.ArgumentParser()

parser.add_argument('--input',type=str,default='example.dat',help='input datasheet(e.g. .dat, .txt, or .csv)')
parser.add_argument('--visualize',type=int,default=0,help='visualize')
opt = parser.parse_args()
arr = np.loadtxt('example_crop.dat', delimiter=",").reshape(128,128,128)
#arr = np.loadtxt(opt.input, delimiter=",").reshape(640,698,512)
print(f"loaded array with shape:\t{arr.shape}")
nii = nb.Nifti1Image(arr,np.eye(4))
nb.save(nii,'example_crop.nii')

if(opt.visualize == 1):
    import matplotlib.pyplot as plt
    fig,ax = plt.subplots(2,2,figsize=(10,10))
    ax[0,0].imshow(arr[0,:,:]),ax[0,0].set_ylabel('yz plane')
    ax[0,1].imshow(arr[:,0,:]),ax[0,1].set_ylabel('xz plane')
    ax[1,0].imshow(arr[:,:,0]),ax[1,0].set_ylabel('xy plane')
    plt.show()

