TGT=../Narog-August/Lists

mkdir $TGT

for f in *
do 
   if [ -d $f ] ; then
      echo $f
      mkdir $TGT/$f
      mv $f/List* $TGT/$f
   fi
done