import qualified Data.Text as T

splitOn :: String -> String -> [String]
splitOn x y = map T.unpack $ T.splitOn (T.pack x) $ T.pack y

transpose:: [[a]] -> [[a]]
transpose ([]:xs) = []
transpose x = (map head x) : transpose (map tail x)

addEmpty :: Int -> [a] -> [a] -> [a]
addEmpty x v y
        | ysize == x+1 = y
        | ysize <= x  = addEmpty x v (y ++ v)
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

putToLines :: [[String]] -> [String]
putToLines x = map (foldr (++) " ") x

main = do
    content <- getContents
    -- print $ column $ map (splitOn " ") $ lines content
    -- print $ putToLines $ column $ map (splitOn " ") $ lines content
    putStr $ unlines . putToLines $ column $ map (splitOn " ") $ lines content
