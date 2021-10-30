table1 = readtable('*.csv');
arr = table2array(table1);
arr = reshape(arr,512,698);
imshow(arr,[]),impixelinfo();