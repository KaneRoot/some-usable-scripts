import Data.List as L

formatLine :: [String] -> [String]
formatLine x = map (\e -> e ++ [' ' | _ <- [length e..nb]]) x
               where nb = maximum $ map length x

completeMatrix :: [[String]] -> [[String]]
completeMatrix m = map (\e -> e ++ [""| _ <- [length e..nb]]) m
                   where nb = maximum $ map length m

main = do
    content <- getContents
    putStr $ unlines $ map unwords $ (L.transpose . (\x -> map formatLine x) . L.transpose . completeMatrix) $ map words $ lines content
