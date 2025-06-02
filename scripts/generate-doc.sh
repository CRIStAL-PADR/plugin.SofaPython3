#!/bin/bash

usage() {
    echo "Usage: generate_doc.sh <sofa-python3-site-packages-dir> "
    echo "This script automatically generates documentation for SofaPython3 modules"
}

if [ "$#" -eq 1 ]; then
    WORK_DIR=$1
else
    usage; exit 1
fi

cd $WORK_DIR
make html
