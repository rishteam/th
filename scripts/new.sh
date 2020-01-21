
#!/bin/bash
if [[ "$1" != "" ]]; then
    touch src/$1.cpp include/$1.h
else
    echo "Usage: $0 <name>"
fi
