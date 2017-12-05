# these are all arguments to be passed to base
echo $0
imageToHide=$1 #image to embed
imageToHideName=$(basename $imageToHide)

mkdir Temp
touch Temp/$imageToHideName.txt # empty file

cp $imageToHide Temp/$imageToHideName

steghide embed -cf Temp/$imageToHideName -ef Temp/$imageToHideName.txt -p root

mv Temp/$imageToHideName $2
echo $imageToHide
rm -rf Temp # empty all left overs

