defaultImg=$1 #cover image path
imageToHide=$2 #image to embed
destFolder=$3 # destination folder
secretFile=$4 # text file to embed

secretFileName=$(basename $secretFile)
imageToHideName=$(basename $imageToHide)
defaultImgName=$(basename $defaultImg)

mkdir Temp
touch Temp/$imageToHide.txt # empty file

cp $defaultImg Temp/$defaultImgName
cp $imageToHide Temp/$imageToHideName

if [ "$#" -ne 4 ]; then
    steghide embed -cf Temp/$imageToHideName -ef Temp/$imageToHide.txt -p root
else
    cp $secretFile Temp/$imageToHide.txt
    steghide embed -cf Temp/$imageToHideName -ef Temp/$imageToHide.txt -p root
fi

steghide embed -cf Temp/$defaultImgName -ef Temp/$imageToHideName -p root
mv Temp/$defaultImgName $destFolder/$imageToHideName

rm -rf Temp/ # empty all left overs
