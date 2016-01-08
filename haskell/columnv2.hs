import Data.List as L

formatLine :: [String] -> [String]
formatLine x = map (\e -> e ++ [' ' | _ <- [length e..nb]]) x
               where nb = maximum $ map length x

formatLines :: [[String]] -> [[String]]
formatLines x = map formatLine x

completeMatrix :: [[String]] -> [[String]]
completeMatrix m = map (\e -> e ++ [""| _ <- [length e..nb]]) m
                   where nb = maximum $ map length m

column :: [[String]] -> [[String]]
column = (L.transpose . formatLines . L.transpose . completeMatrix)

main = do
    content <- getContents
    putStr $ unlines $ map unwords $ column $ map words $ lines content
