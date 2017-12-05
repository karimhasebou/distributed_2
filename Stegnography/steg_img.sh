# these are all arguments to be passed to base
defaultImg=$1 #cover image path
imageToHide=$2 #image to embed
destFolder=$3 # destination folder
secretFile=$4 # text file to embed, note this is an optional argument

secretFileName=$(basename $secretFile)
imageToHideName=$(basename $imageToHide)
defaultImgName=$(basename $defaultImg)

echo '-------------'
echo $imageToHideName
echo '-------------'

mkdir Temp
touch Temp/$imageToHideName.txt # empty file

cp $defaultImg Temp/$defaultImgName
cp $imageToHide Temp/$imageToHideName

if [ "$#" -ne 4 ]; then
	echo "n"
   steghide embed -cf Temp/$imageToHideName -ef Temp/$imageToHideName.txt -p root
else
    cp $secretFile Temp/$imageToHideName.txt
    steghide embed -cf Temp/$imageToHideName -ef Temp/$imageToHideName.txt -p root
fi

steghide embed -cf Temp/$defaultImgName -ef Temp/$imageToHideName -p root
mv Temp/$defaultImgName $destFolder/$imageToHideName

pwd
rm -rf Temp # empty all left overs

