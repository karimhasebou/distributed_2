#!/usr/bin/bash
defaultImg=$1 #img to extract

defaultImgName=$(basename $defaultImg)


rm -rf Temp/ # remove temp if exists
mkdir Temp
cp $defaultImg Temp/$defaultImgName
cd Temp/

mv $defaultImgName tmp1 # rename default image to avoid conflict

steghide extract -sf tmp1 -p root # extract img once

echo 'extracted img'

steghide extract -sf $defaultImgName -p root # extract txt file

echo 'extracted file'

cd .. # go back to our previous directory

