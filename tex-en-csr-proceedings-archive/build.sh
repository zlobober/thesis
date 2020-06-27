#!/bin/bash

set -x

rm -r archive
mkdir archive

cp ../tex-en-csr-submission/{1*,2*,3*,4*,6*} archive/
cp ./0-main-proceedings.tex archive/
cp ../tex-en-csr-submission/llncs.cls archive/
cp -r ../tex-en-csr-submission/img archive/img-src
cp -r ../build-tex-en-csr-submission/img archive/img
cp ../tex-en-csr-submission/0-main.bib archive/
cp ../tex-en-csr-submission/splncs04.bst archive/
cp ./53-algorithms.tex archive/

pushd archive
zip -r archive.zip *
popd

