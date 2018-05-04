# Pdflatex
PDFLATEX="pdflatex -interaction=nonstopmode -shell-escape -file-line-error -output-directory=`pwd`"
GREP='grep ".*:[0-9]*:.*"' # показывает на выходе только ошибки

# Файлы/Папки
PDF_NAME='thesis.pdf'
TEX='../tex'
IMG='inc/img'
MAINTEX="0-main"

pushd $TEX

# Конвертация eps
find $IMG/ -type f -name "*.eps" -exec epstopdf {} ";" ;
find $IMG -type f -name "*.eps" -exec rm -f {} \;

# Сборка latex
$PDFLATEX $MAINTEX > /dev/null
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

