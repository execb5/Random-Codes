-- Haskell Annotations
--
-- All taken from the book:
--      http://learnyouahaskell.com/
--
-- God bless the internet


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
