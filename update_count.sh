defaultImg=$1 #cover image path
imageToHide=$2 #image to embed
destFolder=$3 # destination folder
secretFile=$4 # text file to embed, note this is an optional argument

imageToHideName=$(basename $imageToHide)
#imageToHidePath=$(basename $imageToHide)

#bash clean.sh
rm -rf Temp
bash unsteg.sh $imageToHide

#find Temp/ ! -name $imageToHideName -type f -exec rm -f {} +

# clear directory
mkdir Temp2
mv Temp/$imageToHideName Temp2/$imageToHideName #back up original photo
$bash clean.sh
rm -rf Temp

bash steg_img.sh $defaultImg Temp2/$imageToHideName $destFolder $secretFile

rm -Rf Temp2




