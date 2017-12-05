img=$0
imgName=$(basename $img)

mkdir Temp
cp $img Temp/$imgName

cd Temp/
steghide extract -sf $imgName -p root

cd ..
