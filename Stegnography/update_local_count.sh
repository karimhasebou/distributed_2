imageToHide=$1 #image to embed

cd MyImages/

steghide embed -cf $imageToHide -ef $imageToHide.txt -p root

rm -r $imageToHide.txt

cd ..


