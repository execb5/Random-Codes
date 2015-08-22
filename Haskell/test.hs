{-# LANGUAGE TemplateHaskell #-}

import Test.QuickCheck
import Test.QuickCheck.All

myLast :: [a] -> a
myLast [x] = x
myLast (_:xs) = myLast xs

prop_myLast xs = length xs > 0 ==> myLast xs == last xs

main = $(quickCheckAll)
