#!/bin/bash
if [ "$1" != "" ]; then
    echo "Creating stucture for: $1"
else
    echo "Plz, use a prequired project name as s parameter to the scrip"
    exit
fi
git checkout -b $1
mkdir $1
cd $1
mkdir png
mkdir dxf
git push --set-upstream origin $1
echo "dxf/*.dxf~" > .gitignore
NAME=${1##*__}
FNAME=$NAME".ino"
echo $FNAME
echo -e "void setup() {\n  pinMode(LED_BUILTIN, OUTPUT);\n}\n\nvoid loop() {\n  digitalWrite(LED_BUILTIN, HIGH);\n  delay(1000);\n  digitalWrite(LED_BUILTIN, LOW);\n  delay(1000); \n}\n" > $FNAME
echo -e "## main/readme" > readme.md
cd ..
ISSUE_NUM=$(echo $1| cut -d'_' -f 1)
echo "|[$ISSUE_NUM](https://github.com/ayaromenok/test_baremetal/issues/$ISSUE_NUM) | ![$NAME](https://github.com/ayaromenok/test_baremetal/blob/master/$1/png/$ISSUE_NUM.png) | NoK | comment |\n" >> README.md
echo "done"
