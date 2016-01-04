import Data.List as L

addEmpty :: Int -> [a] -> [a] -> [a]
addEmpty x v y
        | ysize == x = y
        | ysize < x  = addEmpty x v (y ++ v)
        | otherwise  = []
        where ysize = length y

formatLine :: [String] -> [String]
formatLine x =  map (addEmpty nb " ") x
                where nb = maximum $ map length x

formatLines :: [[String]] -> [[String]]
formatLines x = map formatLine x

completeMatrix :: [[String]] -> [[String]]
completeMatrix m = map (addEmpty nb [""]) m
                   where nb = maximum $ map length m

column :: [[String]] -> [[String]]
column x = L.transpose $ formatLines $ L.transpose $ completeMatrix x

main = do
    content <- getContents
    putStr $ unlines $ map unwords $ column $ map words $ lines content
