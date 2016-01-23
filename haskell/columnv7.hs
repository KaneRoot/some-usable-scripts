import Data.List
main = do interact $ (unlines . map unwords . transpose . map (pad ' ') . transpose . pad "" . map words . lines)
          where pad v m = map (\e -> e ++ replicate ((maximum $ map length m)- length e) v) m
