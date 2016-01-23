import Data.List
main = do interact $ (unlines . map unwords . transpose . map (completeMatrix ' ') . transpose . completeMatrix "" . map words . lines)
          where completeMatrix v m = map (\e -> e ++ replicate ((maximum $ map length m)- length e) v) m
