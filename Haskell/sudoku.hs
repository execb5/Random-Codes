import Data.List

type T = (Int,Int) -> [Int]

main = do
  s <- getContents
  putStr $ unlines $ map disp $ solve [input s]

solve :: [T] -> [T]
solve s = foldr search s idx where
    search p l = [mark (p,n) s | s <- l, n <- s p]

mark :: ((Int,Int),Int) -> T -> T
mark (p@(i,j),n) s q@(x,y) =
  if p==q then [n] else
  if x==i || y==j || e x i && e y j then delete n $ s q else s q
  where e a b = div (a-1) 3==div (b-1) 3

disp :: T -> String
disp s  = unlines [unwords [show $ head $ s (i,j) | j <- [1..9]] | i <- [1..9]]

input :: String -> T
input s = foldr mark (const [1..9]) $
  [(p,n) | (p,n) <- zip idx $ map read $ lines s >>= words, n>0]

idx :: [(Int,Int)]
idx = [(i,j) | i <- [1..9], j <- [1..9]]
