
module Haskell where

import Foreign.C.Types

foreign export ccall haskellPrint :: CInt -> IO ()

haskellPrint :: CInt -> IO ()
haskellPrint (CInt n) = putStrLn $ show n ++ ". Printing from Haskell"
