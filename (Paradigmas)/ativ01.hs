{-
Código-fonte para resolver o quebra-cabeça lógico:
http://logicgridpuzzles.com/puzzles/show_logic.php?ID=55

Crie um novo código para resolver o seu quebra-cabeça.
-}


import Data.List (permutations, intersperse)

{--- se os atributos forem nomes, use a seguinte estrutura-}

data Shoe = Boots | Pumps | Sandals
    deriving (Show, Enum, Eq)
    
data Color = Brown | Green | Pink
            deriving (Show, Enum, Eq)

{--- se forem numéricos represente como lista de números-}

preços = [19, 38, 40]

{--- gera as permutações dos valores possíveis-}

sapatosPerms = permutations [Boots ..]
corPerms = permutations [Brown ..]
preçosPerms = permutations preços

{-
-- gera todas as combinações de valores para as três pessoas
-- zip3 funciona igual zip, mas para três listas, gerando lista de triplas-}

combinações = [ zip3 p1 p2 p3 | p1 <- sapatosPerms, 
                          p2 <- preçosPerms, 
                          p3 <- corPerms 
        ]
        
{--- funções para recuperar o valor de cada atributo        -}

sapato (s,_,_) = s
preço  (_,p,_) = p
cor    (_,_,c) = c


{--- funções para recuperar os atributos de cada nome-}

clarisse [a1, _, _] = a1
margaret [_, a2, _] = a2
sally [_, _, a3] = a3

{--- operador Se booleano-}

True ==> True  = True
True ==> False = False
_    ==> _     = True

{--- regras sobre cada atributo-}

r1 a = (sapato a == Pumps) ==> not (cor a == Pink)
r2 a = (sapato a == Boots) ==> (cor a == Brown)

{--- regras sobre um nome especifico (posicional)-}

r3 as = sapato (margaret as) /= Boots
r4 as = sapato (clarisse as) /= Pumps
r5 as = preço (clarisse as) > preço (sally as)
r6 as = sapato (margaret as) == Sandals
r7 as = preço (margaret as) == 2 * (preço (sally as))
r8 as = cor (margaret as) /= Green

{-- aplica as regras condicionais e posicionais-}

condicional r as = all r as 
posicional  r as = r as

{-- gera as soluções que atendam as regras-}

soluções = [c | c <- combinações,
                condicional r1 c,
                condicional r2 c,
                posicional  r3 c,
                posicional  r4 c,
                posicional  r5 c,
                posicional  r6 c,
                posicional  r7 c,
                posicional  r8 c
           ]
           
{-- funções para imprimir o resultado   -}

nomes = [("Clarisse", clarisse), ("Margaret", margaret), ("Sally", sally)]

printSapato a = "comprou " ++ (show $ sapato a)
printCor    a = "cor " ++ (show $ cor a)
printPreço  a = "preço " ++ (show $ preço a)

printFrase (n, a) = concat 
                  $ intersperse " " 
                  $ [n, printSapato a, printCor a, printPreço a]

imprime s = unlines
          $ [printFrase (n, (f s)) | (n,f) <- nomes]


main = do 
  mapM_ (putStr . imprime) soluções
  
  