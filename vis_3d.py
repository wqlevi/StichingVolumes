import numpy as np
import nibabel as nb
#arr = np.loadtxt('example_crop.dat', delimiter=",").reshape(128,128,128)
arr = np.loadtxt('example.dat', delimiter=",")
print(f"loaded array with shape:\t{arr.shape}")
import matplotlib.pyplot as plt
plt.imshow(arr)
plt.show()
'''
nii = nb.Nifti1Image(arr,np.eye(4))
nb.save(nii,'example_crop.nii')
'''
