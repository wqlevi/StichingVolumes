function lr_img = downsample_kspace(img, scale)
%
% input HR image, downsample by subsampling K-space data by scale factor...
% output LR image in complex numbers
%
k = fftshift(fftn(img));

kcrop = zeros(size(k));

[nx,ny,nz] = size(k);

scale = 2;
centersize = round([nx,ny,nz] ./ scale);

kcrop(round(nx)/2-centersize(1)/2:round(nx)/2+centersize(1)/2-1, round(ny)/2-centersize(2)/2:round(ny)/2+centersize(2)/2-1, round(nz)/2-centersize(3)/2:round(nz)/2+centersize(3)/2-1) = ...
    k(round(nx)/2-centersize(1)/2:round(nx)/2+centersize(1)/2-1, round(ny)/2-centersize(2)/2:round(ny)/2+centersize(2)/2-1, round(nz)/2-centersize(3)/2:round(nz)/2+centersize(3)/2-1);

lr_img = (ifftn(kcrop));
end
