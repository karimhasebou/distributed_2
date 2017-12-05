# these are all arguments to be passed to base
imageToHide=$1 #image to embed
target=$2

imageToHideName=$(basename $imageToHide)

mkdir Temp
touch Temp/$imageToHideName.txt # empty file

cp $imageToHide Temp/$imageToHideName

steghide embed -cf Temp/$imageToHideName -ef Temp/$imageToHideName.txt -p root

mv Temp/$imageToHideName $target

rm -rf Temp # empty all left overs

