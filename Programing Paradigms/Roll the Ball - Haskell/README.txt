// Copyright 2020 Lica Robert-Mihai <robertlica21@gmail.com>
EN:

The game "Roll the Ball" implemented in Haskell and a solver for the game using the A* algorithm.

To play the game:
- run in the command line: stack exec ghci Interactive.hs
- to play level 0 (there are 10 levels): Interactvie.hs> play level0

To run the checker run the command:
    stack runhaskell RollTest.hs
or
    stack exec ghci RollTest.hs

RO:

Pentru rularea testelor:
      stack runhaskell RollTest.hs
sau 
      stack exec ghci RollTest.hs
 
      *RollTest.hs> main                      ---> rulează toate testele 
      *RollTest.hs> runTestPP nume_test       ---> rulează un test anume,
      												  cu o valoare din:
      				[ testAddObject
        	                     , testCreateLevel
                	             , testMove
                        	     , testWin
	                             , testSuccessors
        	                     , testBFS
                	             , testbidirBFS
                        	     , testExtractPath
	                             , testBonus
        	                     , testSolve
                	             ]

Pentru a juca în linia de comandă:
      -- setati workingOs la Windows sau Linux
       
      stack exec ghci Interactive.hs 
 
      *Interactvie.hs> play level0               ---> pornește în linia de 
                                                      comandă level0 
