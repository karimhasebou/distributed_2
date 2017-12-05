defaultImg=$1 #cover image path
imageToHide=$2 #image to embed
destFolder=$3 # destination folder
secretFile=$4 # text file to embed, note this is an optional argument

imageToHideName=$(basename $imageToHide)
#imageToHidePath=$(basename $imageToHide)
echo $0 $1 $2 $3 $imageToHideName

#bash clean.sh

rm -rf Temp
if [[ $imageToHide == *"MyImages"* ]]; then
	Stegnography/unstegone.sh $imageToHide
else
	Stegnography/unsteg.sh $imageToHide
fi
#find Temp/ ! -name $imageToHideName -type f -exec rm -f {} +

# clear directory
mkdir Temp2
mv Temp/$imageToHideName Temp2/$imageToHideName #back up original photo
Stegnography/clean.sh

rm -rf Temp

pwd
echo $imageToHide
if [[ $imageToHide == *"MyImages"* ]]; then
Stegnography/steg_one.sh Temp2/$imageToHideName $destFolder/$imageToHideName
echo "update one"
else
Stegnography/steg_img.sh $defaultImg Temp2/$imageToHideName $destFolder $secretFile
echo "update two"
fi
rm -rf Temp2



