import Data.List as L

main = do
    content <- getContents
    putStr $ unlines $ map unwords $ L.transpose $ map formatLine $ L.transpose $ completeMatrix $ map words $ lines content
    where completeMatrix m = map (\e -> e ++ [""| _ <- [length e .. (\ x -> maximum $ map length x) m ]]) m
          formatLine x = map (\e -> e ++ [' ' | _ <- [length e..(\ x -> maximum $ map length x) x]]) x
