#!/bin/bash

if [ ! -f "pa2" ]; then
    make
fi

./pa2 <../test/test0.in >../test/test_your.out # output your answer
diff ../test/test0.out ../test/test_your.out

./pa2 <../test/test1.in >../test/test_your1.out # output your answer
diff ../test/test1.out ../test/test_your1.out
