#!/bin/bash
echo "Você é Caio?(s)||(n)"
read confirma
if [ $confirma = "s" ] ;
then
    git pull
    git  add ./
    echo "Digite um commit:"
    read commit
    git commit -m "$commit" 
    git push
else
    echo "Faça alterações apenas na sua pasta"
fi


