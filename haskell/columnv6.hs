import Data.List as L
main = do content <- getContents
          putStr $ unlines $ map unwords $ L.transpose $ map (completeMatrix ' ') $ L.transpose $ completeMatrix "" $ map words $ lines $ content
          where completeMatrix v m = map (\e -> e ++ [v| _ <- [length e .. (\ x -> maximum $ map length x) m ]]) m
