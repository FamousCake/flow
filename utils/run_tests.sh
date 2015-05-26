FILES=./tests/*
for f in $FILES
do
  echo "Processing $f file..."
  # take action on each file. $f store current file name
  cat $f | ./run.out >> results5.txt
  # cat $f
done

