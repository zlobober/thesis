#!/bin/bash

shopt -s extglob

# Pdflatex
export TEXINPUTS=".:`pwd`:"
PDFLATEX="pdflatex -shell-escape -file-line-error -output-directory=`pwd`"
GREP='grep ".*:[0-9]*:.*"' # показывает на выходе только ошибки

# Файлы/Папки
PDF_NAME='article.pdf'
TEX='../tex-en-csr-talk'
IMG='img'
MAINTEX="main"

pushd $TEX/$IMG
rm !(*.mp);
mpost pic.mp || exit 1
mpost pic.mp || exit 1
popd

mkdir -p img

mv $TEX/$IMG/!(*.mp) ./img/

pushd $TEX

# Сборка latex
$PDFLATEX $MAINTEX
popd
BIBOUTPUT=$(BSTINPUTS=$TEX BIBINPUTS=$TEX bibtex $MAINTEX)
pushd $TEX
# Показывать output bibtex'a только в случае ошибок
if [[ "$BIBOUTPUT" =~ "error" ]]; then
    echo "$BIBOUTPUT"
fi
$PDFLATEX $MAINTEX > /dev/null
$PDFLATEX $MAINTEX

popd

mv $MAINTEX.pdf $PDF_NAME

