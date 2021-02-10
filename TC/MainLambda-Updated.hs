--------------------------------------------------
module MainLambda where

-- Definição da sintaxe abstrata na linguagem: simple-typed lambda calculus


import Data.List

data TLam = Var Char
          | Abs Char TLam
          | App TLam TLam  deriving (Show, Eq) 


-------------------------------------------------------------------------------
freeVars :: TLam -> [Char]
freeVars (Var x) = [x] 
freeVars (Abs x t1) = (delete x (freeVars t1)) 
freeVars (App t1 t2) = (freeVars t1) ++ (freeVars t2)


isVal :: TLam -> Bool
isVal (Var x) = True
isVal (Abs x t) = True
isVal _ = False

-------------------------------------------------------------------------------
subs :: (Char, TLam) -> TLam -> TLam
subs (x,s) (Var y) = if (x==y) then s else (Var y)
subs (x,s) (Abs y t1) = (Abs y (subs (x, s) t1))
subs (x,s) (App t1 t2) = App (subs (x, s) t1) (subs (x, s) t2)

