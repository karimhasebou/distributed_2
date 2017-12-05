defaultImg=$1 #cover image path
imageToHide=$2 #image to embed
destFolder=$3 # destination folder
secretFile=$4 # text file to embed, note this is an optional argument

imageToHideName=$(basename $imageToHide)
#imageToHidePath=$(basename $imageToHide)

#bash clean.sh
rm -rf Temp
Stegnography/unsteg.sh $imageToHide

#find Temp/ ! -name $imageToHideName -type f -exec rm -f {} +

# clear directory
mkdir Temp2
mv Temp/$imageToHideName Temp2/$imageToHideName #back up original photo
Stegnography/clean.sh

rm -rf Temp

echo "noob here4"
if [[$imageToHide == *"MyImages"]]; then
Stegnography/stegone.sh Temp2/$imageToHideName $destFolder
else
Stegnography/steg_img.sh $defaultImg Temp2/$imageToHideName $destFolder $secretFile
fi
echo "noob here2"
rm -rf Temp2
echo "noob here3"



