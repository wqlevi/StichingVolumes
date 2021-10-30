uiopen('example.csv',1);
arr = table2array(example);
arr = reshape(arr,512,698);
imshow(arr,[]),impixelinfo();