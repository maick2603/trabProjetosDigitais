#!/bin/bash

#reconhece_placas.sh [NOME DA IMAGEM] [CAMINHO DE SAIDA]

if [ ! -n "$2" ]
        then
                echo "falta parametros!"
else
        if [ ! -d "$2" ]
                then
                        mkdir "$2"
        fi
fi


if [ ! -n "$1" ] 
        then 
                echo "imagem" "$1" "não encontrada!"
        else             
                convert $1.jpg -depth 8 -compress none $1.pgm  #converte a placa
fi



./sobel $1.pgm










