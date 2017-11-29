defaultImg=$1 #img to extract

defaultImgName=$(basename $defaultImg)


rm Temp/ # remove temp if exists
mkdir Temp
cd Temp/
cp $defaultImg $defaultImgName


steghide extract -sf $defaultImgName -p root # extract img once

echo 'extracted img'

steghide extract -sf $defaultImgName -p root # extract txt file

echo 'extracted file'

cd .. # go back to our previous directory
