imageToHide=$2 #image to embed
destFolder=$3 # destination folder
secretFile=$4 # text file to embed, note this is an optional argument

imageToHideName=$(basename $imageToHide)

#bash clean.sh
rm -rf Temp
../Stegnography/unsteg_one.sh $imageToHide


# clear directory
mkdir Temp2
mv Temp/$imageToHideName Temp2/$imageToHideName #back up original photo
../Stegnography/clean.sh

rm -rf Temp

../Stegnography/steg_img_one.sh $defaultImg Temp2/$imageToHideName $destFolder $secretFile


rm -rf Temp2




