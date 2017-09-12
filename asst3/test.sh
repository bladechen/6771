cd ../build/asst3/
make
cd -
for ((i=2;i<=13;i++))

do
    ../build/asst3/test$i > out.$i
    diff result${i}.txt out.$i >/dev/null
    if [ "$?" == "0" ]
    then
        echo "pass $i"
    else
        echo "failed $i"
    fi
done
