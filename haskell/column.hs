transpose:: [[a]] -> [[a]]
transpose ([]:xs) = []
transpose x = (map head x) : transpose (map tail x)

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
column x = transpose $ formatLines $ transpose $ completeMatrix x

main = do
    content <- getContents
    putStr $ unlines $ map unwords $ column $ map words $ lines content
