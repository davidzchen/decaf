#!/bin/sh

for file in $(grep -li "exceptions" *.out)
do
    sed -e "s/\/usr\/class\/cs143\/bin/\/opt\/local\/share\/spim/g" $file > temp.out
    mv temp.out $file
done
