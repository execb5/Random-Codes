-- Haskell Annotations
--
-- All taken from the book:
--      http://learnyouahaskell.com/
--
-- God bless the internet

--imports... only needed after chapter 7
import Data.List
import Data.Char
--import Data.List (nub,sort) use like this to import only those functions
--import Data.List hiding (nub) import all functions except nub
import qualified Data.Map as Map
import qualified Data.Set as Set
--qualified makes us reference Data.Map when we call its functions
--as M is just a rename so that we don't have to type Data.Map everytime

{-
 - Chapter 2
 -
 - STARTING OUT
 -
-}

doubleMe x = x + x

doubleUs x y = doubleMe x + doubleMe y

doubleSmallNumber x = if x > 100
                        then x
                        else x*2

quicksort :: Ord a => [a] -> [a]
quicksort []     = []
quicksort (p:xs) = (quicksort lesser) ++ [p] ++ (quicksort greater)
    where
        lesser = filter (< p) xs
        greater = filter (>= p) xs

boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

{-length' xs = sum [1 | _ <- xs]-}

removeNonUppercase :: String -> String
removeNonUppercase st = [ c | c <- st, c `elem` ['A'..'Z']]

triangles = [ (a,b,c) | c <- [1..10], b <- [1..10], a <- [1..10] ]

rightTriangles' = [ (a,b,c) | c <- [1..10], b <- [1..c], a <- [1..b], a^2 + b^2 == c^2, a+b+c == 24]

{-
 - Chapter 3
 -
 - TYPES AND TYPECLASSES
 -
-}

addThree :: Int -> Int -> Int -> Int
addThree x y z = x + y + z

factorial :: Integer -> Integer
factorial n = product [1..n]

factorial' :: (Integral a) => a -> a
factorial' 0 = 1
factorial' n = n * factorial' (n - 1)

circumference :: Float -> Float
circumference r = 2 * pi * r

circumference' :: Double -> Double
circumference' r = 2 * pi * r

{-
 - Chapter 4
 -
 - SYNTAX IN FUNCTIONS
 -
-}

lucky :: (Integral a) => a -> String
lucky 7 = "LUCKY NUMBER SEVEN!"
lucky x = "Sorry, you're out of luck, pal!"

sayMe :: (Integral a) => a -> String  
sayMe 1 = "One!"  
sayMe 2 = "Two!"  
sayMe 3 = "Three!"  
sayMe 4 = "Four!"  
sayMe 5 = "Five!"  
sayMe x = "Not between 1 and 5"

charName :: Char -> String
charName 'a' = "Albert"
charName 'b' = "Broseph"
charName 'c' = "Cecil"

addVectors :: (Num a) => (a, a) -> (a, a) -> (a, a)
{-addVectors a b = (fst a + fst b, snd a + snd b)-}
addVectors (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

first :: (a, b, c) -> a
first (x, _, _) = x

second :: (a, b , c) -> b
second (_, y, _) = y

third :: (a, b, c) -> c
third (_, _, z) = z

head' :: [a] -> a
head' [] = error "Can't call head on an empty list, dummy!"
head' (x:_) = x

tell :: (Show a) => [a] -> String
tell [] = "The list is empty"
tell (x:[]) = "The list has one element: " ++ show x
tell (x:y:[]) = "The list has two elements: " ++ show x ++ " and " ++ show y
tell (x:y:_) = "This list is long. The first two elements are: " ++ show x ++ " and " ++ show y

length' :: (Num b) => [a] -> b
length' [] = 0
length' (_:xs) = 1 + length' xs

sum' :: (Num a) => [a] -> a
sum' [] = 0
sum' (x:xs) = x + sum' xs

{-There's also a thing called as patterns. Those are a handy way of breaking-}
{-something up according to a pattern and binding it to names whilst still keeping-}
{-a reference to the whole thing. You do that by putting a name and an @ in front-}
{-of a pattern. For instance, the pattern xs@(x:y:ys). This pattern will match-}
{-exactly the same thing as x:y:ys but you can easily get the whole list via xs-}
{-instead of repeating yourself by typing out x:y:ys-}
capital :: String -> String
capital "" = "Empty string, whoops!"
capital all@(x:xs) = "The first letter of " ++ all ++ " is " ++ [x]

{-Guards are indicated by pipes that follow a function's name and its parameters.-}
{-Usually, they're indented a bit to the right and lined up. A guard is basically-}
{-a boolean expression. If it evaluates to True, then the corresponding function-}
{-body is used. If it evaluates to False, checking drops through to the next guard-}
{-and so on. If we call this function with 24.3, it will first check if that's-}
{-smaller than or equal to 18.5. Because it isn't, it falls through to the next-}
{-guard. The check is carried out with the second guard and because 24.3 is less-}
{-than 25.0, the second string is returned.-}
bmiTell :: (RealFloat a) => a -> a -> String
bmiTell weight height
    | bmi <= skinny = "You're underweight, you emo, you!"
    | bmi <= normal = "You're supposedly normal. Pffft, I bet you're ugly!"
    | bmi <= fat = "You're fat! Lose some weight, fatty!"
    | otherwise   = "You're a whale, congratulations!"
    where bmi = weight / height ^ 2
          skinny = 18.5
          normal = 25.0
          fat = 30.0
          {-(skinny, normal, fat) = (18.5, 25.0, 30.0)-}
          {-another way to write this where-}
{-"where" can be used to define several names and functions-}

max' :: (Ord a) => a -> a -> a
max' a b
    | a > b     = a
    | otherwise = b
{-In line using guards. Advised against because it's less readable.-}
{-max' a b | a > b = a | otherwise = b-}

myCompare :: (Ord a) => a -> a -> Ordering
a `myCompare` b
    | a > b     = GT
    | a == b    = EQ
    | otherwise = LT

initials :: String -> String -> String
initials firstname lastname = [f] ++ ". " ++ [l] ++ "."
    where (f:_) = firstname
          (l:_) = lastname

calcBmis :: (RealFloat a) => [(a, a)] -> [a]
calcBmis xs = [bmi w h | (w, h) <- xs]
    where bmi weight height = weight / height ^ 2
{-Writing the same function using let binding-}
{-calcBmis :: (RealFloat a) => [(a, a)] -> [a]-}
{-calcBmis xs = [bmi | (w, h) <- xs, let bmi = w / h ^ 2]-}

{-Very similar to where bindings are let bindings. Where bindings are a syntactic-}
{-construct that let you bind to variables at the end of a function and the whole-}
{-function can see them, including all the guards. Let bindings let you bind to-}
{-variables anywhere and are expressions themselves, but are very local, so they-}
{-don't span across guards. Just like any construct in Haskell that is used to-}
{-bind values to names, let bindings can be used for pattern matching. Let's see-}
{-them in action! This is how we could define a function that gives us a-}
{-cylinder's surface area based on its height and radius: -}
cylinder :: (RealFloat a) => a -> a -> a
cylinder r h =
    let sideArea = 2 * pi * r * h
        topArea = pi * r ^ 2
    in sideArea + 2 * topArea

{-Case expressions-}
describeList :: [a] -> String
describeList xs = "The list is " ++ case xs of [] -> "empty."
                                               [x] -> "a singleton list."
                                               xs -> "a longer list."
{-Defining the same function, but using where clause-}
{-describeList :: [a] -> String-}
{-describeList xs = "The list is " ++ what xs-}
        {-where what [] = "empty."-}
              {-what [x] = "a singleton list."-}
              {-what xs = "a longer list."-}

{-
 - Chapter 5
 -
 - RECURSION
 -
-}

maximum' :: (Ord a) => [a] -> a
maximum' [] = error "maximum of empty list"
maximum' [x] = x
maximum' (x:xs)
    | x > maxTail = x
    | otherwise = maxTail
    where maxTail = maximum' xs
{-rewriting maximum using max function-}
{-maximum' :: (Ord a) => [a] -> a-}
{-maximum' [] = error "maximum of empty list"-}
{-maximum' [x] = x-}
{-maximum' (x:xs) = max x (maximum' xs)-}

replicate' :: (Num i, Ord i) => i -> a -> [a]  
replicate' n x  
    | n <= 0    = []  
    | otherwise = x:replicate' (n-1) x

take' :: (Num i, Ord i) => i -> [a] -> [a]
take' n _
    | n <= 0   = []
take' _ []     = []
take' n (x:xs) = x : take' (n-1) xs

reverse' :: [a] -> [a]
reverse' [] = []
reverse' (x:xs) = reverse' xs ++ [x]

repeat' :: a -> [a]
repeat' x = x:repeat' x

zip' :: [a] -> [b] -> [(a,b)]
zip' _ [] = []
zip' [] _ = []
zip' (x:xs) (y:ys) = (x,y):zip' xs ys

elem' :: (Eq a) => a -> [a] -> Bool
elem' a [] = False
elem' a (x:xs)
    | a == x    = True
    | otherwise = a `elem'` xs

quicksort' :: (Ord a) => [a] -> [a]
quicksort' [] = []
quicksort' (x:xs) =
    let smallerSorted = quicksort' [a | a <- xs, a <= x]
        biggerSorted = quicksort' [a | a <- xs, a > x]
    in smallerSorted ++ [x] ++ biggerSorted

{-
 - Chapter 6
 -
 - HIGHER ORDER FUNCTIONS
 -
-}

{-Every function in Haskell officially only takes one parameter. So how is it-}
{-possible that we defined and used several functions that take more than one-}
{-parameter so far? Well, it's a clever trick! All the functions that accepted-}
{-several parameters so far have been curried functions. What does that mean?-}
{-You'll understand it best on an example. Let's take our good friend, the max-}
{-function. It looks like it takes two parameters and returns the one that's-}
{-bigger. Doing max 4 5 first creates a function that takes a parameter and-}
{-returns either 4 or that parameter, depending on which is bigger. Then, 5 is-}
{-applied to that function and that function produces our desired result. That-}
{-sounds like a mouthful but it's actually a really cool concept. The following-}
{-two calls are equivalent:Every function in Haskell officially only takes one-}
{-parameter. So how is it possible that we defined and used several functions that-}
{-take more than one parameter so far? Well, it's a clever trick! All the-}
{-functions that accepted several parameters so far have been curried functions.-}
{-What does that mean? You'll understand it best on an example. Let's take our-}
{-good friend, the max function. It looks like it takes two parameters and returns-}
{-the one that's bigger. Doing max 4 5 first creates a function that takes a-}
{-parameter and returns either 4 or that parameter, depending on which is bigger.-}
{-Then, 5 is applied to that function and that function produces our desired-}
{-result. That sounds like a mouthful but it's actually a really cool concept. The-}
{-following two calls are equivalent:-}
{-max 4 5-}
{-5-}
{-(max 4) 5-}
{-5-}

multThree :: (Num a) => a -> a -> a -> a
multThree x y z = x * y * z

compareWithHundred :: (Num a, Ord a) => a -> Ordering  
compareWithHundred x = compare 100 x
{-If we call it with 99, it returns a GT. Simple stuff. Notice that the x is on-}
{-the right hand side on both sides of the equation. Now let's think about what-}
{-compare 100 returns. It returns a function that takes a number and compares it-}
{-with 100. Wow! Isn't that the function we wanted? We can rewrite this as:-}
compareWithHundred' :: (Num a, Ord a) => a -> Ordering
compareWithHundred' = compare 100
{-The type declaration stays the same, because compare 100 returns a function.-}
{-Compare has a type of (Ord a) => a -> (a -> Ordering) and calling it with 100-}
{-returns a (Num a, Ord a) => a -> Ordering. The additional class constraint-}
{-sneaks up there because 100 is also part of the Num typeclass.-}

{-Infix functions can also be partially applied by using sections. To section an-}
{-infix function, simply surround it with parentheses and only supply a parameter-}
{-on one side. That creates a function that takes one parameter and then applies-}
{-it to the side that's missing an operand. An insultingly trivial function:-}
divideByTen :: (Floating a) => a -> a
divideByTen = (/10)

isUpperAlphanum :: Char -> Bool
isUpperAlphanum = (`elem` ['A'..'Z'])

{-Functions can take functions as parameters and also return functions. To-}
{-illustrate this, we're going to make a function that takes a function and then-}
{-applies it twice to something!-}
applyTwice :: (a -> a) -> a -> a
applyTwice f x = f (f x)

zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

flip' :: (a -> b -> c) -> (b -> a -> c)
flip' f = g
    where g x y = f y x

flip'' :: (a -> b -> c) -> b -> a -> c
flip'' f y x = f x y

map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = f x : map f xs

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' p (x:xs)
    | p x       = x : filter p xs
    | otherwise = filter' p xs

largestDivisible :: (Integral a) => a
largestDivisible = head (filter' p [100000,99999..])
    where p x = mod x 3829 == 0

chain :: (Integral a) => a -> [a]
chain 1 = [1]
chain n
    | even n = n:chain (div n 2)
    | odd n  = n:chain (n*3 + 1)

numLongChains :: Int
{-numLongChains = length (filter isLong (map chain [1..100]))-}
    {-where isLong xs = length xs > 15-}
numLongChains = length (filter (\xs -> length xs > 15) (map chain [1..100]))

addThree' :: (Num a) => a -> a -> a -> a
addThree' = \x -> \y -> \z -> x + y + z

flip''' :: (a -> b -> c) -> b -> a -> c
flip''' f = \x y -> f y x

sum'' :: (Num a) => [a] -> a
sum'' xs = foldl (\acc x -> acc + x) 0 xs

sum''' :: (Num a) => [a] -> a
sum''' = foldl (+) 0

elem'' :: (Eq a) => a -> [a] -> Bool
elem'' y ys = foldl (\acc x -> if x == y then True else acc) False ys

map'' :: (a -> b) -> [a] -> [b]
map'' f xs = foldr (\x acc -> f x : acc) [] xs

maximum'' :: (Ord a) => [a] -> a
maximum'' = foldr1 (\x acc -> if x > acc then x else acc)

reverse'' :: [a] -> [a]
reverse'' = foldl (\acc x -> x : acc) []

product' :: (Num a) => [a] -> a
product' = foldr1 (*)

filter'' :: ( a -> Bool) -> [a] -> [a]
filter'' p = foldr (\x acc -> if p x then x : acc else acc) []

head'' :: [a] -> a
head'' = foldr1 (\x _ -> x)

last' :: [a] -> a
last' = foldl1 (\_ x -> x)

{-How many elements does it take for the sum of the roots of all natural numbers-}
{-to exceed 1000?-}
sqrtSums :: Int
sqrtSums = length (takeWhile (<1000) (scanl1 (+) (map sqrt [1..]))) + 1

{-Function application with $-}
{-$ has low precedence-}
{-f (g (z x)) == f $ g $ z x-}
{-map ($ 3) [(4+), (10*), (^2), sqrt]-}

{-Function composition-}
{-fn x = ceiling (negate (tan (cos (max 50 x))))-}
fn = ceiling . negate . tan . cos . max 50 --point free style

{-Function that finds the sum of all odd squares that are smaller than 10000-}
{-oddSquareSum :: Integer-}
{-oddSquareSum = sum (takeWhile (<10000) (filter odd (map (^2) [1..])))-}

{-Same function but in point free style-}
{-oddSquareSum :: Integer-}
{-oddSquareSum = sum . takeWhile (<10000) . filter odd . map (^2) $ [1..]-}

{-Same function but written so that it is easier to understand-}
oddSquareSum :: Integer
oddSquareSum =
    let oddSquares = filter odd $ map (^2) [1..]
        belowLimit = takeWhile (<10000) oddSquares
    in  sum belowLimit

{-
 - Chapter 7
 -
 - MODULES
 -
-}

numUniques :: (Eq a) => [a] -> Int
numUniques = length . nub

search :: (Eq a) => [a] -> [a] -> Bool
search needle haystack =
    let nlen = length needle
    in foldl (\acc x -> if take nlen x == needle then True else acc) False (tails haystack)

encode :: Int -> String -> String
encode shift msg =
    let ords = map ord msg
        shifted = map (+ shift) ords
    in map chr shifted

decode :: Int -> String -> String
decode shift msg = encode (negate shift) msg

phoneBook = 
    [
        ("betty", "555-2938"),
        ("betty","342-2492"),
        ("bonnie", "452-2928"),
        ("patsy","493-2928"),
        ("patsy","943-2929"),
        ("patsy","827-9162"),
        ("lucille","205-2928"),
        ("wendy","939-8282"),
        ("penny","853-2492"),
        ("penny","555-2111")
    ]

findKey :: (Eq k) => k -> [(k,v)] -> Maybe v
findKey key [] = Nothing
findKey key ((k,v):xs) = if key == k then Just v else findKey key xs

findKey' :: (Eq k) => k -> [(k,v)] -> Maybe v
findKey' key = foldr (\(k,v) acc -> if key == k then Just v else acc) Nothing

fromList' :: (Ord k) => [(k,v)] -> Map.Map k v
fromList' = foldr (\(k,v) acc -> Map.insert k v acc) Map.empty

phoneBookToMap :: (Ord k) => [(k, String)] -> Map.Map k String
phoneBookToMap xs = Map.fromListWith (\number1 number2 -> number1 ++ ", " ++ number2) xs

phoneBookToMap' :: (Ord k) => [(k, a)] -> Map.Map k [a]  
phoneBookToMap' xs = Map.fromListWith (++) $ map (\(k,v) -> (k,[v])) xs
